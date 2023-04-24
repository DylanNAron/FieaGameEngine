#pragma once
#include "EventPublisher.h"
#include <memory>
#include <chrono>
#include "GameTime.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Struct to be held in the event queue, contains shared pointer to the event publisher as well as epiration time and function for checking if is expired
	/// </summary>
	struct QueueEntry
	{
		QueueEntry() = default;
		std::shared_ptr<EventPublisher> _event;
		std::chrono::high_resolution_clock::time_point _expirationtime;
		inline bool IsExpired(const GameTime& time);

		inline bool operator!=(const QueueEntry& other) const;
		inline bool operator==(const QueueEntry& other) const;
	};

	/// <summary>
	/// Queue of events to be updated from the game. The queue will publish expired events.
	/// </summary>
	class EventQueue
	{
	public:

		/// <summary>
		/// Given the address of an EventPublisher, a GameTime (used to retrieve the current time), and an optional delay time, enqueue the event.
		/// </summary>
		/// <param name="eventPublisher">shared pointer to an event publisher</param>
		/// <param name="time">current game time</param>
		/// <param name="delay">an optional delay</param>
		void Enqueue(std::shared_ptr<EventPublisher> eventPublisher, const GameTime& time, std::chrono::milliseconds delay = std::chrono::milliseconds(0));

		/// <summary>
		/// Given a GameTime, publish any queued events that have expired.
		/// </summary>
		/// <param name="time">current game time</param>
		void Update(const GameTime& time);

		/// <summary>
		/// Clears the queued events and does not publish any of them, the queue will not be cleared until the next update
		/// </summary>
		void Clear();

		/// <summary>
		/// Returns boolean whether queue is empty
		/// </summary>
		/// <returns>boolean of isEmpty</returns>
		bool IsEmpty();

		/// <summary>
		/// Returns the size of the event queue
		/// </summary>
		/// <returns>size of queue</returns>
		size_t Size();

	private:
		Vector<QueueEntry> _queuedEvents;

		/// <summary>
		/// Helper function to handle the pending queue of events. Events to be added/removed are pending until update so as not to cause interruption.
		/// </summary>
		void HandlePendingQueue();
		bool _pendingClear{ false };
		Vector<QueueEntry> _pendingAdd;
		Vector<QueueEntry*> _pendingRemove;
	};

}