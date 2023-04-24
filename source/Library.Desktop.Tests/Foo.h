#pragma once
#include <cstdint>
#include <RTTI.h>
#include "Factory.h"
#include "Hashmap.h"
#include "gsl/gsl"

namespace UnitTests
{
	class Foo final : public FieaGameEngine::RTTI
	{
		RTTI_DECLARATIONS(Foo, FieaGameEngine::RTTI);

	public:
		explicit Foo(std::int32_t data = 0);
		Foo(const Foo& rhs);
		Foo(Foo&& rhs) noexcept;
		Foo& operator=(const Foo& rhs);
		Foo& operator=(Foo&& rhs) noexcept;
		virtual ~Foo();
		bool operator==(const Foo& rhs) const;
		bool operator!=(const Foo& rhs) const;
		std::int32_t Data() const;
		void SetData(std::int32_t data);
		std::string ToString() const override;
	private:
		std::int32_t* _data;
	};




}

using namespace UnitTests;
namespace FieaGameEngine
{
	ConcreteFactory(Foo, FieaGameEngine::RTTI);
}


//Macro Expands to ...
// 
//namespace FieaGameEngine
//{
//	class FooFactory : public Factory<RTTI>
//	{
//	public:
//		FooFactory() :_className( std::string("Foo") ) {  }
//
//		~FooFactory() { }
//
//		const std::string& ClassName() const override { return _className; }
//
//		gsl::owner<RTTI*> Create() const override { return new UnitTests::Foo(); }
//
//	private:
//		std::string _className;
//	};
//
//}
