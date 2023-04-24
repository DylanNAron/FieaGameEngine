#pragma once
#include "Hashmap.h"
#include "gsl/gsl"

namespace FieaGameEngine
{
	/// <summary>
	/// Factory class to implement the abstract factory design pattern. ConcreteFactories will be stored in the static "FactoryManager" for easy creation of objects at runtime.
	/// </summary>
	/// <typeparam name="T"> T is the templated product type</typeparam>
	template<typename T>
	class Factory
	{
	public:

		/// <summary>
		/// Given a class name, return the associated concrete factory. 
		/// </summary>
		/// <param name="className">class name for the product</param>
		/// <returns>Factory ptr for associated product</returns>
		static const Factory* Find(const std::string& className);

		/// <summary>
		///  Given a class name (string), return a new object of that type.
		/// </summary>
		/// <param name="className">class name for the product</param>
		/// <returns>Unique pointer to newly created product</returns>
		static gsl::owner<T*> Create(const std::string& className);

		/// <summary>
		///  Return the address of a concrete product associated with this concrete factory class. 
		/// </summary>
		/// <returns>Unique pointer to a new created concrete product</returns>
		virtual gsl::owner<T*> Create() const = 0;

		/// <summary>
		/// Return a string representing the name of the class the factory instantiates.
		/// </summary>
		/// <returns>String of the class name for products</returns>
		virtual const std::string& ClassName() const = 0;

		Factory() = default;
		Factory(const Factory&) = delete;
		Factory(Factory&&) = delete;
		Factory& operator=(const Factory&) = delete;
		Factory& operator=(Factory&&) = delete;
		virtual ~Factory<T>() = default;

		/// <summary>
		/// Add unique pointer factory to the static factories hashmap. User must add factories they wish to use.
		/// </summary>
		/// <typeparam name="factory">pointer to a factory to be added</typeparam>
		static void Add(std::unique_ptr<Factory<T>> factory);

		/// <summary>
		/// Remove unique pointer factory from the static factories hashmap.
		/// </summary>
		/// <typeparam name="factory">pointer to a factory to be removed</typeparam>
		static void Remove(std::unique_ptr<Factory<T>> factory);


	private:
		inline static Hashmap<std::string, std::unique_ptr<const Factory<T>>> _factories;
	};

#define ConcreteFactory(ConcreteProductType, AbstractProductType)													\
		class ConcreteProductType ## Factory : public Factory<AbstractProductType>	{								\
	public:																											\
		ConcreteProductType ## Factory() : _className(#ConcreteProductType) { }										\
		~ ## ConcreteProductType ## Factory() {  }																	\
		const std::string& ClassName() const override { return _className; }										\
		gsl::owner<AbstractProductType*> Create() const override { return new ConcreteProductType(); }				\
	private:																										\
		std::string _className;																						\
	};			

}

#include "Factory.inl"