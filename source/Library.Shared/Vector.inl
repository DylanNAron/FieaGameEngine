#include "Vector.h"
#include "stdexcept"
namespace FieaGameEngine
{
#pragma region Iterator
	template<typename T>
	inline Vector<T>::Iterator::Iterator(const Vector<T>* container, const size_type position):
		 _position{position}, _container{ container }
	{
	}

	template<typename T>
	inline T& Vector<T>::Iterator::operator*() const
	{
		if (_container == nullptr || _position >= _container->_size)
		{
			throw std::runtime_error("Invalid index: checking end or empty iterator!");
		}

		return _container->_data[_position];
	}

	template<typename T>
	typename inline Vector<T>::Iterator& Vector<T>::Iterator::operator++()
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("Iterator is not associated");
		}

		++_position;
		return *this;
	}

	template<typename T>
	typename inline Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
	{
		Iterator iterator = *this;
		operator++();
		return iterator;
	}

	template<typename T>
	typename inline Vector<T>::Iterator& Vector<T>::Iterator::operator+=(const size_t& rhs)
	{
		_position += rhs;
		return *this;
	}

	template<typename T>
	typename inline Vector<T>::Iterator& Vector<T>::Iterator::operator--()
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("Iterator is not associated");
		}

		--_position;
		return *this;
	}

	template<typename T>
	typename inline Vector<T>::Iterator Vector<T>::Iterator::operator--(int)
	{
		Iterator iterator = *this;
		operator--();
		return iterator;
	}

	template<typename T>
	typename inline bool Vector<T>::Iterator::operator!=(const Iterator& other) const
	{/*
		if (_container == other._container)
		{
			return this->_position != other._position;
		}

		return true;*/

		return _container != other._container || _position != other._position;
	}

	template<typename T>
	typename inline bool Vector<T>::Iterator::operator==(const Iterator& other) const
	{
		return !(*this != other);
	}

#pragma endregion Iterator

#pragma region ConstIterator

	template<typename T>
	inline Vector<T>::ConstIterator::ConstIterator(const Vector<T>* container, const size_type position) :
		 _position{ position }, _container{ container }
	{
	}

	template<typename T>
	inline Vector<T>::ConstIterator::ConstIterator(const Iterator& other) :
		 _position{ other._position }, _container{ other._container }
	{
	}

	template<typename T>
	inline const T& Vector<T>::ConstIterator::operator*() const
	{
		if (_container == nullptr || _position >= _container->_size)
		{
			throw std::runtime_error("Invalid index: checking end or empty ConstIterator!");
		}

		return _container->_data[_position];

	}

	template<typename T>
	typename inline Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator++()
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("ConstIterator is not associated");
		}

		++_position;
		return *this;
	}

	template<typename T>
	typename inline Vector<T>::ConstIterator Vector<T>::ConstIterator::operator++(int)
	{
		ConstIterator ConstIterator = *this;
		operator++();
		return ConstIterator;
	}

	template<typename T>
	typename inline Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator+=(const size_t& rhs)
	{
		_position += rhs;
		return *this;
	}

	template<typename T>
	typename inline Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator--()
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("ConstIterator is not associated");
		}

		--_position;
		return *this;
	}

	template<typename T>
	typename inline Vector<T>::ConstIterator Vector<T>::ConstIterator::operator--(int)
	{
		ConstIterator ConstIterator = *this;
		operator--();
		return ConstIterator;
	}

	template<typename T>
	typename inline bool Vector<T>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		/*if (_container == other._container)
		{
			return this->_position != other._position;

		}

		return true;*/

		return _container != other._container || _position != other._position;

	}

	template<typename T>
	typename inline bool Vector<T>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return !(*this != other);
	}

#pragma endregion ConstIterator

	template<typename T>
	inline Vector<T>::Vector(std::initializer_list<T> list)
	{
		Reserve(list.size());
		for (auto& item : list)
		{
			PushBack(item);
		}
	}


	template<typename T>
	inline Vector<T>::~Vector()
	{
		Clear();
		ShrinkToFit();
	}

	template<typename T>
	inline Vector<T>& Vector<T>::operator=(const Vector& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			ShrinkToFit();
			_capacity = rhs._capacity;

			T* data = reinterpret_cast<T*>(malloc(rhs._size * sizeof(T)));
			assert(data != nullptr);
			_data = data;
			for (size_t i = 0; i < rhs._size; ++i)
			{
				PushBack(rhs[i]);
			}
		}
		return *this;
	}

	template<typename T>
	inline Vector<T>& Vector<T>::operator=(Vector&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Clear();
			ShrinkToFit();
			_capacity = std::forward<size_t>(rhs._capacity);
			_data = std::forward<T*>(rhs._data);
			_size = std::forward<size_t>(rhs._size);
			rhs._size = 0;
			rhs._capacity = 0;
			rhs._data = nullptr;
		}
		return *this;
	}

	template<typename T>
	inline Vector<T>::Vector(Vector&& rhs) noexcept :
		_size{ std::forward<size_t>(rhs._size) }, _capacity{ std::forward<size_t>(rhs._capacity) }, _data{ std::forward<T*>(rhs._data) }
	{
		rhs._size = 0;
		rhs._capacity = 0;
		rhs._data = nullptr;
	}

	template<typename T>
	inline Vector<T>::Vector(const Vector& rhs)
	{
		_capacity = rhs._capacity;

		T* data = reinterpret_cast<T*>(malloc(_capacity * sizeof(T)));
		assert(data != nullptr);
		_data = data;
		for (size_t i = 0; i < rhs._size; ++i)
		{
			PushBack(rhs[i]);
		}

	}

	template<typename T>
	inline T& Vector<T>::operator[](size_type pos)
	{
		if (pos >= _size)
		{
			throw std::runtime_error("Out of bounds");
		}
		return _data[pos];
	}

	template<typename T>
	inline const T& Vector<T>::operator[](size_type pos) const
	{
		if (pos >= _size)
		{
			throw std::runtime_error("Out of bounds");
		}
		return _data[pos];
	}

	template<typename T>
	inline T& Vector<T>::At(size_type pos)
	{
		if (pos < 0 || pos > _size)
		{
			throw std::runtime_error("Out of bounds");
		}
		return _data[pos];
	}

	template<typename T>
	inline const T& Vector<T>::At(size_type pos) const
	{
		if (pos < 0 || pos > _size)
		{
			throw std::runtime_error("Out of bounds");
		}
		return _data[pos];
	}

	template<typename T>
	inline void Vector<T>::PopBack()
	{
		if (_size == 0)
		{
			throw std::runtime_error("Empty Vector, nothing to popback");
		}

		(_data + _size-1)->~T();
		--_size;
	}

	template<typename T>
	inline bool Vector<T>::IsEmpty()
	{
		return _size == 0;
	}

	template<typename T>
	inline T& Vector<T>::Front()
	{
		if (_size == 0)
		{
			throw std::runtime_error("Empty Vector, nothing at Front");
		}
		return _data[0];
	}

	template<typename T>
	inline const T& Vector<T>::Front() const
	{
		if (_size == 0)
		{
			throw std::runtime_error("Empty Vector, nothing at Front");
		}
		return _data[0];
	}

	template<typename T>
	inline T& Vector<T>::Back()
	{
		if (_size == 0)
		{
			throw std::runtime_error("Empty Vector, nothing at Back");
		}
		return _data[_size-1];
	}

	template<typename T>
	inline const T& Vector<T>::Back() const
	{
		if (_size == 0)
		{
			throw std::runtime_error("Empty Vector, nothing at Back");
		}
		return _data[_size - 1];
	}

	template<typename T>
	inline void Vector<T>::PushBack(const_reference value, IncrementFunctor incrementFunctor)
	{
		if (_size + 1 > _capacity)
		{
			Reserve(incrementFunctor(_size, _capacity));
		}
		new (_data + _size++) T(value); 
	}

	template<typename T>
	inline void Vector<T>::PushBack(rvalue_reference value, IncrementFunctor incrementFunctor)
	{
		if (_size + 1 > _capacity)
		{
			Reserve(incrementFunctor(_size, _capacity));
		}
		new (_data + _size++) T(std::move(value));
	}

	template<typename T>
	inline std::size_t Vector<T>::Size() const
	{
		return _size;
	}

	template<typename T>
	inline std::size_t Vector<T>::Capacity() const
	{
		return _capacity;
	}

	template<typename T>
	typename inline Vector<T>::Iterator Vector<T>::begin()
	{
		Vector::Iterator it(this, 0);
		return it;
	}

	template<typename T>
	typename inline Vector<T>::ConstIterator Vector<T>::begin() const
	{
		Vector::ConstIterator it(this, 0);
		return it;
	}

	template<typename T>
	typename inline Vector<T>::Iterator Vector<T>::end()
	{
		Vector::Iterator it(this, _size);
		return it;
	}

	template<typename T>
	typename inline Vector<T>::ConstIterator Vector<T>::end() const
	{
		Vector::ConstIterator it(this, _size);
		return it;
	}

	template<typename T>
	typename inline Vector<T>::ConstIterator Vector<T>::cbegin() const
	{
		Vector::ConstIterator it(this, 0);
		return it;
	}

	template<typename T>
	typename inline Vector<T>::ConstIterator Vector<T>::cend() const
	{
		Vector::ConstIterator it(this, _size);
		return it;
	}

	template<typename T>
	inline void Vector<T>::Reserve(size_t capacity)
	{
		if (capacity > _capacity)
		{
			T* data = reinterpret_cast<T*>(realloc(_data, capacity * sizeof(T)));
			assert(data != nullptr);
			_data = data;
			_capacity = capacity;
		}
	}

	template<typename T>
	typename inline Vector<T>::Iterator Vector<T>::Find(const_reference data)
	{
		Vector::Iterator it(this, 0);
		while (it != this->end() && *it != data)
		{
			++it;
		}
		return it;
	}

	template<typename T>
	typename inline Vector<T>::ConstIterator Vector<T>::Find(const_reference data) const
	{
		Vector::ConstIterator it(this, 0);
		while (it != this->end() && *it != data)
		{
			++it;
		}
		return it;
	}

	template<typename T>
	inline void Vector<T>::Clear()
	{
		for (size_t i = 0; i < _size; ++i)
		{
			(_data + i)->~T();
		}
		_size = 0;
	}
	template<typename T>
	inline void Vector<T>::ShrinkToFit()
	{
		if (_size == 0)
		{
			free(_data);
			_data = nullptr;
		}
		else if (_capacity > _size)
		{
			T* data = reinterpret_cast<T*>(realloc(_data, _size * sizeof(T)));
			assert(data != nullptr);
			_data = data;
		}
		_capacity = _size;
	}

	template<typename T>
	inline bool Vector<T>::Remove(const_reference data)
	{
		Vector::Iterator itFound = Find(data);
		return Remove(itFound);
	}

	template<typename T>
	inline bool Vector<T>::Remove(const Iterator& iterator)
	{
		if (iterator == this->end())
		{
			return false;
		}


		(_data + iterator._position)->~T();
		memmove((_data + iterator._position), (_data + iterator._position + 1), sizeof(T) * (_size - iterator._position));
		--_size;

		return true;
	}

}