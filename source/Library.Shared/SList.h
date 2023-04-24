#pragma once
#include <cstdlib>

/*
* Dylan Aron 1/10/23
* Singly Linked List Template implementation
* 
* 
*/

namespace FieaGameEngine
{
	template<typename T>
	class SList final
	{
		struct Node
		{
			T Data;
			Node* nextNode{ nullptr };

			Node(const T& data, Node* next = nullptr);
			Node(T&& data, Node* next = nullptr);
		};

	public:
		using size_type = std::size_t;
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using rvalue_reference = value_type&&;

#pragma region Iterator
		/// <summary>
		/// Iterator class which allows for traversing through slist nodes
		/// </summary>
		class Iterator final
		{
			friend SList;
			friend class ConstIterator;
		public:
			Iterator() = default;
			reference operator*() const;
			Iterator& operator++(); //prefix
			Iterator operator++(int); //postfix
			bool operator!=(const Iterator& other) const;
			bool operator==(const Iterator& other) const;

		private:
			Iterator(const SList* container, Node* node = nullptr);

			Node* _node{ nullptr };
			const SList* _container{ nullptr };
		};
#pragma endregion Iterator

#pragma region ConstIterator
		/// <summary>
		/// Const Iterator class which allows for traversing slist
		/// </summary>
		class  ConstIterator final
		{
			friend SList;
		public:
			ConstIterator() = default;
			ConstIterator(const class Iterator& other);
			const_reference operator*() const;
			ConstIterator& operator++(); //prefix
			ConstIterator operator++(int); //postfix
			bool operator!=(const ConstIterator& other) const;
			bool operator==(const ConstIterator& other) const;

		private:
			ConstIterator(const SList* container, Node* node = nullptr);

			Node* _node{ nullptr };
			const SList* _container{ nullptr };
		};
#pragma endregion ConstIterator

		/// <summary>
		/// returns the iterator to the head of list
		/// </summary>
		/// <returns>Iterator</returns>
		SList::Iterator begin();
		/// <summary>
		/// return the const iterator to head of list
		/// </summary>
		/// <returns>ConstIterator</returns>
		SList::ConstIterator begin() const;
		/// <summary>
		/// returns iterator pointing past the tail of list
		/// </summary>
		/// <returns>iterator</returns>
		SList::Iterator end();
		/// <summary>
		/// returns const iterator pointing past the tail of list
		/// </summary>
		/// <returns>const iterator</returns>
		SList::ConstIterator end() const;

		/// <summary>
		/// specifically returns a ConstIterator to head of list
		/// </summary>
		/// <returns>const iterator</returns>
		SList::ConstIterator cbegin() const;
		/// <summary>
		/// specifically returns a ConstIterator past tail of list
		/// </summary>
		/// <returns>const iterator</returns>
		SList::ConstIterator cend() const;

		/// <summary>
		/// Append the given item after the item the given iterator points to
		/// </summary>
		/// <param name="data"></param>
		/// <param name="iterator"></param>
		void InsertAfter(T data, SList::Iterator iterator);
		/// <summary>
		/// finds the first iterator pointing to the given item. if not found returns end
		/// </summary>
		/// <param name="value"></param>
		/// <returns>iterator pointing to value or end</returns>
		SList::Iterator Find(const T& value);
		/// <summary>
		/// finds the first const iterator pointing to the given item. if not found returns end
		/// </summary>
		/// <param name="value"></param>
		/// <returns>const iterator pointing to value or end</returns>
		SList::ConstIterator Find(const T& value) const;
		/// <summary>
		/// Removes the item associated with given value while maintaining list. If value is not found does not cause harm
		/// </summary>
		/// <param name="value"></param>
		/// <returns>boolean based on success of removal</returns>
		bool Remove(const T& value);
		
		SList() = default;
		~SList();

		SList& operator=(const SList& rhs); 
		SList& operator=(SList&& rhs) noexcept; 
		SList(const SList& rhs); 
		SList(SList&& rhs) noexcept;

		Iterator PushFront(const T& data);
		Iterator PushBack(const T& data);
		Iterator PushBack(T&& data);
		void PopFront(); 
		void PopBack();

		bool isEmpty() const;

		[[nodiscard]] size_t Size() const;
		[[nodiscard]] T& Front();
		[[nodiscard]] const T& Front() const;
		[[nodiscard]] const T& Back() const;
		[[nodiscard]] T& Back();

		void Clear();

	private:
		size_t _size{ 0 };
		Node* _headNode{ nullptr };
		Node* _tailNode{ nullptr };

	};
	
}

#include "SList.inl"
