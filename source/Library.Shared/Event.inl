#pragma once
#include "Event.h"

namespace FieaGameEngine
{
	template<typename T>
	RTTI_DEFINITIONS(Event<T>);


	template<typename T>
	inline Event<T>::Event(const T& message) : 
		EventPublisher(_subscriberList), _message(message)
	{
	}

	template<typename T>
	inline void Event<T>::Subscribe(EventSubscriber* subscriber)
	{
		_pendingSubscribe.PushBack(subscriber);
	}

	template<typename T>
	inline void Event<T>::Unsubscribe(EventSubscriber* subscriber)
	{
		_pendingUnsubscribe.PushBack(subscriber);
	}

	template<typename T>
	inline void Event<T>::UnsubscribeAll()
	{
		_pendingUnsubAll = true;
	}

	template<typename T>
	inline const T& Event<T>::Message() const
	{
		return _message;
	}

	template<typename T>
	inline void Event<T>::Deliver()
	{
		HandlePendingSubscribers();
		EventPublisher::Deliver();
	}

	template<typename T>
	inline void Event<T>::HandlePendingSubscribers()
	{
		if (!_pendingUnsubAll)
		{
			for (auto& entry : _pendingUnsubscribe)
			{
				_subscriberList.Remove(entry);
				_subscriberList.ShrinkToFit();
			}
			for (auto& entry : _pendingSubscribe)
			{
				if (_subscriberList.Find(entry) == _subscriberList.end())
				{
					_subscriberList.PushBack(std::move(entry));
				}
			}
		}
		else
		{
			_subscriberList.Clear();
			_subscriberList.ShrinkToFit();
			_pendingUnsubAll = false;
		}

		_pendingUnsubscribe.Clear();
		_pendingUnsubscribe.ShrinkToFit();
		_pendingSubscribe.Clear();
		_pendingSubscribe.ShrinkToFit();
	}

}