#include "pch.h"
#include "CppUnitTest.h"
#include "ToStringSpecializations.h"
#include "TypeRegistry.h"
#include "RTTI.h"
#include "EventMessageAttributed.h"
#include "World.h"
#include "ReactionAttributed.h"
#include "ActionIncrement.h"
#include "Event.h"
#include "ActionEvent.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;
using namespace std::string_literals;


namespace LibraryDesktopTests
{
	TEST_CLASS(ReactionTests)
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

		TEST_METHOD(EventMessageAttributedConstruction)
		{

			EventMessageAttributed eventMessage;
			World gameWorld;
			eventMessage.SetSubtype("Hello"s);
			Assert::AreEqual("Hello"s, eventMessage.GetSubtype());
			eventMessage.SetWorld(gameWorld);
			Assert::AreSame(gameWorld, eventMessage.GetWorld());
		}

		TEST_METHOD(ReactionNotifyTesting)
		{
			GameObject root;
			World gameWorld(root);
			EventMessageAttributed eventMessage("Test", &gameWorld);
			ReactionAttributed* reaction = new ReactionAttributed;
			root.Adopt(*reaction, "Reaction");
			reaction->Append("Subtype").SetString("Test"s);
			reaction->Append("A") = 5;
			ActionIncrement* incrAct = new ActionIncrement;
			incrAct->Append("Target").SetString("A");
			reaction->Adopt(*incrAct, "Actions"s);

			//Updating the game should not affect the reaction as long as its not notified
			gameWorld.Update();
			Assert::AreEqual(5, reaction->Append("A").GetInteger());

			// Reaction should only update when Notified
			auto event = std::make_shared<Event<EventMessageAttributed>>(eventMessage);
			reaction->Notify(*event);
			Assert::AreEqual(6, reaction->Append("A").GetInteger());

		}

		TEST_METHOD(ActionEventUpdate)
		{
			GameObject root;
			World gameWorld(root);

			ActionEvent* actionEvent = new ActionEvent;
			root.Adopt(*actionEvent, "Actions"s);

			//When action events update is called it should enqueue an event
			Assert::AreEqual(size_t(0), gameWorld.GetEventQueue().Size());
			gameWorld.Update();
			Assert::AreEqual(size_t(1), gameWorld.GetEventQueue().Size());
			gameWorld.Update();

		}

		TEST_METHOD(ReactionToAnActionEvent)
		{
			GameObject root;
			World gameWorld(root);

			ActionEvent* actionEvent = new ActionEvent;
			actionEvent->Append("Subtype").SetString("Test"s);
			actionEvent->AppendAuxiliaryAttribute("TestAux") = 7;
			root.Adopt(*actionEvent, "Actions"s);

			ReactionAttributed* reaction = new ReactionAttributed;
			root.Adopt(*reaction, "Reaction");
			reaction->Append("Subtype").SetString("Test"s);

			//Before updating reaction has no auxiliary attributes and the eventQueue is Empty.
			Assert::AreEqual(size_t(0), gameWorld.GetEventQueue().Size());
			Assert::IsTrue(Datum::DatumTypes::Unknown == reaction->Append("TestAux").Type());

			Event<EventMessageAttributed>::Subscribe(reaction);
			gameWorld.Update();

			//After updating reaction will be notified and copy aux attributes from the message "test aux"
			Assert::AreEqual(size_t(1), gameWorld.GetEventQueue().Size());
			Assert::AreEqual(7, reaction->Append("TestAux").GetInteger());
			Assert::IsTrue(Datum::DatumTypes::Integer == reaction->Append("TestAux").Type());

			gameWorld.Update();

			Event<EventMessageAttributed>::UnsubscribeAll();
			Event<EventMessageAttributed>::HandlePendingSubscribers();

		}


	private:
		inline static _CrtMemState _startMemState;
	};
}
