#pragma once

#include "CppUnitTest.h"
#include "Foo.h"
#include "SList.h"
#include "Vector.h"
#include "Hashmap.h"
#include "Datum.h"
#include "Scope.h"
#include "AttributedFoo.h"
#include "JsonParseCoordinator.h"
#include "JsonParseTestHelper.h"
#include "JsonTableParseHelper.h"
#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"
#include "GameObject.h"
#include "World.h"

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<>
	inline std::wstring ToString<UnitTests::Foo>(const UnitTests::Foo& t)
	{
		RETURN_WIDE_STRING(t.Data());
	}

	template<>
	inline std::wstring ToString<UnitTests::Foo>(const UnitTests::Foo* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<UnitTests::Foo>(UnitTests::Foo* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::SList<UnitTests::Foo>::Iterator>(const FieaGameEngine::SList<UnitTests::Foo>::Iterator& t)
	{
		using namespace std::string_literals;
		std::wstring value;
		try
		{
			value = ToString(*t);
		}
		catch (const std::exception&)
		{
			value = L"end()"s;
		}
		return value;
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::SList<UnitTests::Foo>::ConstIterator>(const FieaGameEngine::SList<UnitTests::Foo>::ConstIterator& t)
	{
		using namespace std::string_literals;
		std::wstring value;
		try
		{
			value = ToString(*t);
		}
		catch (const std::exception&)
		{
			value = L"end()"s;
		}
		return value;
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Vector<UnitTests::Foo>::Iterator>(const FieaGameEngine::Vector<UnitTests::Foo>::Iterator& t)
	{
		using namespace std::string_literals;
		std::wstring value;
		try
		{
			value = ToString(*t);
		}
		catch (const std::exception&)
		{
			value = L"end()"s;
		}
		return value;
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Vector<UnitTests::Foo>::ConstIterator>(const FieaGameEngine::Vector<UnitTests::Foo>::ConstIterator& t)
	{
		using namespace std::string_literals;
		std::wstring value;
		try
		{
			value = ToString(*t);
		}
		catch (const std::exception&)
		{
			value = L"end()"s;
		}
		return value;
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Hashmap<UnitTests::Foo, UnitTests::Foo>::Iterator>(const FieaGameEngine::Hashmap<UnitTests::Foo, UnitTests::Foo>::Iterator& t)
	{
		using namespace std::string_literals;
		std::wstring value;
		try
		{
			value = ToString((*t).first.Data());
		}
		catch (const std::exception&)
		{
			value = L"end()"s;
		}
		return value;
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Hashmap<UnitTests::Foo, UnitTests::Foo>::ConstIterator>(const FieaGameEngine::Hashmap<UnitTests::Foo, UnitTests::Foo>::ConstIterator& t)
	{
		using namespace std::string_literals;
		std::wstring value;
		try
		{
			value = ToString((*t).first.Data());
		}
		catch (const std::exception&)
		{
			value = L"end()"s;
		}
		return value;
	}


	template<>
	inline std::wstring ToString<FieaGameEngine::Scope>(const FieaGameEngine::Scope& t)
	{
		RETURN_WIDE_STRING(&t);
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Scope>(const FieaGameEngine::Scope* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Scope>(FieaGameEngine::Scope* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<UnitTests::AttributedFoo>(const UnitTests::AttributedFoo& t)
	{
		t;
		using namespace std::string_literals;
		std::string str = t.ToString();
		std::wstring  value(str.begin(), str.end());

		RETURN_WIDE_STRING(value);
	}

	template<>
	inline std::wstring ToString<UnitTests::AttributedFoo>(const UnitTests::AttributedFoo* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<UnitTests::AttributedFoo>(UnitTests::AttributedFoo* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::GameObject>(const FieaGameEngine::GameObject& t)
	{
		t;
		using namespace std::string_literals;
		std::string str = t.ToString();
		std::wstring  value(str.begin(), str.end());

		RETURN_WIDE_STRING(value);
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::GameObject>(const FieaGameEngine::GameObject* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::GameObject>(FieaGameEngine::GameObject* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::JsonParseCoordinator>(FieaGameEngine::JsonParseCoordinator* t)
	{
		t;
		using namespace std::string_literals;
		std::wstring value;
		value = L"JsonParseCoordinator"s;
		return value;
	}

	template<>
	inline std::wstring ToString<std::shared_ptr<FieaGameEngine::JsonParseCoordinator::Wrapper>>(const std::shared_ptr<FieaGameEngine::JsonParseCoordinator::Wrapper>& t)
	{
		t;
		using namespace std::string_literals;
		std::wstring value;
		value = L"JsonParseCoordinator::Wrapper"s;
		return value;
	}

	template<>
	inline std::wstring ToString<std::shared_ptr<FieaGameEngine::IJsonParseHelper>>(const std::shared_ptr<FieaGameEngine::IJsonParseHelper>& t)
	{
		t;
		using namespace std::string_literals;
		std::wstring value;
		value = L"JsonParsing Helper"s;
		return value;
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::JsonParseTestHelper::Wrapper>(const FieaGameEngine::JsonParseTestHelper::Wrapper& t)
	{
		t;
		using namespace std::string_literals;
		std::string str = t.ToString();
		std::wstring  value(str.begin(), str.end());

		RETURN_WIDE_STRING(value);
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::JsonParseTestHelper::Wrapper>(const FieaGameEngine::JsonParseTestHelper::Wrapper* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::JsonParseTestHelper::Wrapper>(FieaGameEngine::JsonParseTestHelper::Wrapper* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::JsonTableParseHelper::Wrapper>(const FieaGameEngine::JsonTableParseHelper::Wrapper& t)
	{
		t;
		using namespace std::string_literals;
		std::string str = t.ToString();
		std::wstring  value(str.begin(), str.end());

		RETURN_WIDE_STRING(value);
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::JsonTableParseHelper::Wrapper>(const FieaGameEngine::JsonTableParseHelper::Wrapper* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::JsonTableParseHelper::Wrapper>(FieaGameEngine::JsonTableParseHelper::Wrapper* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<glm::vec4>(const glm::vec4& t)
	{
		std::string str = glm::to_string(t);
		std::wstring  value(str.begin(), str.end());

		RETURN_WIDE_STRING(value);

	}

	template<>
	inline std::wstring ToString<glm::mat4>(const glm::mat4& t)
	{
		std::string str = glm::to_string(t);
		std::wstring  value(str.begin(), str.end());

		RETURN_WIDE_STRING(value);

	}

	template<>
	inline std::wstring ToString<FieaGameEngine::World>(const FieaGameEngine::World& t)
	{
		RETURN_WIDE_STRING(&t);
	}

}