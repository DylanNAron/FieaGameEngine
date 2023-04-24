#include "DefaultHash.h"

namespace FieaGameEngine
{

	template<typename TKey>
	inline std::size_t DefaultHash<TKey>::operator()(const TKey& key) const
	{
		//const std::uint8_t* data = reinterpret_cast<const std::uint8_t*>(&key);
		const std::byte* data = reinterpret_cast<const std::byte*>(&key);
		size_t hash = 0;
		for (size_t index = 0; index < sizeof(TKey); ++index)
		{
			hash += static_cast<size_t>(data[index]);
		}
		return hash;
	}

	//specializations
	template<>
	class DefaultHash<std::string>
	{
	public:
		DefaultHash() = default;
		std::size_t operator()(const std::string& key) const
		{
			size_t hash = 0;
			for (size_t index = 0; index < key.length(); ++index)
			{
				hash += static_cast<size_t>(key[index]);
			}
			return hash;
		}
	};

	template<>
	class DefaultHash<char*>
	{
	public:
		DefaultHash() = default;
		std::size_t operator()(const char* key) const
		{
			size_t hash = 0;
			for (size_t index = 0; key[index] != '\0'; ++index)
			{
				hash += static_cast<size_t>(key[index]);
			}
			return hash;
		}
	};


}

