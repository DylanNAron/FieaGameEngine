#include "pch.h"
#include "CppUnitTest.h"
#include "Hashmap.h"
#include "ToStringSpecializations.h"
#include "HashFunctorSpecializations.h"
#include "Foo.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;


namespace LibraryDesktopTests
{
	TEST_CLASS(DefaultHashTests)
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

		TEST_METHOD(IntegerHash)
		{
			DefaultHash<int> hashFunctor{};
			const int a{ 1 };
			const int b{ 1 };
			const int c{ 2 };

			Assert::AreEqual( hashFunctor(a), hashFunctor(a) );
			Assert::AreEqual( hashFunctor(a), hashFunctor(b) );
			Assert::AreNotEqual( hashFunctor(a), hashFunctor(c) );
			Assert::AreNotEqual( hashFunctor(b), hashFunctor(c) );


		}

		TEST_METHOD(StringHash)
		{
			DefaultHash<std::string> hashFunctor{};
			const std::string a = "Hello";
			const std::string b = "ByeBye";
			const std::string c(a);


			Assert::AreEqual(hashFunctor(a), hashFunctor(a));
			Assert::AreEqual(hashFunctor(a), hashFunctor(c));
			Assert::AreNotEqual(hashFunctor(a), hashFunctor(b));

		}

		TEST_METHOD(FooHash)
		{
			DefaultHash<Foo> hashFunctor{};
			const Foo a{ 1 };
			const Foo b{ 1 };
			const Foo c{ 2 };

			Assert::AreEqual(hashFunctor(a), hashFunctor(a));
			Assert::AreEqual(hashFunctor(a), hashFunctor(b));
			Assert::AreNotEqual(hashFunctor(a), hashFunctor(c));
			Assert::AreNotEqual(hashFunctor(b), hashFunctor(c));
		}

		TEST_METHOD(CharHash)
		{
			DefaultHash<char*> hashFunctor{};

			const char* a = "apple";
			const char* b = "apple";
			const char* c = "orange";

			Assert::AreEqual(hashFunctor(a), hashFunctor(a));
			Assert::AreEqual(hashFunctor(a), hashFunctor(b));
			Assert::AreNotEqual(hashFunctor(a), hashFunctor(c));
			Assert::AreNotEqual(hashFunctor(b), hashFunctor(c));
		}

		

	private:
		inline static _CrtMemState _startMemState;
	};
}