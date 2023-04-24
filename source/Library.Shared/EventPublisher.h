#pragma once
#include "RTTI.h"
#include "Vector.h"
#include "EventSubscriber.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Abstract base class to be inherited by all events for our event pub/sub system following the observer pattern.
	/// </summary>
	class EventPublisher : public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher, RTTI);

	public:

		/// <summary>
		/// Notify all subscribers of this event.
		/// </summary>
		virtual void Deliver();

	protected:

		/// <summary>
		/// Constructor that is protected and will be called in the consturctor initializer line on creation of event instances.
		/// </summary>
		/// <param name="subscriberList">Reference to the static subscriber list for the event type</param>
		EventPublisher(Vector<EventSubscriber*>& subscriberList);

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other">Reference to other EventPublisher</param>
		EventPublisher(const EventPublisher& other) = default;

		/// <summary>
		/// Copy Assignment operator
		/// </summary>
		/// <param name="other">Reference to other EventPublisher</param>
		EventPublisher& operator=(const EventPublisher& other) = default;
		
		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs">rvalue Reference to other EventPublisher</param>
		EventPublisher(EventPublisher&& rhs) noexcept = default;

		/// <summary>
		/// Move Assignment operator
		/// </summary>
		/// <param name="rhs">rvalue Reference to other EventPublisher</param>
		EventPublisher& operator=(EventPublisher&& rhs) noexcept = default;


		Vector<EventSubscriber*>* _subscribers;
	};
}