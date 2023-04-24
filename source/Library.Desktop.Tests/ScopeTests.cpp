#include "pch.h"
#include "CppUnitTest.h"
#include "ToStringSpecializations.h"
#include "Scope.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTests;
using namespace std;
using namespace std::string_literals;
using namespace FieaGameEngine;

namespace LibraryDesktopTests
{
	TEST_CLASS(ScopeTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &_startMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(Construction)
		{
			{
				Scope scope{};
				Assert::IsNull(scope.GetParent());
				Assert::AreEqual(size_t(0), scope.Size());
			}

			{
				Scope scope(8);
				Assert::IsNull(scope.GetParent());
				Assert::AreEqual(size_t(0), scope.Size());
			}
		}

		TEST_METHOD(Append)
		{
			Scope scope{};
			const string a = "apple";

			Assert::AreEqual(size_t(0), scope.Size());
			Datum& aDatum = scope.Append(a);
			aDatum = "Scope time!";
			Assert::AreEqual(size_t(1), scope.Size());
			Assert::IsNotNull(scope.Find(a));
		}

		TEST_METHOD(AppendScope)
		{

			Scope scope;
			const string a = "apple";
			const string b = "banana";

			Scope& nestedScope = scope.AppendScope(a);
			nestedScope.Append(b);

			Assert::AreEqual(size_t(1), scope.Size());
			Assert::IsNotNull(scope.Find(a));

			Scope* foundScope = nullptr;
			nestedScope.Search(a, foundScope);
			Assert::AreEqual(scope, *foundScope);
			Assert::IsTrue(scope == *foundScope);
		}

		TEST_METHOD(Find)
		{
			Scope scope{};
			const string a = "apple";
			const string b = "banana";
			const string tst = "Scope time!";

			Datum& aDatum = scope.Append(a);
			aDatum = "Scope time!";

			Assert::IsNotNull(scope.Find(a));
			Assert::AreEqual(tst, scope.Find(a)->GetString());
			Assert::IsNull(scope.Find(b));
		}

		TEST_METHOD(FindContainedScope)
		{

			{

				Scope scope;
				const string a = "apple";

				Scope& nestedScope = scope.AppendScope(a);
				Scope& nestedScope2 = scope.AppendScope(a);
				Scope& nestedScope3 = scope.AppendScope(a);
				
				auto [Datum, index] = scope.FindContainedScope(&nestedScope3);
				Assert::AreEqual(size_t(2), index);

				nestedScope;
				nestedScope2;
				nestedScope3;
			}

		}


		TEST_METHOD(Search)
		{

			{
				Scope scope;
				const string a = "apple";
				const string b = "banana";
				Scope& nestedScope = scope.AppendScope(a);
				Scope& nestedNestedScope = nestedScope.AppendScope(b);

				Scope* foundScope = nullptr;
				nestedNestedScope.Search(a, foundScope);
				Assert::AreEqual(scope, *foundScope);
				Assert::IsTrue(scope == *foundScope);
			}

			{
				const string a = "apple";

				Scope scope;
				Scope* foundScope = nullptr;
				scope.Search(a, foundScope);

				Assert::IsNull(foundScope);

			}

		}

		TEST_METHOD(Clear)
		{
			Scope scope{};
			const string a = "apple";
			const string b = "banana";

			Datum& aDatum = scope.Append(a);
			aDatum = "Scope time!";
			Datum& bDatum = scope.Append(b);
			bDatum = "its scope or nothin!";

			Assert::IsNotNull(scope.Find(a));
			Assert::IsNotNull(scope.Find(b));

			scope.Clear();

			Assert::IsNull(scope.Find(a));
			Assert::IsNull(scope.Find(b));


		}

		TEST_METHOD(Adopt)
		{
			//test basic adoption
			{
				Scope originalScope;
				const string a = "apple";
				const string b = "banana";
				Scope& nestedScope = originalScope.AppendScope(a);
				nestedScope.Append(b);

				Scope adoptingScope;
				adoptingScope.Adopt(nestedScope, a);

				//nested scope should not be present in originalScope and should be in adoptingScope
				Assert::AreNotEqual(nestedScope.GetParent(), &originalScope);
				Assert::AreEqual(nestedScope.GetParent(), &adoptingScope);

			}

			//Ancestory
			{
				const string a = "A";
				const string b = "B";
				const string c = "C";

				Scope scope;
				Scope& aScope = scope.AppendScope(a);
				Scope& bScope = scope.AppendScope(b);
				Scope& cScope = scope.AppendScope(c);

				Assert::ExpectException<std::runtime_error>([&cScope, &bScope]() { cScope.Adopt(bScope, "AdoptingAncestor"); });
				Assert::ExpectException<std::runtime_error>([&cScope, &aScope]() { cScope.Adopt(aScope, "AdoptingAncestor"); });

			}


			//key does match with datum of type table
			{
				const string a = "A";
				const string b = "B";
				const string c = "C";

				Scope scopeForAdopt;
				Scope& cScope = scopeForAdopt.AppendScope(c);

				Scope scope;
				Datum& aDatum = scope.Append(a);
				aDatum = 7.f; //float at key a Datum so cannot input table
				Scope& bScope = scope.AppendScope(b);
				bScope;

				Assert::ExpectException<std::runtime_error>([&cScope, &scope, &a]() { scope.Adopt(cScope, a);  });

			}

		}

		TEST_METHOD(Orphan)
		{

			{
				Scope originalScope;
				const string a = "apple";
				const string b = "banana";
				Scope& nestedScope = originalScope.AppendScope(a);
				nestedScope.Append(b);

				Scope* orphanNestedScope = nestedScope.Orphan();
				
				//no parent
				Assert::IsNull(orphanNestedScope->GetParent());
				//datum has no scopes in it anymore
				Datum& tableDatum = originalScope.Append(a);
				Assert::AreEqual(size_t(0), tableDatum.Size());
				//we must delete the orphan because we took ownership

				delete orphanNestedScope;

			}

		}

		TEST_METHOD(CopySemantics)
		{
			//Copy construction basic
			{

				Scope scope{};
				const string a = "apple";
				const string b = "banana";
				Datum& aDatum = scope.Append(a);
				aDatum = "Scope time!";

				Scope scopeCopy(scope);
				Assert::AreEqual(scope, scopeCopy);

			}

			//Copy construction with nestedScopes
			{
				const string a = "A";
				const string b = "B";
				const string c = "C";
				Scope scope;
				Datum& aDatum = scope.Append(a);
				aDatum = "Hello!";
				Datum& bDatum = scope.Append(b);
				bDatum = 7.f;
				Scope& cScope = scope.AppendScope(c);
				cScope.Append(a);

				Scope scopeCopy(scope);
				Assert::AreEqual(scope, scopeCopy);

			}

			//copy assignment
			{

				Scope scope{};
				const string a = "apple";
				const string b = "banana";
				Datum& aDatum = scope.Append(a);
				aDatum = "Scope time!";

				Scope scopeCopy;
				scopeCopy.Append(b);
				scopeCopy = scope;
				Assert::AreEqual(scope, scopeCopy);

			}

			//Copy assignment with nested scope
			{
				const string a = "A";
				const string b = "B";
				const string c = "C";
				Scope scope;
				Datum& aDatum = scope.Append(a);
				aDatum = "Hello!";
				Datum& bDatum = scope.Append(b);
				bDatum = 7.f;
				Scope& cScope = scope.AppendScope(c);
				cScope.Append(a);

				Scope scopeCopy;
				scopeCopy = scope;
				Assert::AreEqual(scope, scopeCopy);

			}

		}

		TEST_METHOD(MoveSemantics)
		{

			//move construction of root scope (with nested scopes)
			{
				Scope scope;
				const string a = "A";
				const string b = "B";
				Scope& nestedScope = scope.AppendScope(a);
				nestedScope.Append(b);

				Scope scopeMove(std::move(scope));
				Assert::AreEqual(size_t(1), scopeMove.Size());
				Assert::AreEqual(size_t(0), scope.Size());

				Assert::AreEqual(&scopeMove, scopeMove[a][0].GetParent());
			}

			//move construction of nested Scope
			{
				Scope scope;
				const string a = "apple";
				const string b = "banana";
				Scope& nestedScope = scope.AppendScope(a);
				nestedScope.Append(b);

				Scope scopeMove(std::move(nestedScope));

				Assert::AreEqual(size_t(1), scopeMove.Size());
				Assert::IsNull(scopeMove.GetParent());

				
			}

			
			//move Assignment of root scope (with nested scopes)
			{
				Scope scope;
				const string a = "A";
				const string b = "B";
				Scope& nestedScope = scope.AppendScope(a);
				nestedScope.Append(b);

				Scope scope2;
				Scope& scopeMove = scope2.AppendScope(a);
				scopeMove = std::move(scope);
				Assert::AreEqual(size_t(1), scopeMove.Size());
				Assert::AreEqual(size_t(0), scope.Size());

				Assert::AreEqual(&scopeMove, scopeMove[a][0].GetParent());
				
				delete &scopeMove; //heap allocated from move assign need to delete
			}

			//move Assignment of nested Scope
			{
				Scope scope;
				const string a = "apple";
				const string b = "banana";
				Scope& nestedScope = scope.AppendScope(a);
				nestedScope.Append(b);

				Scope scopeMove;
				scopeMove.AppendScope(b);

				scopeMove = std::move(nestedScope);

				Assert::AreEqual(size_t(1), scopeMove.Size());
				Assert::IsNull(scopeMove.GetParent());


			}

		}


		TEST_METHOD(Equality)
		{
			//Equal with nested scope
			{

				const string a = "A";
				const string b = "B";
				const string c = "C";
				Scope scope;
				Datum& aDatum = scope.Append(a);
				aDatum = "Hello!";
				Datum& bDatum = scope.Append(b);
				bDatum = 7.f;
				Scope& cScope = scope.AppendScope(c);
				cScope.Append(a);


				Scope scopeCopy = scope;
				Assert::AreEqual(scope, scopeCopy);
				Assert::IsFalse(scope != scopeCopy);

			}

			//Unequal with nested scope
			{
				const string a = "A";
				const string b = "B";
				const string c = "C";
				Scope scope;
				Datum& aDatum = scope.Append(a);
				aDatum = "Hello!";
				Datum& bDatum = scope.Append(b);
				bDatum = 7.f;
				Scope& cScope = scope.AppendScope(c);
				cScope.Append(a);

				Scope scope2;
				Datum& a2Datum = scope2.Append(a);
				a2Datum = "Hello!";
				Datum& b2Datum = scope2.Append(b);
				b2Datum = 8.f;
				Scope& c2Scope = scope2.AppendScope(c);
				c2Scope.Append(a);

				Scope scope3;
				scope3.Append(c);

				Assert::AreNotEqual(scope, scope2);
				Assert::IsFalse(scope == scope2);

				Assert::AreNotEqual(scope, scope3);

			}

		}


		TEST_METHOD(Indexing)
		{
			const string a = "A";
			const string b = "B";
			const string c = "C";
			Scope scope;
			Datum& aDatum = scope[a];
			aDatum = "Hello!";
			scope[b];
			scope[1].PushBack(7.f);

			Assert::AreEqual(size_t(2), scope.Size());
			Assert::IsNotNull(scope.Find(a));
			Assert::IsNotNull(scope.Find(b));
			Assert::IsNull(scope.Find(c));

		}



	private:
		inline static _CrtMemState _startMemState;
	};
}