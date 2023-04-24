#include "pch.h"
#include "EventPublisher.h"
#include "Vector.h"
#include <future>

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(EventPublisher);

	EventPublisher::EventPublisher(Vector<EventSubscriber*>& subscriberList) : _subscribers(&subscriberList)
	{
	}

	void EventPublisher::Deliver()
	{
		Vector<std::future<void>> futures;

		for (auto& subscriber : *_subscribers)
		{
			//subscriber->Notify(*this);
			futures.PushBack(std::async(std::launch::async, [&subscriber, this] {subscriber->Notify(*this); }));
		}

		//Wait for all async tasks to finish
		for (auto& future : futures)
		{
			future.get();
		}
		
	}

}
