#pragma once
#include <cstddef>
#include <string>


/*
* Dylan Aron 2/1/23 HashFunctor
*/

namespace FieaGameEngine
{
	/// <summary>
	/// Default Hashfunctor used for our hashmap
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename TKey>
	class DefaultHash final
	{
	public:
		DefaultHash() = default;
		std::size_t operator()(const TKey& key) const;
	};
	
}
#include "DefaultHash.inl"