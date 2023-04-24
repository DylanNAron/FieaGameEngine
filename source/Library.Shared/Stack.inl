#pragma once
#include "Stack.h"

namespace FieaGameEngine
{

	template <typename T>
	inline void Stack<T>::Push(const_reference value)
	{
		_list.PushFront(value);
	}

	template<typename T>
	inline void Stack<T>::Push(rvalue_reference value)
	{
		_list.PushFront(std::move(value));
	}

	template<typename T>
	inline void Stack<T>::Pop()
	{
		_list.PopFront();
	}

	template<typename T>
	inline T& Stack<T>::Top()
	{
		return _list.Front();
	}

	template<typename T>
	inline const T& Stack<T>::Top() const
	{
		return _list.Front();
	}

	template<typename T>
	inline size_t Stack<T>::Size() const
	{
		return _list.Size();
	}

	template<typename T>
	inline bool Stack<T>::IsEmpty() const
	{
		return _list.Size() == 0;
	}

	template<typename T>
	inline void Stack<T>::Clear()
	{
		_list.Clear();
	}




}