#include "pch.h"
#include "CppUnitTest.h"
#include "ToStringSpecializations.h"
#include "AttributedFoo.h"
#include "TypeRegistry.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;


namespace LibraryDesktopTests
{

	TEST_CLASS(TypeRegistryTests)
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

		TEST_METHOD(TypeRegistryCreateDestroy)
		{
			TypeRegistry* typeRegistry = TypeRegistry::GetInstance();

			typeRegistry->RegisterType(AttributedFoo::TypeIdClass(), AttributedFoo::Signatures());

			TypeRegistry::DestroyInstance();

		}


	private:
		inline static _CrtMemState _startMemState;
	};

}
