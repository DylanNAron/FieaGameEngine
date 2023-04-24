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

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;
using namespace std::string_literals;


namespace LibraryDesktopTests
{
	TEST_CLASS(GameObjectTests)
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
			GameObject obj;
			Assert::AreEqual(size_t(7), obj.Size());
			Assert::AreEqual(&obj, obj["this"].GetPointer()->As<GameObject>());
			Assert::IsNotNull(obj.Find("Name"));
			Assert::IsNotNull(obj.Find("Position"));
			Assert::IsNotNull(obj.Find("Rotation"));
			Assert::IsNotNull(obj.Find("Scale"));
			Assert::IsNotNull(obj.Find("Children"));
			Assert::IsNotNull(obj.Find("Actions"));
			Assert::AreEqual(size_t(0), obj.Children().Size());

		}

		TEST_METHOD(UpdateGameObjects)
		{
			World time;
			GameObject rootObj;
			TestGameObject* child1 = new TestGameObject{}; //increments value in its update method
			GameObject* child2 = new GameObject{};

			rootObj["Children"].PushBack(child1);
			rootObj["Children"].PushBack(child2);

			Assert::AreEqual(size_t(2), rootObj["Children"].Size());
			Assert::AreEqual(size_t(0), child1->incrementValue);
			rootObj.Update(time);
			Assert::AreEqual(size_t(1), child1->incrementValue);
			rootObj.Update(time);
			Assert::AreEqual(size_t(2), child1->incrementValue);

		}

		TEST_METHOD(ParseGameObject)
		{
			std::string file = R"(Content/TestGameObject.json)";

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

			//Children
			GameObject& aGameObject = static_cast<GameObject&>(root["AGameObject"].GetTable());
			Assert::AreEqual(size_t(2), aGameObject.Children().Size());
			Assert::AreEqual(72, aGameObject.GetChild()["child1Integer"].GetInteger());
			Assert::ExpectException<std::runtime_error>([&aGameObject] {aGameObject.GetChild(7); });


		}

		TEST_METHOD(Cloning)
		{
			Scope root;
			GameObject* obj = new GameObject;
			root.Adopt(*obj, "gameOb"s);

			Assert::IsTrue(root["gameOb"s].GetTable().Is(GameObject::TypeIdClass()));
			Scope rootCopy{ root };
			Assert::IsTrue(rootCopy["gameOb"s].GetTable().Is(GameObject::TypeIdClass()));

		}


		TEST_METHOD(ActionIncrement)
		{

			std::string file = R"(Content/TestGameObject.json)";
			auto rootScope = std::make_shared<Scope>();
			std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper(std::make_shared<JsonTableParseHelper::Wrapper>(rootScope));
			JsonParseCoordinator coordinator(wrapper);
			auto helper = std::make_shared<JsonTableParseHelper>();
			coordinator.AddHelper(helper);
			coordinator.DeserializeObjectFromFile(file);
			JsonTableParseHelper::Wrapper* rawWrapper = static_cast<JsonTableParseHelper::Wrapper*>(wrapper.get());
			Scope& root = *rawWrapper->root;

			GameObject& aGameObject = static_cast<GameObject&>(root["AGameObject"].GetTable());
			Datum& actions = aGameObject.Actions();
			Assert::AreEqual(size_t(1), actions.Size());
			Assert::AreEqual("IamAnActionIncrement"s, actions.GetTable().As<Action>()->Name());
			actions.GetTable().As<Action>()->SetName("ActionIncrName"s);
			Assert::AreEqual("ActionIncrName"s, actions.GetTable().As<Action>()->Name());
			Assert::IsTrue(actions.GetTable().Is(ActionIncrement::TypeIdClass()));

			//ActionIncrement
			Assert::AreEqual(size_t(4), actions.GetTable().Size());
			Assert::AreEqual("Health"s, actions.GetTable()["Target"].GetString());
			Assert::AreEqual(1, actions.GetTable()["Step"].GetInteger());

			//Incrementing
			World time;
			Assert::AreEqual(100, root["AGameObject"].GetTable()["Health"].GetInteger());
			aGameObject.Update(time);
			Assert::AreEqual(101, root["AGameObject"].GetTable()["Health"].GetInteger());


		}


	private:
		inline static _CrtMemState _startMemState;
	};
}
