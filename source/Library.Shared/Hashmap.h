#pragma once
#include <cstddef>
#include <string>

#include "Vector.h"
#include "SList.h"
#include "DefaultHash.h"

/*
* Dylan Aron 1/31/23 - HashMap
*/

namespace FieaGameEngine
{
	/// <summary>
	/// Unordered Hashmap that implements chaining. Comprised of a vector or slists.
	/// </summary>
	/// <typeparam name="TKey">Key data type, first part of pair</typeparam>
	/// <typeparam name="TData">Data data type, second part of pair</typeparam>
	/// <typeparam name="HashFunctor">Hash Functor for determining the hash of a given key, can be user supplied or left defaulted</typeparam>
	template<typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	class Hashmap final
	{
	public:
		using key_type = TKey;
		using mapped_type = TData;
		using value_type = std::pair<const TKey, TData>;
		using chain_type = SList<value_type>;
		using size_type = std::size_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using rvalue_reference = value_type&&;

		using iterator_category = std::forward_iterator_tag;

		/// <summary>
		/// Iterator class used for forward traversal of hashmap
		/// </summary>
		class Iterator final
		{
			friend Hashmap;
			friend class ConstIterator;
		public:
			/// <summary>
			/// Default Constructor of Iterator
			/// </summary>
			Iterator() = default;
			/// <summary>
			/// Default Destructor of Iterator
			/// </summary>
			~Iterator() = default;
			/// <summary>
			/// Dereference operator of Iterator
			/// </summary>
			/// <returns>reference to the pair of key and data</returns>
			/// <exception>Thrown when empty iterator</exception>
			reference operator*() const;
			/// <summary>
			/// Preincrement operator
			/// </summary>
			/// <returns> Iterator reference </returns>
			/// <exception>Thrown when empty iterator</exception>
			Iterator& operator++();
			/// <summary>
			/// Postincrement operator
			/// </summary>
			/// <returns> Iterator </returns>
			/// <exception>Thrown when empty iterator</exception>
			Iterator operator++(int);
			/// <summary>
			/// Not equal comparison operator
			/// </summary>
			/// <param name="other">reference to the other Iterator we are comparing against</param>
			/// <returns>boolean</returns>
			bool operator!=(const Iterator& other) const;
			/// <summary>
			/// Equal comparison operator
			/// </summary>
			/// <param name="other">reference to the other Iterator we are comparing against</param>
			/// <returns>boolean</returns>
			bool operator==(const Iterator& other) const;
		private:
			/// <summary>
			/// Private Constructor of Iterator based on given Container, Bucket Iterator, and Chain Iterator. Used for our begin and end functions for Hashmap to construct Hashmap Iterator.
			/// </summary>
			/// <typeparam name="Container">Reference to the hashmap container to assign</typeparam>
			/// <typeparam name="bucketIt">Iterator of the buckets to assign</typeparam>
			/// <typeparam name="chainIt">Iterator of the specific chain to assign</typeparam>
			Iterator(Hashmap& container, typename Vector<chain_type>::Iterator bucketIt, typename chain_type::Iterator chainIt);
			
			Hashmap* _container{ nullptr };
			typename Vector<chain_type>::Iterator _bucketIt;
			typename SList<value_type>::Iterator _chainIt;
		};


		/// <summary>
		/// ConstIterator class used for forward traversal of hashmap
		/// </summary>
		class ConstIterator final
		{
			friend Hashmap;
		public:
			/// <summary>
			/// Default Constructor of Const Iterator
			/// </summary>
			ConstIterator() = default;
			/// <summary>
			/// Default Destructor of Const Iterator
			/// </summary>
			~ConstIterator() = default;
			/// <summary>
			/// Constructor of Const Iterator based on given Iterator Reference
			/// </summary>
			/// <param name="other">Reference to the other Iterator we are creating a const Iterator from</param name>
			/// <returns></returns>
			ConstIterator(const class Iterator& other);
			/// <summary>
			/// Dereference operator of Const Iterator
			/// </summary>
			/// <returns>reference to the pair of key and data</returns>
			/// <exception>Thrown when empty iterator</exception>
			const_reference operator*() const;
			/// <summary>
			/// Preincrement operator
			/// </summary>
			/// <returns> Const Iterator reference </returns>
			/// <exception>Thrown when empty iterator</exception>
			ConstIterator& operator++();
			/// <summary>
			/// Postincrement operator
			/// </summary>
			/// <returns> Const Iterator </returns>
			/// <exception>Thrown when empty iterator</exception>
			ConstIterator operator++(int);
			/// <summary>
			/// Not equal comparison operator
			/// </summary>
			/// <param name="other">reference to the other Const Iterator we are comparing against</param>
			/// <returns>boolean</returns>
			bool operator!=(const ConstIterator& other) const;
			/// <summary>
			/// Equal comparison operator
			/// </summary>
			/// <param name="other">reference to the other Const Iterator we are comparing against</param>
			/// <returns>boolean</returns>
			bool operator==(const ConstIterator& other) const;
		private:
			/// <summary>
			/// Private Constructor of Const Iterator based on given Container, Bucket Iterator, and Chain Iterator. Used for our begin/cbegin and end/cend and functions for Hashmap to construct Hashmap Const Iterator.
			/// </summary>
			/// <typeparam name="Container">Reference to the hashmap container to assign</typeparam>
			/// <typeparam name="bucketIt">Const Iterator of the buckets to assign</typeparam>
			/// <typeparam name="chainIt">Const Iterator of the specific chain to assign</typeparam>
			ConstIterator(const Hashmap& container, typename Vector<chain_type>::ConstIterator bucketIt, typename chain_type::ConstIterator chainIt);
			const Hashmap* _container{ nullptr };

			typename Vector<chain_type>::ConstIterator _bucketIt;
			typename SList<value_type>::ConstIterator _chainIt;
		};



		/// <summary>
		/// Constructer for hashmap based on given size
		/// </summary>
		/// <param name="size">Parameter for the size of the hashmap, which specifies the number of buckets for each chain. This is defaulted to 5.</param>
		explicit Hashmap(size_type size = 5);

		/// <summary>
		/// Hashmap constructor given an initializer list
		/// </summary>
		/// <typeparam name="list">initializer list to populate the hashmap with</typeparam>
		Hashmap(std::initializer_list<std::pair<TKey, TData>> list);

		/// <summary>
		///  takes a “key” argument of the appropriate type and which returns a reference to the TData part. Create an entry with the associated key, if one isn’t already in the hash map.
		/// </summary>
		/// <param name="key">Reference to a TKey</param>
		/// <returns>A Reference to our mapped type of TData</returns>
		/// <exception>Thrown when Key is not present</exception>
		mapped_type& operator[] (const TKey& key);
		
		/// <summary>
		/// Assignment operator
		/// </summary>
		/// <param name="rhs">Reference to the right hand side hashmap that we want to assign this to</param>
		/// <returns>Hashmap Reference</returns>
		Hashmap& operator=(const Hashmap& rhs) = default;
		/// <summary>
		/// Move assignment operator
		/// </summary>
		/// <param name="rhs &&">Rvalue reference to hashmap</param>
		/// <returns>Hashmap Reference</returns>
		Hashmap& operator=(Hashmap&& rhs) noexcept = default;
		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs && Hashmap"Rvalue reference to hashmap></param>
		/// <returns>Hashmap Reference</returns>
		Hashmap(Hashmap&&) noexcept = default;
		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="rhs">reference to const hashmap that we are constructing hashmap from</param>
		Hashmap(const Hashmap& rhs) = default;
		/// <summary>
		/// Destructor
		/// </summary>
		~Hashmap() = default;

		/// <summary>
		/// takes a “key” argument of the appropriate type (constant reference to TKey) and which returns an Iterator.
		/// </summary>
		/// <param name="key"></param>
		/// <returns>Iterator to the found key. If key is not found, we return end iterator</returns>
		Iterator Find(const TKey& key);

		/// <summary>
		/// takes a “key” argument of the appropriate type (constant reference to TKey) and which returns an Iterator.
		/// </summary>
		/// <param name="key"></param>
		/// <returns>Iterator to the found key. If key is not found, we return end iterator</returns>
		ConstIterator Find(const TKey& key) const;

		/// <summary>
		/// takes an “entry” argument of the appropriate type (constant reference to PairType) and which returns an Iterator. If the table already contains an entry with a key that matches the key of the given entry, then do not modify the entry. Simply return the iterator of the found key.
		/// </summary>
		/// <param name="pair"></param>
		/// <returns>pair of Iterator pointing to the insertion position, and boolean of successful iteration</returns>
		std::pair<Iterator, bool> Insert(const value_type& pair);

		/// <summary>
		/// takes an Rvalue “entry” argument of the appropriate type (constant reference to PairType) and which returns an Iterator. If the table already contains an entry with a key that matches the key of the given entry, then do not modify the entry. Simply return the iterator of the found key.
		/// </summary>
		/// <param name="pair"></param>
		/// <returns>pair of Iterator pointing to the insertion position, and boolean of successful iteration</returns>
		std::pair<Iterator, bool> Insert(value_type&& pair);

		/// <summary>
		/// takes a “key” argumentand which returns nothing. It should remove the matching entry, if it exists, otherwise it should do nothing.
		/// </summary>
		/// <param name="key">Key to find and remove</param>
		void Remove(const TKey& key);

		/// <summary>
		/// empties the table and deletes any memory it allocated.
		/// </summary>
		void Clear() noexcept;

		/// <summary>
		/// Rehash the hashmap to the given size. Reinsert all previous entries into hashmap of new size.
		/// </summary>
		/// <typeparam name="size">New size to rehash our hashmap to</typeparam>
		void Rehash(size_type size);

		/// <summary>
		/// reports the population of the table, as an unsigned integer.
		/// </summary>
		/// <returns>size type of the population</returns>
		size_type Size() const;

		/// <summary>
		/// Gets the total amount of buckets available in the hashmap
		/// </summary>
		/// <returns>size type of number of buckets</returns>
		size_type Buckets() const;

		/// <summary>
		/// returns a Boolean indicating the presence of a key within the hash map.
		/// </summary>
		/// <param name="key">key to look if is contained in the hashmap</param>
		/// <returns>Boolean for if key contained</returns>
		bool ContainsKey(const TKey& key) const;

		/// <summary>
		/// returns a TData reference at the given key
		/// </summary>
		/// <param name="key">Key to search for in hashmap</param>
		/// <returns>mapped_type of TData reference</returns>
		/// <exception>Thrown when Key is not present</exception>
		mapped_type& At(const TKey& key);
		/// <summary>
		/// returns a TData reference at the given key
		/// </summary>
		/// <param name="key">Key to search for in hashmap</param>
		/// <returns>mapped_type of TData reference</returns>
		/// <exception>Thrown when Key is not present</exception>
		const mapped_type& At(const TKey& key) const;

		
		/// <summary>
		/// returns the iterator to the begin of Hashmap
		/// </summary>
		/// <returns>Iterator pointing to start of hashmap</returns>
		Hashmap::Iterator begin();
		/// <summary>
		/// return the const iterator to begin of Hashmap
		/// </summary>
		/// <returns>ConstIterator pointing to start of hashmap</returns>
		Hashmap::ConstIterator begin() const;
		/// <summary>
		/// returns iterator pointing past the end of Hashmap
		/// </summary>
		/// <returns>iterator pointing to end of hashmap</returns>
		Hashmap::Iterator end();
		/// <summary>
		/// returns const iterator pointing past the end of Hashmap
		/// </summary>
		/// <returns>const iterator pointing to end of hashmap</returns>
		Hashmap::ConstIterator end() const;
		/// <summary>
		/// specifically returns a ConstIterator to front of Hashmap
		/// </summary>
		/// <returns>const iterator pointing to start of hashmap</returns>
		Hashmap::ConstIterator cbegin() const;
		/// <summary>
		/// specifically returns a ConstIterator past end of Hashmap
		/// </summary>
		/// <returns>const iterator pointing to end of hashmap</returns>
		Hashmap::ConstIterator cend() const;

	private:
		
		Vector<chain_type> _map{ };
		size_type _population{ 0 };
		size_type _buckets{ 0 };


	};


}

#include "Hashmap.inl"