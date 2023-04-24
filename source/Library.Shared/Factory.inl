#pragma once
#include "Factory.h"

namespace FieaGameEngine
{
	
	template<typename T>
	inline const Factory<T>* Factory<T>::Find(const std::string& className)
	{
		auto iterator = _factories.Find(className);
		if (iterator == _factories.end())
		{
			return nullptr;
		}

		return (*iterator).second.get();
	}

	template<typename T>
	gsl::owner<T*> Factory<T>::Create(const std::string& className)
	{
		auto factoryFound = Find(className);
		if (factoryFound == nullptr)
		{
			return nullptr;
		}
		
		return factoryFound->Create();
	}

	template<typename T>
	inline void Factory<T>::Add(std::unique_ptr<Factory<T>> factory)
	{
		_factories.Insert(std::make_pair(factory->ClassName(), std::move(factory)));
	}

	template<typename T>
	inline void Factory<T>::Remove(std::unique_ptr<Factory<T>> factory)
	{
		_factories.Remove(factory->ClassName());
	}
}