#pragma once
#include "EventPublisher.h"
#include "RTTI.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Event derives from event publisher and is templated for the concrete type of message to send
	/// </summary>
	/// <typeparam name="T"> templated type for event</typeparam>
	template<typename T>
	class Event final : public EventPublisher
	{
		RTTI_DECLARATIONS(Event, EventPublisher);

	public:
		/// <summary>
		/// Constructor. Takes a message in which is the templated type.
		/// </summary>
		/// <typeparam name="message">The message object or the payload of this event</typeparam>
		Event(const T& message);

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <typeparam name="other">reference to other event</typeparam>
		Event(const Event& other) = default;

		/// <summary>
		/// Copy Assignment operator
		/// </summary>
		/// <typeparam name="other">reference to other event</typeparam>
		Event& operator=(const Event& other) = default;

		/// <summary>
		/// Move constructor
		/// </summary>
		/// <typeparam name="rhs">rvalue reference to other event</typeparam>
		Event(Event&& rhs) noexcept = default;

		/// <summary>
		/// Move assignment operator
		/// </summary>
		/// <typeparam name="rhs">rvalue reference to other event</typeparam>
		Event& operator=(Event&& rhs) noexcept = default;

		/// <summary>
		/// virtual destructor
		/// </summary>
		virtual ~Event() = default;

		/// <summary>
		/// Given the address of an event subscriber add it to the list of subscribers for this event type.
		/// </summary>
		/// <typeparam name="subscriber">Address of a subscriber</typeparam>
		static void Subscribe(EventSubscriber* subscriber);

		/// <summary>
		/// Given the address of an event subscriber remove it from the list of subscribers for this event type.
		/// </summary>
		/// <typeparam name="subscriber">Address of a subscriber</typeparam>
		static void Unsubscribe(EventSubscriber* subscriber);

		/// <summary>
		/// Remove all subscribers.
		/// </summary>
		static void UnsubscribeAll();

		/// <summary>
		/// Getter for the message (or payload) of this event
		/// </summary>
		const T& Message() const;

		/// <summary>
		/// Deliver this event, notify all subscribers and then handle all the pending subscribers.
		/// </summary>
		void Deliver() override;

		/// <summary>
		/// Helper function to handle all pending subscribers. Subscribers added/removed are in a pending list, so not to cause interuption during update
		/// </summary>
		static void HandlePendingSubscribers();
	private:
		T _message;
		inline static Vector<EventSubscriber*> _subscriberList{};

		inline static bool _pendingUnsubAll{ false };
		inline static Vector<EventSubscriber*> _pendingUnsubscribe{};
		inline static Vector<EventSubscriber*> _pendingSubscribe{};

	};		
}

#include "Event.inl"