#include "pch.h"
#include "CppUnitTest.h"
#include "ToStringSpecializations.h"
#include "AttributedFoo.h"
#include "TypeRegistry.h"
#include "RTTI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;


namespace LibraryDesktopTests
{
	TEST_CLASS(AttributedTests)
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



		TEST_METHOD(ConstructionPopulate)
		{

			AttributedFoo aFoo;
			Assert::AreEqual(size_t(13), aFoo.Size());

			Assert::AreEqual(&aFoo, aFoo["this"].GetPointer()->As<AttributedFoo>());

			Assert::IsNotNull(aFoo.Find("ExternalInteger"));
			Assert::IsNotNull(aFoo.Find("ExternalFloat"));
			Assert::IsNotNull(aFoo.Find("ExternalString"));
			Assert::IsNotNull(aFoo.Find("ExternalVector"));
			Assert::IsNotNull(aFoo.Find("ExternalMatrix"));

			Assert::IsNotNull(aFoo.Find("ExternalIntegerArray"));
			Assert::IsNotNull(aFoo.Find("ExternalFloatArray"));
			Assert::IsNotNull(aFoo.Find("ExternalStringArray"));
			Assert::IsNotNull(aFoo.Find("ExternalVectorArray"));
			Assert::IsNotNull(aFoo.Find("ExternalMatrixArray"));

			Assert::IsNotNull(aFoo.Find("NestedScope"));
			Assert::IsNotNull(aFoo.Find("NestedScopeArray"));			

		}

		TEST_METHOD(CopySemantics)
		{
			//Copy constructor
			{
				AttributedFoo foo;
				AttributedFoo fooCopy(foo);

				Assert::AreEqual(&foo, foo["this"].GetPointer()->As<AttributedFoo>());
				Assert::AreEqual(&fooCopy, fooCopy["this"].GetPointer()->As<AttributedFoo>());
				Assert::AreNotEqual(&fooCopy, &foo);

				foo.AppendAuxiliaryAttribute("Aux");
				Assert::IsTrue(foo.IsAuxiliaryAttribute("Aux"));
				Assert::IsFalse(fooCopy.IsAuxiliaryAttribute("Aux"));
			}

			//Copy assignment
			{

				AttributedFoo foo;
				AttributedFoo fooCopy;
				fooCopy.AppendAuxiliaryAttribute("ShouldBeWiped");
				
				fooCopy = foo;
				Assert::IsFalse(fooCopy.IsAuxiliaryAttribute("ShouldBeWiped"));


				Assert::AreEqual(&foo, foo["this"].GetPointer()->As<AttributedFoo>());
				Assert::AreEqual(&fooCopy, fooCopy["this"].GetPointer()->As<AttributedFoo>());
				Assert::AreNotEqual(&fooCopy, &foo);

				foo.AppendAuxiliaryAttribute("Aux");
				Assert::IsTrue(foo.IsAuxiliaryAttribute("Aux"));
				Assert::IsFalse(fooCopy.IsAuxiliaryAttribute("Aux"));


			}

		}

		TEST_METHOD(MoveSemantics)
		{
			//Move Constructor
			{
				AttributedFoo foo;
				foo.AppendAuxiliaryAttribute("Aux");

				AttributedFoo fooCopy(std::move(foo));

				Assert::AreEqual(size_t(0), foo.Size());
				
				Assert::IsNotNull(fooCopy.Find("ExternalInteger"));
				Assert::IsNotNull(fooCopy.Find("ExternalFloat"));
				Assert::IsNotNull(fooCopy.Find("Aux"));

			}

			//Move Assignment
			{
				AttributedFoo foo;
				foo.AppendAuxiliaryAttribute("Aux");

				AttributedFoo fooCopy; fooCopy = std::move(foo);

				Assert::AreEqual(size_t(0), foo.Size());

				Assert::IsNotNull(fooCopy.Find("ExternalInteger"));
				Assert::IsNotNull(fooCopy.Find("ExternalFloat"));
				Assert::IsNotNull(fooCopy.Find("Aux"));
			}


		}

		TEST_METHOD(IsAttribute)
		{
			AttributedFoo aFoo;
			aFoo.Append("auxilaryAttribute!");

			Assert::IsTrue(aFoo.IsAttribute("ExternalInteger"));
			Assert::IsTrue(aFoo.IsAttribute("auxilaryAttribute!"));
			Assert::IsFalse(aFoo.IsAttribute("not an attribute"));
			
		}

		TEST_METHOD(IsPrescribed)
		{
			AttributedFoo aFoo;
			aFoo.Append("auxilaryAttribute!");

			Assert::IsTrue(aFoo.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsFalse(aFoo.IsPrescribedAttribute("auxilaryAttribute!"));
			Assert::IsFalse(aFoo.IsPrescribedAttribute("not an attribute"));
		}

		TEST_METHOD(IsAuxiliary)
		{
			AttributedFoo aFoo;
			aFoo.Append("auxilaryAttribute!");

			Assert::IsFalse(aFoo.IsAuxiliaryAttribute("ExternalInteger"));
			Assert::IsTrue(aFoo.IsAuxiliaryAttribute("auxilaryAttribute!"));
			Assert::IsFalse(aFoo.IsAuxiliaryAttribute("not an attribute"));

		}

		TEST_METHOD(AppendAuxiliaryAttribute)
		{
			AttributedFoo aFoo;
			Assert::ExpectException<std::runtime_error>([&aFoo] { aFoo.AppendAuxiliaryAttribute("ExternalInteger"); });

			aFoo.AppendAuxiliaryAttribute("PassMeTheAuxAttribute");
			Assert::IsTrue(aFoo.IsAuxiliaryAttribute("PassMeTheAuxAttribute"));

		}

		TEST_METHOD(Accessors)
		{
			AttributedFoo aFoo; //13 prescribed , 1 aux , full size is 14
			aFoo.AppendAuxiliaryAttribute("AnotherOne");

			Assert::AreEqual(size_t(0), aFoo.Attributes().first);
			Assert::AreEqual(aFoo.Size(), aFoo.Attributes().second);

			Assert::AreEqual(size_t(13), aFoo.PrescribedAttributes().second);

			Assert::AreEqual(size_t(13), aFoo.AuxiliaryAttributesRange().first);


		}

		TEST_METHOD(RTTITest)
		{

			{
				AttributedFoo a;
				RTTI* rtti = &a;

				Assert::IsTrue(rtti->Is(AttributedFoo::TypeIdClass()));

				Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));

				Assert::AreEqual(AttributedFoo::TypeIdClass(), rtti->TypeIdInstance());

				AttributedFoo* f = rtti->As<AttributedFoo>();
				Assert::IsNotNull(f);
				Assert::AreEqual(&a, f);

			}

			{

				const AttributedFoo a;
				const RTTI* rtti = &a;
				Assert::IsTrue(rtti->Is(AttributedFoo::TypeIdClass()));

				Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));

				Assert::AreEqual(AttributedFoo::TypeIdClass(), rtti->TypeIdInstance());

				const AttributedFoo* f = rtti->As<AttributedFoo>();
				Assert::IsNotNull(f);
				Assert::AreEqual(&a, f);

			}

			{
				AttributedFoo a;
				RTTI* rtti = &a;

				Assert::AreEqual(a.ToString(), rtti->ToString());
			}



		}


	private:
		inline static _CrtMemState _startMemState;
	};
}
