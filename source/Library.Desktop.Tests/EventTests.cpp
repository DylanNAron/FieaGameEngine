#include "pch.h"
#include "CppUnitTest.h"
#include "ToStringSpecializations.h"
#include "RTTI.h"
#include "GameTime.h"
#include "FooSubscriber.h"
#include "EventQueue.h"
#include "Event.h"
#include "Foo.h"
#include "TestSubscriber.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;
using namespace std::string_literals;


namespace LibraryDesktopTests
{
	TEST_CLASS(EvenTests)
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

		TEST_METHOD(EventConstruction)
		{

			//Message
			Event<Foo> fooEvent(Foo{1});
			Assert::AreEqual(1, fooEvent.Message().Data());
		}

		TEST_METHOD(SubscribeUnsubscribe)
		{
			GameTime time;
			FooSubscriber fooSub;
			EventQueue eventQueue;
			auto event = std::make_shared<Event<Foo>>( Foo{ 1 } );

			eventQueue.Enqueue(event, time);
			Event<Foo>::Subscribe(&fooSub);
			Assert::IsFalse(fooSub.isNotified);

			time.SetCurrentTime(time.CurrentTime() + std::chrono::milliseconds(50));
			eventQueue.Update(time);
			Assert::IsTrue(fooSub.isNotified);


			fooSub.isNotified = false;

			Event<Foo>::Unsubscribe(&fooSub);
			eventQueue.Update(time);
			Assert::IsFalse(fooSub.isNotified);


			Event<Foo>::Subscribe(&fooSub);
			Event<Foo>::UnsubscribeAll();
			eventQueue.Update(time);
			Assert::IsFalse(fooSub.isNotified);

			Event<Foo>::HandlePendingSubscribers();
		}

		TEST_METHOD(EventQueueConstruction)
		{
			GameTime time;
			EventQueue eQueue;
			auto event = std::make_shared<Event<Foo>>(Foo { 1 });
			Assert::AreEqual(size_t(0), eQueue.Size());
			eQueue.Enqueue(event, time);
			Assert::AreEqual(size_t(0), eQueue.Size());
			
			eQueue.Update(time);
			Assert::AreEqual(size_t(1), eQueue.Size());

			eQueue.Clear();
			Assert::IsFalse(eQueue.IsEmpty());
			eQueue.Update(time);
			Assert::IsTrue(eQueue.IsEmpty());

			eQueue.Update(time);

		}

		TEST_METHOD(UnsubscribingInTheNotify)
		{
			GameTime time;
			EventQueue eventQueue;
			TestSubscriber sub;
			auto event = std::make_shared<Event<Foo>>(Foo { 1 });

			Event<Foo>::Subscribe(&sub);
			Event<Foo>::Subscribe(&sub);
			eventQueue.Enqueue(event, time);
			time.SetCurrentTime(time.CurrentTime() + std::chrono::milliseconds(50));
			eventQueue.Update(time);

			Assert::AreEqual(sub._data, event->Message().Data());

			Event<Foo>::HandlePendingSubscribers();
		}




	private:
		inline static _CrtMemState _startMemState;
	};
}
