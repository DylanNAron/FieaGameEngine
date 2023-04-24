#include "SList.h"

namespace FieaGameEngine
{
	//Node
	template<typename T>
	inline SList<T>::Node::Node(const T& data, Node* next) :
		Data(data), nextNode(next)
	{
	}

	template<typename T>
	inline SList<T>::Node::Node(T&& data, Node* next) :
		Data(std::move(data)), nextNode(next)
	{
	}

	template<typename T>
	inline SList<T>::Iterator::Iterator(const SList* container, Node* node) :
		_container{ container }, _node{ node }
	{
	}

	template<typename T>
	inline SList<T>::ConstIterator::ConstIterator(const SList* container, Node* node) :
		_container{ container }, _node{ node }
	{
	}
	
	template<typename T>
	inline SList<T>::ConstIterator::ConstIterator(const Iterator& other) :
		_container{ other._container }, _node{ other._node }
	{
	}

#pragma region Iterator Operators
	template<typename T>
	inline T& SList<T>::Iterator::operator*() const
	{
		if (this->_node == nullptr)
		{
			throw std::runtime_error("Nullptr, checking end!");
		}
		return _node->Data;
	}

	template<typename T>
	inline const T& SList<T>::ConstIterator::operator*() const
	{
		if (this->_node == nullptr)
		{
			throw std::runtime_error("Nullptr, checking end!");
		}
		return _node->Data;
	}
	
	template<typename T>
	typename inline SList<T>::Iterator& SList<T>::Iterator::operator++()
	{
		if (_node == nullptr)
		{
			throw std::runtime_error("Iterator is not associated");
		}

		_node = _node->nextNode;
		return *this;
	}

	template<typename T>
	typename inline SList<T>::ConstIterator& SList<T>::ConstIterator::operator++()
	{
		if (_node == nullptr)
		{
			throw std::runtime_error("Iterator is not associated");
		}

		_node = _node->nextNode;
		return *this;
	}

	template<typename T>
	typename inline SList<T>::Iterator SList<T>::Iterator::operator++(int)
	{
		Iterator iterator = *this;
		operator++();
		return iterator;
	}

	template<typename T>
	typename inline SList<T>::ConstIterator SList<T>::ConstIterator::operator++(int)
	{
		ConstIterator iterator = *this;
		operator++();
		return iterator;
	}

	template<typename T>
	inline bool SList<T>::Iterator::operator!=(const SList<T>::Iterator& other) const
	{
		if (_container == other._container)
		{
			return this->_node != other._node;
		}

		return true;
	}

	template<typename T>
	inline bool SList<T>::ConstIterator::operator!=(const SList<T>::ConstIterator& other) const
	{
		if (_container == other._container)
		{
			return this->_node != other._node;
		}

		return true;
	}

	template<typename T>
	inline bool SList<T>::Iterator::operator==(const SList<T>::Iterator& other) const
	{
		return !(*this != other);
	}

	template<typename T>
	inline bool SList<T>::ConstIterator::operator==(const SList<T>::ConstIterator& other) const
	{
		return !(*this != other);
	}

#pragma endregion Iterator Operators

	template<typename T>
	typename inline SList<T>::Iterator SList<T>::begin()
	{
		SList<T>::Iterator it(this, _headNode);
		return it;
	}

	template<typename T>
	typename inline SList<T>::ConstIterator SList<T>::begin() const
	{
		SList<T>::ConstIterator it(this, _headNode);
		return it;
	}

	template<typename T>
	typename inline SList<T>::ConstIterator SList<T>::cbegin() const
	{
		SList<T>::ConstIterator it(this, _headNode);
		return it;
	}
	
	template<typename T>
	typename inline SList<T>::Iterator SList<T>::end()
	{
		SList<T>::Iterator it(this, _tailNode->nextNode);
		return it;
	}

	template<typename T>
	typename inline SList<T>::ConstIterator SList<T>::end() const
	{
		SList<T>::ConstIterator it(this, _tailNode->nextNode);
		return it;
	}

	template<typename T>
	typename inline SList<T>::ConstIterator SList<T>::cend() const
	{
		SList<T>::ConstIterator it(this, _tailNode->nextNode);
		return it;
	}

	template<typename T>
	inline void SList<T>::InsertAfter(T data, SList<T>::Iterator iterator)
	{
		//check same container
		if (iterator._container != this)
		{
			throw std::runtime_error("Iterators are not from the same container");
		}

		//if points to end (just push back!)
		if (iterator._node == nullptr)
		{
			this->PushBack(data);
		}
		else
		{
			SList<T>::Iterator currentIt(this, _headNode);
			while (currentIt != iterator)
			{
				++currentIt;
			}
			Node* nextNode = currentIt._node->nextNode;
			currentIt._node->nextNode = new Node{ data, nextNode };
		}
	}

	template<typename T>
	typename inline SList<T>::Iterator SList<T>::Find(const T& value)
	{
		SList<T>::Iterator currentIt(this, _headNode);
		while (currentIt != this->end() && *currentIt != value)
		{
			++currentIt;
		}
		return currentIt;
	}

	template<typename T>
	typename inline SList<T>::ConstIterator SList<T>::Find(const T& value) const
	{
		SList<T>::ConstIterator currentIt(this, _headNode);
		while (currentIt != this->end() && *currentIt != value)
		{
			++currentIt;
		}
		return currentIt;
	}

	template<typename T>
	inline bool SList<T>::Remove(const T& value)
	{
		SList<T>::Iterator foundValueIt = Find(value);
		if (foundValueIt == this->end())
		{
			return false;
		}
		else
		{
			if (foundValueIt._node->nextNode == nullptr)
			{
				PopBack();
			}
			else if (foundValueIt._node == _headNode)
			{
				PopFront();
			}
			else
			{
				SList<T>::Iterator prevIterator(this, _headNode);
				while (prevIterator._node->nextNode != foundValueIt._node)
				{
					++prevIterator;
				}
				prevIterator._node->nextNode = foundValueIt._node->nextNode;
				foundValueIt._node->nextNode = nullptr;
				delete foundValueIt._node;
				--_size;
			}
			return true;
		}

	}

	//Slist
	template<typename T>
	SList<T>::~SList()
	{
		Clear();
	}

	template<typename T>
	SList<T>& SList<T>::operator=(const SList& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			Node* curNode = rhs._headNode;
			while (curNode != nullptr)
			{
				PushBack(curNode->Data);
				curNode = curNode->nextNode;
			}
		}
		return *this;
	}

	template<typename T>
	SList<T>& SList<T>::operator=(SList&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Clear();
			Node* curNode = rhs._headNode;
			while (curNode != nullptr)
			{
				PushBack(std::move(curNode->Data));
				curNode = curNode->nextNode;
			}
		}
		return *this;
	}

	template<typename T>
	SList<T>::SList(const SList& rhs)
	{
		Node* curNode = rhs._headNode;
		while (curNode != nullptr)
		{
			PushBack(curNode->Data);
			curNode = curNode->nextNode;
		}
	}

	template<typename T>
	SList<T>::SList(SList&& rhs) noexcept:
		_headNode(rhs._headNode), _tailNode(rhs._tailNode), _size(rhs._size)
	{
		rhs._headNode = nullptr;
		rhs._tailNode = nullptr;
		rhs._size = 0;
	}

	//insert given data into front of list as a new node
	template<typename T>
	typename SList<T>::Iterator SList<T>::PushFront(const T& data)
	{
		_headNode = new Node{ data, _headNode };
		if (_size == 0)
		{
			_tailNode = _headNode;
		}

		++_size;

		return Iterator(this, _headNode);

	}

	//Add given item into the back of list as new tail node
	template<typename T>
	typename SList<T>::Iterator SList<T>::PushBack(const T& data)
	{
		Node* oldTail = _tailNode;
		_tailNode = new Node{ data, nullptr };
		if (_size == 0)
		{
			_headNode = _tailNode;
		}
		else
		{
			oldTail->nextNode = _tailNode;
		}
		++_size;

		return Iterator(this, _tailNode);
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::PushBack(T&& data)
	{
		Node* oldTail = _tailNode;
		_tailNode = new Node{ std::move(data), nullptr };
		if (_size == 0)
		{
			_headNode = _tailNode;
		}
		else
		{
			oldTail->nextNode = _tailNode;
		}
		++_size;

		return Iterator(this, _tailNode);
	}

	//remove and delete the first item from the list and return a copy of its value
	template<typename T>
	void SList<T>::PopFront()
	{
		if (_size == 0)
		{
			throw std::runtime_error("Empty List");
		}
		
		if (_size == 1)
		{
			delete _headNode;
			_tailNode = nullptr;
			_headNode = nullptr;
		}
		else
		{
			Node* curNode = _headNode->nextNode;
			delete(_headNode);
			_headNode = curNode;
		}
		--_size;

	}

	//remove item from end of list and return copy of data, and also set new tail 
	template<typename T>
	void SList<T>::PopBack()
	{
		if (_size == 0)
		{
			throw std::runtime_error("Empty List");
		}
		
		if (_size == 1)
		{
			delete _tailNode;
			_tailNode = nullptr;
			_headNode = nullptr;
			--_size;
		}
		else
		{
			Node* curNode = _headNode;
			while (curNode->nextNode != _tailNode)
			{
				curNode = curNode->nextNode;
			}
			curNode->nextNode = nullptr;
			delete(_tailNode);
			_tailNode = curNode;
			--_size;
		}

	}

	// return boolean indicating whether list contains any items
	template<typename T>
	inline bool SList<T>::isEmpty() const
	{
		return(_size == 0);
	}

	// return the size (this runs in constant time because we increment/decrement on push/pop)
	template<typename T>
	inline std::size_t SList<T>::Size() const
	{
		return _size;
	}

	template<typename T>
	inline T& SList<T>::Front()
	{
		if (_size == 0)
		{
			throw std::runtime_error("list empty");
		}
		return _headNode->Data;
	}

	// return the first item in the list (head)
	template<typename T>
	const inline T& SList<T>::Front() const
	{
		if (_size == 0)
		{
			throw std::runtime_error("list empty");
		}
		return _headNode->Data;
	}

	// return the last item in the list (tail)
	template<typename T>
	const inline T& SList<T>::Back() const
	{
		if (_size == 0)
		{
			throw std::runtime_error("list empty");
		}
		return _tailNode->Data;
	}

	template<typename T>
	inline T& SList<T>::Back()
	{
		if (_size == 0)
		{
			throw std::runtime_error("list empty");
		}
		return _tailNode->Data;
	}

	//remove all items in the list and delete them
	template<typename T>
	void SList<T>::Clear()
	{
		Node* prev = _headNode;
		Node* temp = _headNode;
		while (temp != nullptr)
		{
			temp = prev->nextNode;
			delete prev;
			prev = temp;
		}
		_headNode = nullptr;
		_tailNode = nullptr;
		_size = 0;
	}
}