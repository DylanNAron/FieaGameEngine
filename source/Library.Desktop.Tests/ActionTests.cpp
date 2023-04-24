#include "pch.h"
#include "CppUnitTest.h"
#include "ToStringSpecializations.h"
#include "TypeRegistry.h"
#include "RTTI.h"
#include "GameObject.h"
#include "TestGameObject.h"
#include "GameTime.h"
#include "JsonParseCoordinator.h"
#include "Action.h"
#include "ActionIncrement.h"
#include "ActionList.h"
#include "ActionListWhile.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;
using namespace std::string_literals;


namespace LibraryDesktopTests
{
	TEST_CLASS(ActionTests)
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

		TEST_METHOD(ActionListConstruction)
		{
			ActionList actionList;
			ActionList* actionList2 = new ActionList;
			Assert::AreEqual(size_t(3), actionList.Size());
			Assert::IsNotNull(actionList.Find("Name"));
			Assert::IsNotNull(actionList.Find("Actions"));
			Assert::AreEqual(size_t(0), actionList.Actions().Size());

			World time;
			actionList.Adopt(*actionList2, "Actions"s);
			actionList.Update(time);
			Assert::IsTrue(static_cast<ActionList&>(actionList).Is(ActionList::TypeIdClass()));
			auto aListCopy = actionList;
			Assert::IsTrue(static_cast<ActionList&>(aListCopy).Is(ActionList::TypeIdClass()));
		}

		TEST_METHOD(Name)
		{
			ActionList actionList;
			actionList.SetName("dylan"s);
			Assert::AreEqual("dylan"s, actionList.Name());
		}

		TEST_METHOD(ActionListClone)
		{
			Scope* actionList = new ActionList;
			Scope* actionListClone = actionList->Clone();
			Assert::IsTrue(actionListClone->Is(ActionList::TypeIdClass()));

			delete actionList;
			delete actionListClone;

		}

		TEST_METHOD(WhileLoop)
		{
			World time;
			GameObject root;
			root.Append("A") = 5;

			ActionIncrement* incrAct = new ActionIncrement;
			incrAct->Append("Target").SetString("A");
			ActionListWhile* whileLoop = new ActionListWhile;


			//Construction
			Assert::IsNotNull(whileLoop->Find("Name"));
			Assert::IsNotNull(whileLoop->Find("Actions"));
			Assert::IsNotNull(whileLoop->Find("Condition"));

			//Looping with an action increment to test condition
			whileLoop->Adopt(*incrAct, "Actions"s);
			root.Adopt(*whileLoop, "Actions"s);

			Assert::AreEqual(size_t(1), whileLoop->Actions().Size());
			whileLoop->Update(time);
			Assert::AreEqual(5, root["A"].GetInteger());

			whileLoop->SetCondition(1);
			Assert::AreEqual(1, whileLoop->Condition());
			whileLoop->Update(time);
			Assert::AreEqual(6, root["A"].GetInteger());
		}

		TEST_METHOD(ParseWhileLoop)
		{
			World time;
			std::string file = R"(Content/TestActionWhileData.json)";
			auto rootScope = std::make_shared<Scope>();
			std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper(std::make_shared<JsonTableParseHelper::Wrapper>(rootScope));
			JsonParseCoordinator coordinator(wrapper);
			auto helper = std::make_shared<JsonTableParseHelper>();
			coordinator.AddHelper(helper);
			coordinator.DeserializeObjectFromFile(file);

			JsonTableParseHelper::Wrapper* rawWrapper = static_cast<JsonTableParseHelper::Wrapper*>(wrapper.get());
			Assert::AreEqual(size_t(1), rawWrapper->root->Size());
			Scope& root = *rawWrapper->root;

			Assert::IsTrue(Datum::DatumTypes::Table == root["AGameObject"].Type());
			Assert::IsTrue(root["AGameObject"].GetTable(0).Is(GameObject::TypeIdClass()));
			Assert::AreEqual(100, root["AGameObject"].GetTable()["Health"].GetInteger());

			GameObject& aGameObject = static_cast<GameObject&>(root["AGameObject"].GetTable());
			Assert::AreEqual(100, aGameObject["Health"].GetInteger());
			aGameObject.Update(time);
			Assert::AreEqual(100, aGameObject["Health"].GetInteger());

			//Changing condition of the while loop which contains action increment
			Assert::AreEqual("WhileLoop"s, static_cast<ActionListWhile&>(aGameObject.Actions().GetTable()).Name());
			static_cast<ActionListWhile&>(aGameObject.Actions().GetTable()).SetCondition(1);
			aGameObject.Update(time);
			Assert::AreEqual(101, aGameObject["Health"].GetInteger());



			//Test copy
			auto copy = root;
			Assert::IsTrue(Datum::DatumTypes::Table == root["AGameObject"].Type());
			Assert::IsTrue(root["AGameObject"].GetTable(0).Is(GameObject::TypeIdClass()));
			GameObject& copyObject = static_cast<GameObject&>(root["AGameObject"].GetTable());
			Assert::IsTrue(copyObject.Actions().GetTable().Is(ActionListWhile::TypeIdClass()));

		}


	private:
		inline static _CrtMemState _startMemState;
	};
}
