#pragma once

#include "CppUnitTest.h"
#include "Foo.h"
#include "Hashmap.h"

namespace FieaGameEngine
{
	template<>
	inline std::size_t DefaultHash<UnitTests::Foo>::operator()(const UnitTests::Foo& key) const
	{
		size_t hash = key.Data();
		return hash;
	}
}