#pragma once
#include "assert.h"
#include <cstdlib>


/* Dylan Aron 1/22/23
 * Vector templated dynamic array class
 * 
 */
namespace FieaGameEngine
{
	/// <summary>
	/// Vector Templated Dynamic Array Class
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class Vector final
	{
	public:
		using size_type = std::size_t;
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using rvalue_reference = value_type&&;

		using iterator_category = std::random_access_iterator_tag;

#pragma region Iterator
		/// <summary>
		/// Iterator class which allows for traversing through Vector
		/// </summary>
		class Iterator final
		{
			friend Vector;
			friend class ConstIterator;
		public:
			Iterator() = default;
			reference operator*() const;
			Iterator& operator++(); 
			Iterator operator++(int);
			Iterator& operator+=(const size_t& rhs);
			Iterator& operator--();
			Iterator operator--(int);
			bool operator!=(const Iterator& other) const;
			bool operator==(const Iterator& other) const;

		private:
			Iterator(const Vector<T>* container, const size_type position);

			size_type _position{ 0 };
			const Vector* _container{ nullptr };
		};
#pragma endregion Iterator

#pragma region ConstIterator
		/// <summary>
		/// Const Iterator class which allows for traversing Vector
		/// </summary>
		class  ConstIterator final
		{
			friend Vector;
		public:
			ConstIterator() = default;
			ConstIterator(const class Iterator& other);
			const_reference operator*() const;
			ConstIterator& operator+=(const size_t& rhs);
			ConstIterator& operator++(); 
			ConstIterator operator++(int);
			ConstIterator& operator--();
			ConstIterator operator--(int);
			bool operator!=(const ConstIterator& other) const;
			bool operator==(const ConstIterator& other) const;

		private:
			ConstIterator(const Vector<T>* container, const size_type position);

			size_type _position{ 0 };
			const Vector* _container{ nullptr };
		};
#pragma endregion ConstIterator

		/// <summary>
		/// Functor to provide to push back for reserve strategy based on a given multiplier to keep of the capacity
		/// </summary>
		class IncrementFunctor final
		{
		private:
			size_t _capacityMultiplier;
		public:
			IncrementFunctor(size_t multiplier) : _capacityMultiplier{ multiplier } 
			{
			}
			std::size_t operator()(std::size_t size, std::size_t capacity) const
			{
				//at minimum make capacity one more then size otherwise make capacity a multiple of the size by given multiplier
				size_t wantedCapacity = size * _capacityMultiplier;
				size_t incrementAmount = size + 1;
				if (capacity < wantedCapacity)
				{
					incrementAmount = wantedCapacity;
				}
				return incrementAmount;
			}
		};

		Vector( std::initializer_list<T> list);

		Vector() = default;
		~Vector();
		/// <summary>
		/// Assignment operator
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns>Vector Reference</returns>
		Vector& operator=(const Vector& rhs);
		/// <summary>
		/// Move assignment operator
		/// </summary>
		/// <param name="rhs &&"></param>
		/// <returns>Vector Reference</returns>
		Vector& operator=(Vector&& rhs) noexcept;
		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs && vector"></param>
		/// <returns>Vector</returns>
		Vector(Vector&&) noexcept;
		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="rhs"></param>
		Vector(const Vector& rhs);

		/// <summary>
		/// retrieve item at the given index. Throw an exception if the index is invalid.
		/// </summary>
		/// <param name="position"></param>
		/// <returns>reference to item at given index</returns>
		[[nodiscard]] reference operator[] (size_type pos);
		/// <summary>
		/// retrieve const item at the given index. Throw an exception if the index is invalid.
		/// </summary>
		/// <param name="position"></param>
		/// <returns>const reference to item at given index</returns>
		[[nodiscard]] const_reference operator[] (size_type pos) const;

		/// <summary>
		/// take an unsigned integer index and return a reference to the item at the given index. Throw an exception if the index is invalid
		/// </summary>
		/// <param name="pos"></param>
		/// <returns>reference</returns>
		[[nodiscard]] reference At(size_type pos);
		/// <summary>
		/// take an unsigned integer index and return a const reference to the item at the given index. Throw an exception if the index is invalid
		/// </summary>
		/// <param name="pos"></param>
		/// <returns>const reference</returns>
		[[nodiscard]] const_reference At(size_type pos) const;

		/// <summary>
		/// Remove the last item in the container, but should not reduce the capacity of the container.
		/// </summary>
		void PopBack();

		/// <summary>
		///  Return a bool indicating whether the list contains any items.
		/// </summary>
		/// <returns>Boolean</returns>
		[[nodiscard]] bool IsEmpty();

		/// <summary>
		/// return the first item in the container. 
		/// </summary>
		/// <returns>reference. </returns>
		[[nodiscard]] reference Front();
		/// <summary>
		/// return the first item in the container. 
		/// </summary>
		/// <returns>const reference</returns>
		[[nodiscard]] const_reference Front() const;
		/// <summary>
		/// return the last item in the container. 
		/// </summary>
		/// <returns>reference</returns>
		[[nodiscard]] reference Back();
		/// <summary>
		/// return the last item in the container. 
		/// </summary>
		/// <returns>const reference</returns>
		[[nodiscard]] const_reference Back() const;

		/// <summary>
		/// return the number of items in the container as an unsigned int. 
		/// </summary>
		/// <returns>unsigned int</returns>
		[[nodiscard]] size_type Size() const;
		/// <summary>
		/// return the number of items allocated within the container as an unsigned int.
		/// </summary>
		/// <returns>unsigned int</returns>
		[[nodiscard]] size_type Capacity() const;

		/// <summary>
		/// returns the iterator to the begin of Vector
		/// </summary>
		/// <returns>Iterator</returns>
		Vector::Iterator begin();
		/// <summary>
		/// return the const iterator to begin of Vector
		/// </summary>
		/// <returns>ConstIterator</returns>
		Vector::ConstIterator begin() const;
		/// <summary>
		/// returns iterator pointing past the end of Vector
		/// </summary>
		/// <returns>iterator</returns>
		Vector::Iterator end();
		/// <summary>
		/// returns const iterator pointing past the end of Vector
		/// </summary>
		/// <returns>const iterator</returns>
		Vector::ConstIterator end() const;
		/// <summary>
		/// specifically returns a ConstIterator to front of Vector
		/// </summary>
		/// <returns>const iterator</returns>
		Vector::ConstIterator cbegin() const;
		/// <summary>
		/// specifically returns a ConstIterator past end of Vector
		/// </summary>
		/// <returns>const iterator</returns>
		Vector::ConstIterator cend() const;

		/// <summary>
		/// append given item after the end of the list.  This must increase array capacity if necessary. 
		/// </summary>
		/// <param name="value"></param>
		void PushBack(const_reference value, IncrementFunctor incrementStrategy = IncrementFunctor{ 1 });

		/// <summary>
		/// append given Rvalue item after the end of the list.  This must increase array capacity if necessary. 
		/// </summary>
		/// <param name="value"></param>
		void PushBack(rvalue_reference value, IncrementFunctor incrementStrategy = IncrementFunctor{ 1 });

		/// <summary>
		/// Increases the capacity to given parameter, but does not shrink it
		/// </summary>
		/// <param name="capacity"></param>
		void Reserve(size_type capacity);

		/// <summary>
		///  take a const reference to an item and return an iterator pointing to the first item in the container that matches the argument. If no match found, return End. 
		/// </summary>
		/// <param name="data"></param>
		/// <returns>Iterator</returns>
		Vector::Iterator Find(const_reference data);
		/// <summary>
		///  take a const reference to an item and return a const iterator pointing to the first item in the container that matches the argument. If no match found, return End. 
		/// </summary>
		/// <param name="data"></param>
		/// <returns>Const Iterator</returns>
		Vector::ConstIterator Find(const_reference data) const;

		/// <summary>
		/// empty the container.
		/// </summary>
		void Clear();
		/// <summary>
		/// Reduce the capacity of the container to match its size;
		/// </summary>
		void ShrinkToFit();

		/// <summary>
		/// Remove the first item found that matches the given data. Return boolean if removed.
		/// </summary>
		/// <param name="data"></param>
		/// <returns>Boolean</returns>
		bool Remove(const_reference data);
		/// <summary>
		/// Remove the first item found that matches the given Iterator. Return boolean if removed.
		/// </summary>
		/// <param name="data"></param>
		/// <returns>Boolean</returns>
		bool Remove(const Iterator& iterator);

	private:
		T* _data{ nullptr };
		size_type _size{ 0 };
		size_type _capacity{ 0 };
		
	};

}

#include "Vector.inl"