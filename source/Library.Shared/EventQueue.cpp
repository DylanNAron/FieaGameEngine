#include "pch.h"
#include "EventQueue.h"

namespace FieaGameEngine
{


	void EventQueue::Enqueue(std::shared_ptr<EventPublisher> eventPublisher, const GameTime& time, std::chrono::milliseconds delay)
	{
		_pendingAdd.PushBack(QueueEntry{ eventPublisher, time.CurrentTime() + delay });
	}

	void EventQueue::Update(const GameTime& time)
	{
		HandlePendingQueue();

		for (auto& entry : _queuedEvents)
		{
			if (entry.IsExpired(time))
			{
				entry._event->Deliver();
				_pendingRemove.PushBack(&entry);
			}
		}
	}

	void EventQueue::Clear()
	{
		_pendingClear = true;
	}

	bool EventQueue::IsEmpty()
	{
		return _queuedEvents.IsEmpty();
	}

	size_t EventQueue::Size()
	{
		return _queuedEvents.Size();
	}

	void EventQueue::HandlePendingQueue()
	{
		if (!_pendingClear)
		{
			for (const auto& entry : _pendingRemove)
			{
				_queuedEvents.Remove(*entry);
			}
			for (auto& entry : _pendingAdd)
			{
				_queuedEvents.PushBack(std::move(entry));
			}
		}
		else
		{
			_queuedEvents.Clear();
			_pendingClear = false;
		}

		_pendingAdd.Clear();
		_pendingRemove.Clear();
	}

	bool QueueEntry::IsExpired(const GameTime& time)
	{
		return time.CurrentTime() >= _expirationtime;
	}

	bool QueueEntry::operator==(const QueueEntry& other) const
	{
		return _event == other._event && _expirationtime == other._expirationtime;
	}

	bool QueueEntry::operator!=(const QueueEntry& other) const
	{
		return !(*this == other);
	}

}
