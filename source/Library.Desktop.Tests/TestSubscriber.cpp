#include "pch.h"
#include "TestSubscriber.h"
#include "Event.h"
#include "Foo.h"

using namespace FieaGameEngine;

namespace UnitTests
{
	void TestSubscriber::Notify(const FieaGameEngine::EventPublisher& eventPublisher)
	{
		auto event = eventPublisher.As<Event<Foo>>();
		_data = event->Message().Data();
		Event<Foo>::Unsubscribe(this);
	}
}
