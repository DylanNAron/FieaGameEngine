#include "pch.h"
#include "CppUnitTest.h"
#include "ToStringSpecializations.h"
#include "Factory.h"
#include "Foo.h"
#include "RTTI.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;
using namespace std::string_literals;



namespace LibraryDesktopTests
{
	TEST_CLASS(FactoryTests)
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

		TEST_METHOD(Find)
		{
			//Finding Null
			auto foundPtr = Factory<Scope>::Find("UnknownFactory"s);
			Assert::IsNull(foundPtr);
		}

		TEST_METHOD(Create)
		{
			//Creating found null
			const std::string str = "UnknownFactory";
			Assert::IsNull(Factory<Scope>::Create(str));

			//Creating from a found foo factory
			Factory<RTTI>::Add(std::make_unique<FooFactory>());
			RTTI* factoryFoo = Factory<RTTI>::Create("Foo"s);
			Assert::IsNotNull(factoryFoo);
			Assert::IsTrue(factoryFoo->Is(Foo::TypeIdClass()));
			delete factoryFoo;
			Factory<RTTI>::Remove(std::make_unique<FooFactory>());

			//Attempting creation of foo after deleting factory should be null
			RTTI* notFoundFactory = Factory<RTTI>::Create("Foo"s);
			Assert::IsNull(notFoundFactory);
		}

		TEST_METHOD(AddRemove)
		{
			auto foundFactory = Factory<RTTI>::Find("Foo"s);
			Assert::IsNull(foundFactory);
			Factory<RTTI>::Add(std::make_unique<FooFactory>());
			foundFactory = Factory<RTTI>::Find("Foo"s);
			Assert::IsNotNull(foundFactory);
			Factory<RTTI>::Remove(std::make_unique<FooFactory>());
		}
	

	private:
		inline static _CrtMemState _startMemState;
	};
}