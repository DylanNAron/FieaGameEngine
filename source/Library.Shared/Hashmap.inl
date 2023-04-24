#include "Hashmap.h"

namespace FieaGameEngine
{
#pragma region Iterator
	template<typename TKey, typename TData, typename HashFunctor>
	inline Hashmap<TKey, TData, HashFunctor>::Iterator::Iterator(Hashmap& container, typename Vector<chain_type>::Iterator bucketIt, typename chain_type::Iterator chainIt) :
		_container{ &container }, _bucketIt{ bucketIt }, _chainIt{ chainIt }
	{
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline std::pair<const TKey, TData>& Hashmap<TKey, TData, HashFunctor>::Iterator::operator*() const
	{
		if (_container == nullptr )
		{
			throw std::runtime_error("Invalid index:  empty iterator!");
		}

		return *_chainIt;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename inline Hashmap<TKey, TData, HashFunctor>::Iterator& Hashmap<TKey, TData, HashFunctor>::Iterator::operator++()
	{
		
		if (_container == nullptr)
		{
			throw std::runtime_error("Iterator is not associated");
		}


		++_chainIt;
		if (_chainIt == (*_bucketIt).end())
		{
			++_bucketIt;
			while (_bucketIt != _container->_map.end() && (*_bucketIt).Size() == 0)
			{
				++_bucketIt;
			}

			if (_bucketIt != _container->_map.end())
			{
				_chainIt = (*_bucketIt).begin();
			}
		}
		
		return *this;

	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename inline Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::Iterator::operator++(int)
	{
		Iterator iterator = *this;
		operator++();
		return iterator;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline bool Hashmap<TKey, TData, HashFunctor>::Iterator::operator!=(const Iterator& other) const
	{
		if (_container == other._container)
		{
			return (_bucketIt != other._bucketIt && _chainIt != other._chainIt);
		}

		return true;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline bool Hashmap<TKey, TData, HashFunctor>::Iterator::operator==(const Iterator& other) const
	{
		return !(*this != other);
	}

#pragma endregion Iterator


#pragma region ConstIterator
	template<typename TKey, typename TData, typename HashFunctor>
	inline Hashmap<TKey, TData, HashFunctor>::ConstIterator::ConstIterator(const Hashmap& container, typename Vector<chain_type>::ConstIterator bucketIt, typename chain_type::ConstIterator chainIt) :
		_container{ &container }, _bucketIt{ bucketIt }, _chainIt{ chainIt }
	{
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline Hashmap<TKey, TData, HashFunctor>::ConstIterator::ConstIterator(const Iterator& other) :
		_container{ other._container }, _bucketIt{ other._bucketIt }, _chainIt{ other._chainIt }
	{
	}


	template<typename TKey, typename TData, typename HashFunctor>
	inline const std::pair<const TKey, TData>& Hashmap<TKey, TData, HashFunctor>::ConstIterator::operator*() const
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("Invalid index:  empty ConstIterator!");
		}

		return *_chainIt;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename inline Hashmap<TKey, TData, HashFunctor>::ConstIterator& Hashmap<TKey, TData, HashFunctor>::ConstIterator::operator++()
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("ConstIterator is not associated");
		}

		++_chainIt;
		if (_chainIt == (*_bucketIt).end())
		{
			++_bucketIt;
			_chainIt = (*_bucketIt).begin();
		}
		return *this;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename inline Hashmap<TKey, TData, HashFunctor>::ConstIterator Hashmap<TKey, TData, HashFunctor>::ConstIterator::operator++(int)
	{
		ConstIterator ConstIterator = *this;
		operator++();
		return ConstIterator;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline bool Hashmap<TKey, TData, HashFunctor>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		if (_container == other._container)
		{
			return (_bucketIt != other._bucketIt && _chainIt != other._chainIt);
		}

		return true;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline bool Hashmap<TKey, TData, HashFunctor>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return !(*this != other);
	}

#pragma endregion ConstIterator


	template<typename TKey, typename TData, typename HashFunctor>
	inline Hashmap<TKey, TData, HashFunctor>::Hashmap(size_type size)
	{
		while (size > 0)
		{
			_map.PushBack(chain_type{});
			--size;
			++_buckets;
		}
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline Hashmap<TKey, TData, HashFunctor>::Hashmap(std::initializer_list<std::pair<TKey, TData>> list) :
		Hashmap(list.size())
	{
		for (auto& pair : list)
		{
			Insert(pair);
		}

	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline TData& Hashmap<TKey, TData, HashFunctor>::operator[](const TKey& key)
	{
		HashFunctor hash;
		size_type hashedKey = hash(key) % _buckets;

		typename Vector<chain_type>::Iterator bucketIt = _map.begin();
		bucketIt += hashedKey;

		SList<value_type>& chain = *bucketIt;

		typename SList<value_type>::Iterator chainIt = chain.begin();
		if (chain.isEmpty())
		{
			throw std::runtime_error("Key is not present");
		}

		while (chainIt != chain.end() && (*chainIt).first != key)
		{
			++chainIt;
		}

		if (chainIt == chain.end())
		{
			throw std::runtime_error("Key is not present");
		}

		return (*chainIt).second;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename inline Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::Find(const TKey& key)
	{
		HashFunctor hash;
		size_type hashedKey = hash(key) % _buckets;
		
		typename Vector<chain_type>::Iterator bucketIt = _map.begin();
		bucketIt += hashedKey;

		SList<value_type>& chain = *bucketIt;

		typename SList<value_type>::Iterator chainIt = chain.begin();
		if (chain.isEmpty())
		{
			return end();
		}

		while (chainIt!=chain.end() && (*chainIt).first != key)
		{
			++chainIt;
		}

		if (chainIt == chain.end())
		{
			return end();
		}

		return Iterator(*this, bucketIt, chainIt);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename inline Hashmap<TKey, TData, HashFunctor>::ConstIterator Hashmap<TKey, TData, HashFunctor>::Find(const TKey& key) const
	{
		HashFunctor hash;
		size_type hashedKey = hash(key) % _buckets;

		typename Vector<chain_type>::ConstIterator bucketIt = _map.begin();
		bucketIt += hashedKey;

		const SList<value_type>& chain = *bucketIt;

		typename SList<value_type>::ConstIterator chainIt = chain.begin();
		if (chain.isEmpty())
		{
			return end();
		}

		while (chainIt != chain.end() && (*chainIt).first != key)
		{
			++chainIt;
		}

		if (chainIt == chain.end())
		{
			return end();
		}

		return ConstIterator(*this, bucketIt, chainIt);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline std::pair<typename Hashmap<TKey, TData, HashFunctor>::Iterator, bool> Hashmap<TKey, TData, HashFunctor>::Insert(const value_type& pair)
	{
		HashFunctor hash;
		size_type hashedKey = hash(pair.first) % _buckets;

		typename Vector<chain_type>::Iterator bucketIt = _map.begin();
		bucketIt += hashedKey;

		Iterator iteratorFound = Find(pair.first);

		if (iteratorFound == end())
		{
			SList<value_type>& chain = *bucketIt;
			typename SList<value_type>::Iterator chainIt = chain.PushBack(pair);
			++_population;
			return std::make_pair(Iterator(*this, bucketIt, chainIt), true);
		}
		else
		{
			return std::make_pair(iteratorFound, false);
		}
	}


	template<typename TKey, typename TData, typename HashFunctor>
	inline std::pair<typename Hashmap<TKey, TData, HashFunctor>::Iterator, bool> Hashmap<TKey, TData, HashFunctor>::Insert(value_type&& pair)
	{
		HashFunctor hash;
		size_type hashedKey = hash(pair.first) % _buckets;

		typename Vector<chain_type>::Iterator bucketIt = _map.begin();
		bucketIt += hashedKey;

		Iterator iteratorFound = Find(pair.first);

		if (iteratorFound == end())
		{
			SList<value_type>& chain = *bucketIt;
			typename SList<value_type>::Iterator chainIt = chain.PushBack(std::move(pair));
			++_population;
			return std::make_pair(Iterator(*this, bucketIt, chainIt), true);
		}
		else
		{
			return std::make_pair(iteratorFound, false);
		}
	}


	template<typename TKey, typename TData, typename HashFunctor>
	inline void Hashmap<TKey, TData, HashFunctor>::Remove(const TKey& key)
	{
		
		HashFunctor hash;
		size_type hashedKey = hash(key) % _buckets;

		typename Vector<chain_type>::Iterator bucketIt = _map.begin();
		bucketIt += hashedKey;

		SList<value_type>& chain = *bucketIt;

		typename SList<value_type>::Iterator chainIt = chain.begin();
		if (chain.isEmpty())
		{
			return;
		}

		Iterator foundIt = Find(key);

		if (chain.Remove((*foundIt)))
		{
			--_population;
		}

	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline void Hashmap<TKey, TData, HashFunctor>::Clear() noexcept
	{
		for (auto& chain : _map)
		{
			chain.Clear();
		}
		_population = 0;

	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline void Hashmap<TKey, TData, HashFunctor>::Rehash(size_type size)
	{
		Hashmap<TKey, TData, HashFunctor> rehashedMap{ size };
		for (Iterator position = begin(); position != end(); ++position)
		{
			rehashedMap.Insert(*position);
		}
		*this = rehashedMap;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline size_t Hashmap<TKey, TData, HashFunctor>::Size() const
	{
		return _population;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline size_t Hashmap<TKey, TData, HashFunctor>::Buckets() const
	{
		return _buckets;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline bool Hashmap<TKey, TData, HashFunctor>::ContainsKey(const TKey& key) const
	{
		return (Find(key) != end());
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline TData& Hashmap<TKey, TData, HashFunctor>::At(const TKey& key)
	{
		HashFunctor hash;
		size_type hashedKey = hash(key) % _buckets;

		typename Vector<chain_type>::Iterator bucketIt = _map.begin();
		bucketIt += hashedKey;

		SList<value_type>& chain = *bucketIt;

		typename SList<value_type>::Iterator chainIt = chain.begin();
		if (chain.isEmpty())
		{
			throw std::runtime_error("Key is not present");
		}

		while (chainIt != chain.end() && (*chainIt).first != key)
		{
			++chainIt;
		}

		if (chainIt == chain.end())
		{
			throw std::runtime_error("Key is not present");
		}

		return (*chainIt).second;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline const TData& Hashmap<TKey, TData, HashFunctor>::At(const TKey& key) const
	{
		auto position = Find(key);
		if (position == end())
		{
			throw std::runtime_error("Key is not present");
		}

		return (*position).second;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename inline Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::begin()
	{
		typename Vector<chain_type>::Iterator bucketIt = _map.begin();

		while (bucketIt != _map.end() && (*bucketIt).Size() == 0 )
		{
			++bucketIt;
		}

		Hashmap::Iterator it(*this, bucketIt, (*bucketIt).begin());
		return it;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename inline Hashmap<TKey, TData, HashFunctor>::ConstIterator Hashmap<TKey, TData, HashFunctor>::begin() const
	{
		typename Vector<chain_type>::ConstIterator bucketIt = _map.begin();

		while (bucketIt != _map.end() && (*bucketIt).Size() == 0)
		{
			++bucketIt;
		}

		Hashmap::ConstIterator it(*this, bucketIt, (*bucketIt).cbegin());
		return it;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename inline Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::end()
	{
		return { *this, _map.end(), { } };
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename inline Hashmap<TKey, TData, HashFunctor>::ConstIterator Hashmap<TKey, TData, HashFunctor>::end() const
	{
		return { *this, _map.end(), { } };
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename inline Hashmap<TKey, TData, HashFunctor>::ConstIterator Hashmap<TKey, TData, HashFunctor>::cbegin() const
	{
		typename Vector<chain_type>::ConstIterator bucketIt = _map.begin();

		while (bucketIt != _map.end() && (*bucketIt).Size() == 0)
		{
			++bucketIt;
		}

		Hashmap::ConstIterator it(*this, bucketIt, (*bucketIt).begin());
		return it;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename inline Hashmap<TKey, TData, HashFunctor>::ConstIterator Hashmap<TKey, TData, HashFunctor>::cend() const
	{
		typename Vector<chain_type>::ConstIterator bucket = _map.end();
		typename chain_type::Iterator chain{};
		Hashmap::ConstIterator it(*this, bucket, chain);
		return it;
	}


}
