#pragma once

namespace FieaGameEngine
{
	class EventPublisher;

	/// <summary>
	/// Abstract base class to be inherited from all classes that wish to be a subscriber to an event. There is no data, so multiple inheritance will not be an issue. This is the observer in our event system which implements the observer pattern
	/// </summary>
	class EventSubscriber
	{
	public:
		/// <summary>
		/// Notifies the subscriber. pure virtual method that accepts the address of an EventPublisher (the actual argument will be the event itself). 
		/// </summary>
		/// <param name="eventPublisher"> Event that is notifying this subscriber</param>
		virtual void Notify(const EventPublisher& eventPublisher) = 0;

		EventSubscriber() = default;
		virtual ~EventSubscriber() = default;
	};

}