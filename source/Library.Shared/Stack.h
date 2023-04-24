#pragma once
#include "SList.h"

namespace FieaGameEngine
{

	template <typename T>
	class Stack final
	{
	public:
		using size_type = std::size_t;
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using rvalue_reference = value_type&&;

		void Push(const_reference value);
		void Push(rvalue_reference value);
		void Pop();

		reference Top();
		const_reference Top() const;
		size_type Size() const;
		bool IsEmpty() const;

		void Clear();

	private:
		SList<value_type> _list;

	};

}

#include "Stack.inl"