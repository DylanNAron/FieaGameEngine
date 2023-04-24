#include "pch.h"
#include "FooSubscriber.h"

namespace UnitTests
{
	void FooSubscriber::Notify(const FieaGameEngine::EventPublisher& eventPublisher)
	{
		eventPublisher;
		isNotified = true;
	}
}
