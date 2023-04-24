#include "pch.h"
#include "CppUnitTest.h"
#include "ToStringSpecializations.h"
#include "JsonParseCoordinator.h"
#include "JsonParseTestHelper.h"
#include "JsonParseIntegerHelper.h"
#include "JsonTableParseHelper.h"
#include "RTTI.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;


namespace LibraryDesktopTests
{
	TEST_CLASS(ParseCoordinatorTests)
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


		TEST_METHOD(CoordinatorConstruction)
		{

			std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper(new JsonParseTestHelper::Wrapper);
			JsonParseCoordinator coordinator(wrapper);

			Assert::AreEqual(size_t(0), wrapper->Depth());
			Assert::AreEqual(&coordinator, wrapper->GetJsonParseCoordinator());
			Assert::AreEqual(wrapper, coordinator.GetWrapper());

			auto helper = std::make_shared<JsonParseTestHelper>();
			coordinator.AddHelper(helper);


		}

		TEST_METHOD(HelpersAddRemove)
		{

			std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper(new JsonParseTestHelper::Wrapper);
			JsonParseCoordinator coordinator(wrapper);
			auto helper = std::make_shared<JsonParseTestHelper>();

			Assert::AreEqual(size_t(0), coordinator.Helpers().Size());
			coordinator.AddHelper(helper);
			Assert::AreEqual(size_t(1), coordinator.Helpers().Size());
			coordinator.RemoveHelper(helper);
			Assert::AreEqual(size_t(0), coordinator.Helpers().Size());


			coordinator.AddHelper(helper);
			Assert::ExpectException<std::runtime_error>([&helper, &coordinator] {coordinator.AddHelper(helper); });

			auto helper2 = std::make_shared<JsonParseIntegerHelper>();
			coordinator.AddHelper(helper2);
			Assert::AreEqual(size_t(2), coordinator.Helpers().Size());
			Assert::ExpectException<std::runtime_error>([&helper2, &coordinator] {coordinator.AddHelper(helper2); });


		}

		TEST_METHOD(IntegerParsing)
		{
			std::string inputString = R"(
			{ 
			 "integer": 100
			}
			)";

			std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper(new JsonParseIntegerHelper::Wrapper);
			JsonParseCoordinator coordinator(wrapper);
			auto helper = std::make_shared<JsonParseIntegerHelper>();
			coordinator.AddHelper(helper);

			coordinator.DeserializeObject(inputString);
			JsonParseIntegerHelper::Wrapper* rawWrapper = static_cast<JsonParseIntegerHelper::Wrapper*>(wrapper.get());

			Assert::AreEqual(size_t(100), rawWrapper->integerData.Front());
			Assert::AreEqual(size_t(0), rawWrapper->Depth());
			
		}

		TEST_METHOD(IntegerParseFile)
		{
			std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper(new JsonParseIntegerHelper::Wrapper);
			JsonParseCoordinator coordinator(wrapper);
			auto helper = std::make_shared<JsonParseIntegerHelper>();
			coordinator.AddHelper(helper);

			std::string file("Content/IntegerData.json");
			coordinator.DeserializeObjectFromFile(file);
			JsonParseIntegerHelper::Wrapper* rawWrapper = static_cast<JsonParseIntegerHelper::Wrapper*>(wrapper.get());

			Assert::AreEqual(size_t(100), rawWrapper->integerData.Front());
			Assert::AreEqual(size_t(0), rawWrapper->Depth());

		}

		TEST_METHOD(IntegerArrayParsing)
		{

			std::string inputString = R"(
			{ 
			 "integer": [100, 200, 300]
			}
			)";

			std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper(new JsonParseIntegerHelper::Wrapper);
			JsonParseCoordinator coordinator(wrapper);
			auto helper = std::make_shared<JsonParseIntegerHelper>();
			coordinator.AddHelper(helper);

			coordinator.DeserializeObject(inputString);
			JsonParseIntegerHelper::Wrapper* rawWrapper = static_cast<JsonParseIntegerHelper::Wrapper*>(wrapper.get());

			Assert::AreEqual(size_t(100), rawWrapper->integerData.Front());
			Assert::AreEqual(size_t(0), rawWrapper->Depth());

		}

		TEST_METHOD(DepthAndTraversing)
		{
			std::string inputString = R"(
			{ 
			 "A": {
					"B":[
							{
							}
						]
				  }
			}
			)";

			std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper(new JsonParseTestHelper::Wrapper);
			JsonParseCoordinator coordinator(wrapper);
			auto helper = std::make_shared<JsonParseTestHelper>();
			coordinator.AddHelper(helper);

			coordinator.DeserializeObject(inputString);
			Assert::AreEqual(size_t(2), helper->MaxDepth);
			Assert::AreEqual(size_t(2), helper->StartsCalled);
			Assert::AreEqual(size_t(2), helper->EndsCalled);
		}

		TEST_METHOD(Cloning)
		{
			std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper(new JsonParseTestHelper::Wrapper);
			JsonParseCoordinator coordinator(wrapper);
			coordinator.AddHelper(std::make_shared<JsonParseTestHelper>());

			std::shared_ptr<JsonParseCoordinator> cloneCoord = coordinator.Clone();

			Assert::AreNotEqual(coordinator.GetWrapper(), cloneCoord->GetWrapper());
			Assert::AreNotEqual(coordinator.Helpers().Front(), cloneCoord->Helpers().Front());

		}

		TEST_METHOD(MoveSemantics)
		{
			//Move Constructor
			{
				std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper(new JsonParseTestHelper::Wrapper);
				JsonParseCoordinator coordinator(wrapper);
				coordinator.AddHelper(std::make_shared<JsonParseTestHelper>());

				JsonParseCoordinator movedCoord(std::move(coordinator));

				Assert::AreEqual(size_t(0), coordinator.Helpers().Size());
				Assert::IsNull(coordinator.GetWrapper().get());

				Assert::AreEqual(size_t(1), movedCoord.Helpers().Size());
				Assert::AreEqual(movedCoord.GetWrapper(), wrapper);
				Assert::AreEqual(movedCoord.GetWrapper()->GetJsonParseCoordinator(), &movedCoord);

			}

			//Move Assignment
			{
				std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper(new JsonParseTestHelper::Wrapper);
				JsonParseCoordinator coordinator(wrapper);
				coordinator.AddHelper(std::make_shared<JsonParseTestHelper>());

				JsonParseCoordinator movedCoord(wrapper);
				movedCoord.AddHelper(std::make_shared<JsonParseTestHelper>());

				movedCoord = std::move(coordinator);

				Assert::AreEqual(size_t(0), coordinator.Helpers().Size());
				Assert::IsNull(coordinator.GetWrapper().get());

				Assert::AreEqual(size_t(1), movedCoord.Helpers().Size());
				Assert::AreEqual(movedCoord.GetWrapper(), wrapper);
				Assert::AreEqual(movedCoord.GetWrapper()->GetJsonParseCoordinator(), &movedCoord);

			}
		}

		TEST_METHOD(WrapperRTTI)
		{

			{
				JsonParseTestHelper::Wrapper a{};
				RTTI* rtti = &a;

				Assert::IsTrue(rtti->Is(JsonParseTestHelper::Wrapper::TypeIdClass()));

				Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));

				Assert::AreEqual(JsonParseTestHelper::Wrapper::TypeIdClass(), rtti->TypeIdInstance());

				JsonParseTestHelper::Wrapper* f = rtti->As<JsonParseTestHelper::Wrapper>();
				Assert::IsNotNull(f);
				Assert::AreEqual(&a, f);

			}

			{

				const JsonParseTestHelper::Wrapper a{};
				const RTTI* rtti = &a;
				Assert::IsTrue(rtti->Is(JsonParseTestHelper::Wrapper::TypeIdClass()));

				Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));

				Assert::AreEqual(JsonParseTestHelper::Wrapper::TypeIdClass(), rtti->TypeIdInstance());

				const JsonParseTestHelper::Wrapper* f = rtti->As<JsonParseTestHelper::Wrapper>();
				Assert::IsNotNull(f);
				Assert::AreEqual(&a, f);

			}

			{
				JsonParseTestHelper::Wrapper a{};
				RTTI* rtti = &a;

				Assert::AreEqual(a.ToString(), rtti->ToString());
			}

			{
				//TableWrapperRTTItesting
				{

					JsonTableParseHelper::Wrapper a{ std::make_shared<Scope>()};
					RTTI* rtti = &a;

					Assert::IsTrue(rtti->Is(JsonTableParseHelper::Wrapper::TypeIdClass()));

					Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));

					Assert::AreEqual(JsonTableParseHelper::Wrapper::TypeIdClass(), rtti->TypeIdInstance());

					JsonTableParseHelper::Wrapper* f = rtti->As<JsonTableParseHelper::Wrapper>();
					Assert::IsNotNull(f);
					Assert::AreEqual(&a, f);

				}

				{

					const JsonTableParseHelper::Wrapper a{ std::make_shared<Scope>() };
					const RTTI* rtti = &a;
					Assert::IsTrue(rtti->Is(JsonTableParseHelper::Wrapper::TypeIdClass()));

					Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));

					Assert::AreEqual(JsonTableParseHelper::Wrapper::TypeIdClass(), rtti->TypeIdInstance());

					const JsonTableParseHelper::Wrapper* f = rtti->As<JsonTableParseHelper::Wrapper>();
					Assert::IsNotNull(f);
					Assert::AreEqual(&a, f);

				}

				{
					JsonTableParseHelper::Wrapper a{ std::make_shared<Scope>() };
					RTTI* rtti = &a;

					Assert::AreEqual(a.ToString(), rtti->ToString());
				}


			}

		}



		TEST_METHOD(TableParsingInteger)
		{
			std::string inputString = R"(
			{
				"Health": {
					"type": "integer",
					"value": "100"
				}
			})";
			auto rootScope = std::make_shared<Scope>();
			std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper(new JsonTableParseHelper::Wrapper(rootScope));
			JsonParseCoordinator coordinator(wrapper);
			auto helper = std::make_shared<JsonTableParseHelper>();
			coordinator.AddHelper(helper);
			coordinator.DeserializeObject(inputString);

			JsonTableParseHelper::Wrapper* rawWrapper = static_cast<JsonTableParseHelper::Wrapper*>(wrapper.get());
			Assert::AreEqual(size_t(1), rawWrapper->root->Size());
			Scope& scopeAfterParse = *rawWrapper->root;
			Assert::AreEqual(100, scopeAfterParse["Health"].GetInteger());

		}

		TEST_METHOD(TableParsingIntegerArray)
		{

			std::string inputString = R"(
			{
				"HealthArr": {
					"type": "integer",
					"value": ["1", "2", "3"]
				}
			})";
			auto rootScope = std::make_shared<Scope>();
			std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper(new JsonTableParseHelper::Wrapper(rootScope));
			JsonParseCoordinator coordinator(wrapper);
			auto helper = std::make_shared<JsonTableParseHelper>();
			coordinator.AddHelper(helper);
			coordinator.DeserializeObject(inputString);

			JsonTableParseHelper::Wrapper* rawWrapper = static_cast<JsonTableParseHelper::Wrapper*>(wrapper.get());
			Assert::AreEqual(size_t(1), rawWrapper->root->Size());
			Scope& scopeAfterParse = *rawWrapper->root;
			Assert::AreEqual(1, scopeAfterParse["HealthArr"].GetInteger(0));
			Assert::AreEqual(2, scopeAfterParse["HealthArr"].GetInteger(1));
			Assert::AreEqual(3, scopeAfterParse["HealthArr"].GetInteger(2));


		}

		TEST_METHOD(TableParsingNestedScope)
		{
			std::string inputString = R"(
			{
				"NestedScope": {
					"type": "table",
					"value": 
						{
							"Health": {
								"type": "integer",
								"value": "100"
						}
					}
				}
			})";

			auto rootScope = std::make_shared<Scope>();
			std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper(new JsonTableParseHelper::Wrapper(rootScope));
			JsonParseCoordinator coordinator(wrapper);
			auto helper = std::make_shared<JsonTableParseHelper>();
			coordinator.AddHelper(helper);
			coordinator.DeserializeObject(inputString);

			JsonTableParseHelper::Wrapper* rawWrapper = static_cast<JsonTableParseHelper::Wrapper*>(wrapper.get());
			Assert::AreEqual(size_t(1), rawWrapper->root->Size());
			Scope& root = *rawWrapper->root;

			Assert::IsTrue(Datum::DatumTypes::Table == root["NestedScope"].Type());
			Assert::AreEqual(100, root["NestedScope"].GetTable()["Health"].GetInteger());
		}

		TEST_METHOD(TableParsingFromFile)
		{
			auto rootScope = std::make_shared<Scope>();
			std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper(new JsonTableParseHelper::Wrapper(rootScope));
			JsonParseCoordinator coordinator(wrapper);
			auto helper = std::make_shared<JsonTableParseHelper>();
			coordinator.AddHelper(helper);

			std::string file("Content/TableData.json");
			coordinator.DeserializeObjectFromFile(file);
			JsonTableParseHelper::Wrapper* rawWrapper = static_cast<JsonTableParseHelper::Wrapper*>(wrapper.get());

			Assert::AreEqual(size_t(14), rawWrapper->root->Size());
			Scope& table = *rawWrapper->root;

			Assert::AreEqual(100, table["IntegerAttribute"].GetInteger());
			Assert::AreEqual(200, table["IntegerAttributeArr"].GetInteger(0));
			Assert::AreEqual(300, table["IntegerAttributeArr"].GetInteger(1));
			Assert::AreEqual(400, table["IntegerAttributeArr"].GetInteger(2));

			Assert::AreEqual(1.5f, table["FloatAttribute"].GetFloat());
			Assert::AreEqual(1.5f, table["FloatAttributeArr"].GetFloat(0));
			Assert::AreEqual(2.5f, table["FloatAttributeArr"].GetFloat(1));

			Assert::AreEqual(glm::vec4(1, 2, 3, 4), table["VectorAttribute"].GetVector());
			Assert::AreEqual(glm::vec4(1), table["VectorAttributeArr"].GetVector(0));
			Assert::AreEqual(glm::vec4(2), table["VectorAttributeArr"].GetVector(1));

			Assert::AreEqual(glm::mat4(1), table["MatrixAttribute"].GetMatrix());
			Assert::AreEqual(glm::mat4(1), table["MatrixAttributeArr"].GetMatrix(0));
			Assert::AreEqual(glm::mat4(2), table["MatrixAttributeArr"].GetMatrix(1));

			Assert::AreEqual(std::string("HelloWorld!"), table["StringAttribute"].GetString());
			Assert::AreEqual(std::string("Hello"), table["StringAttributeArr"].GetString(0));
			Assert::AreEqual(std::string("World"), table["StringAttributeArr"].GetString(1));

			Assert::AreEqual(27, table["NestedScope"].GetTable()["NestedIntegerAttribute"].GetInteger());

			Assert::AreEqual(72, table["NestedScopeArr"].GetTable()["TimmyTable"].GetTable()["TimmysInteger"].GetInteger());
			Assert::AreEqual(43, table["NestedScopeArr"].GetTable()["TommyTable"].GetTable()["TommysInteger"].GetInteger());
		}
		
		TEST_METHOD(TableParsingExternal)
		{
			auto root = std::make_shared<AttributedFoo>();
			std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper(new JsonTableParseHelper::Wrapper(root));

			JsonParseCoordinator coordinator(wrapper);
			auto helper = std::make_shared<JsonTableParseHelper>();
			auto helperTestInt = std::make_shared<JsonParseIntegerHelper>();
			coordinator.AddHelper(helper);
			coordinator.AddHelper(helperTestInt);

			std::string file("Content/TableData.json");
			coordinator.DeserializeObjectFromFile(file);
			JsonTableParseHelper::Wrapper* rawWrapper = static_cast<JsonTableParseHelper::Wrapper*>(wrapper.get());
			Scope& table = *rawWrapper->root;

			Assert::AreEqual(7, table["ExternalIntegerArray"].GetInteger(0));
			Assert::AreEqual(6, table["ExternalIntegerArray"].GetInteger(1));
			Assert::AreEqual(5, table["ExternalIntegerArray"].GetInteger(2));

			Assert::AreEqual(62, table["ExternalInteger"].GetInteger());
		}

		TEST_METHOD(TableCloning)
		{
			auto root = std::make_shared<AttributedFoo>();
			std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper(new JsonTableParseHelper::Wrapper(root));
			JsonParseCoordinator coordinator(wrapper);
			coordinator.AddHelper(std::make_shared<JsonTableParseHelper>());

			std::shared_ptr<JsonParseCoordinator> cloneCoord = coordinator.Clone();

			Assert::AreNotEqual(coordinator.GetWrapper(), cloneCoord->GetWrapper());
			Assert::AreNotEqual(coordinator.Helpers().Front(), cloneCoord->Helpers().Front());

			
		}

		TEST_METHOD(ParsingAttributedFooCLASS)
		{
			std::string inputString = R"(
			{
				"AttributeFoo": {
					"type": "table",
					"class": "AttributedFoo",
					"value": 
						{
							"Health": {
								"type": "integer",
								"value": "100"
						}
					}
				}
			})";
			auto rootScope = std::make_shared<Scope>();
			std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper(new JsonTableParseHelper::Wrapper(rootScope));
			JsonParseCoordinator coordinator(wrapper);
			auto helper = std::make_shared<JsonTableParseHelper>();
			coordinator.AddHelper(helper);
			coordinator.DeserializeObject(inputString);

			JsonTableParseHelper::Wrapper* rawWrapper = static_cast<JsonTableParseHelper::Wrapper*>(wrapper.get());
			Assert::AreEqual(size_t(1), rawWrapper->root->Size());
			Scope& root = *rawWrapper->root;

			Assert::IsTrue(Datum::DatumTypes::Table == root["AttributeFoo"].Type());
			Assert::IsTrue(root["AttributeFoo"].GetTable().Is(AttributedFoo::TypeIdClass()));
			Assert::AreEqual(100, root["AttributeFoo"].GetTable()["Health"].GetInteger());
		}




	private:
		inline static _CrtMemState _startMemState;
	};
}