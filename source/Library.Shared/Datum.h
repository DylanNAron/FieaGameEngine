#pragma once
#include "Hashmap.h"
#include "RTTI.h"
#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"
/*
* Dylan Aron - 2/7/23 
*/

namespace FieaGameEngine
{
	/// <summary>
	/// Forward Declaration of Scope class
	/// </summary>
	class Scope; 

	/// <summary>
	/// Datum class which stores values with a single given type. Each Datum object represents, in general, an array, and all of the elements in that array have the same type. 
	/// </summary>
	class Datum final
	{
	public:
		enum class DatumTypes
		{
			Unknown = 0,
			Integer,
			Float,
			Vector,
			Matrix,
			Table,
			String,
			Pointer
		};

		inline static const Hashmap<std::string, DatumTypes> DatumTypeStringMap
		{
			std::pair("unknown", DatumTypes::Unknown),
			std::pair("integer", DatumTypes::Integer),
			std::pair("float", DatumTypes::Float),
			std::pair("vector", DatumTypes::Vector),
			std::pair("matrix", DatumTypes::Matrix),
			std::pair("table", DatumTypes::Table),
			std::pair("string", DatumTypes::String),
			std::pair("pointer", DatumTypes::Pointer)
		};

		/// <summary>
		/// Construction of Datum that can be defaulted or set size / type
		/// </summary>
		Datum(size_t size = 0, DatumTypes type = DatumTypes::Unknown);

		/// <summary>
		/// Constructor via initializer list for Integer.
		/// </summary>
		/// <param name="list">Integer initializer list</param>
		Datum(std::initializer_list<int32_t> list);

		/// <summary>
		/// Constructor via initializer list for Float.
		/// </summary>
		/// <param name="list">Float initializer list</param>
		Datum(std::initializer_list<float> list);

		/// <summary>
		/// Constructor via initializer list for Vector.
		/// </summary>
		/// <param name="list">Vector initializer list</param>
		Datum(std::initializer_list<glm::vec4> list);

		/// <summary>
		/// Constructor via initializer list for Matrix.
		/// </summary>
		/// <param name="list">Matrix initializer list</param>
		Datum(std::initializer_list<glm::mat4> list);

		/// <summary>
		/// Constructor via initializer list for String.
		/// </summary>
		/// <param name="list">String initializer list</param>
		Datum(std::initializer_list<std::string> list);

		/// <summary>
		/// Constructor via initializer list for Pointer.
		/// </summary>
		/// <param name="list">Pointer initializer list</param>
		Datum(std::initializer_list<RTTI*> list);

		/// <summary>
		/// Destructor of Datum. Free any memory owned by this object.
		/// </summary>
		~Datum();

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other">Reference to other Datum object that we are constructing this from</param>
		Datum(const Datum& other);

		/// <summary>
		/// Assignment Operator
		/// </summary>
		/// <param name="other">Reference to other Datum object that we are assigning this from</param>
		/// <returns>Reference to Datum for assignment</returns>
		Datum& operator=(const Datum& other);

		/// <summary>
		/// Assignment Operator Integer Overload
		/// </summary>
		/// <param name="other">Reference to scalar Integer that we are assigning this Datum to</param>
		/// <returns>Reference to Datum for assignment</returns>
		Datum& operator=(const std::int32_t other);

		/// <summary>
		/// Assignment Operator Float Overload
		/// </summary>
		/// <param name="other">Reference to scalar Float that we are assigning this Datum to</param>
		/// <returns>Reference to Datum for assignment</returns>
		Datum& operator=(const float other);

		/// <summary>
		/// Assignment Operator Vector Overload
		/// </summary>
		/// <param name="other">Reference to scalar Vector that we are assigning this Datum to</param>
		/// <returns>Reference to Datum for assignment</returns>
		Datum& operator=(const glm::vec4 other);

		/// <summary>
		/// Assignment Operator Matrix Overload
		/// </summary>
		/// <param name="other">Reference to scalar Matrix that we are assigning this Datum to</param>
		/// <returns>Reference to Datum for assignment</returns>
		Datum& operator=(const glm::mat4 other);

		/// <summary>
		/// Assignment Operator String Overload
		/// </summary>
		/// <param name="other">Reference to scalar String that we are assigning this Datum to</param>
		/// <returns>Reference to Datum for assignment</returns>
		Datum& operator=(const std::string& other);

		/// <summary>
		/// Assignment Operator Pointer Overload
		/// </summary>
		/// <param name="other">Reference to scalar Pointer (RTTI) that we are assigning this Datum to</param>
		/// <returns>Reference to Datum for assignment</returns>
		Datum& operator=(RTTI* const other);

		/// <summary>
		/// Assignment Operator Table Overload
		/// </summary>
		/// <param name="other">Reference to scalar pointer to Scope (Table) that we are assigning this Datum to</param>
		/// <returns>Reference to Datum for assignment</returns>
		Datum& operator=(Scope* const other);

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs"> Rvalue reference to Datum object that we are moving for Construction</param>
		Datum(Datum&& rhs) noexcept;

		/// <summary>
		/// Move Assignment operator
		/// </summary>
		/// <param name="rhs">Rvalue reference to Datum object that we are moving for assignment</param>
		/// <returns>Reference to Datum for move assignment</returns>
		Datum& operator=(Datum&& rhs) noexcept;


		/// <summary>
		/// Equality Comparison Operator for Datum to another Datum
		/// </summary>
		/// <param name="other">reference to other datum</param>
		/// <returns>Boolean whether values are equal</returns>
		bool operator==(const Datum& other);


		/// <summary>
		/// Equality Comparison Operator for Datum to integer
		/// </summary>
		/// <param name="other">reference to other datum</param>
		/// <returns>Boolean whether values are equal</returns>
		bool operator==(const std::int32_t& other);


		/// <summary>
		/// Equality Comparison Operator for Datum to float
		/// </summary>
		/// <param name="other">reference to other datum</param>
		/// <returns>Boolean whether values are equal</returns>
		bool operator==(const float& other);


		/// <summary>
		/// Equality Comparison Operator for Datum to vector
		/// </summary>
		/// <param name="other">reference to other datum</param>
		/// <returns>Boolean whether values are equal</returns>
		bool operator==(const glm::vec4& other);


		/// <summary>
		/// Equality Comparison Operator for Datum to matrix
		/// </summary>
		/// <param name="other">reference to other datum</param>
		/// <returns>Boolean whether values are equal</returns>
		bool operator==(const glm::mat4& other);

		/// <summary>
		/// Equality Comparison Operator for Datum to string
		/// </summary>
		/// <param name="other">reference to other datum</param>
		/// <returns>Boolean whether values are equal</returns>
		bool operator==(const std::string& other);

		/// <summary>
		/// Equality Comparison Operator for Datum to Pointer (RTTI)
		/// </summary>
		/// <param name="other">reference to other datum</param>
		/// <returns>Boolean whether values are equal</returns>
		bool operator==(RTTI* const other);


		/// <summary>
		/// Inequality Comparison Operator for Datum to another Datum
		/// </summary>
		/// <param name="other">reference to other datum</param>
		/// <returns>Boolean whether values are equal</returns>
		bool operator!=(const Datum& other);


		/// <summary>
		/// Inequality Comparison Operator for Datum to integer
		/// </summary>
		/// <param name="other">reference to other datum</param>
		/// <returns>Boolean whether values are equal</returns>
		bool operator!=(const std::int32_t& other);


		/// <summary>
		/// Inequality Comparison Operator for Datum to float
		/// </summary>
		/// <param name="other">reference to other datum</param>
		/// <returns>Boolean whether values are equal</returns>
		bool operator!=(const float& other);


		/// <summary>
		/// Inequality Comparison Operator for Datum to vector
		/// </summary>
		/// <param name="other">reference to other datum</param>
		/// <returns>Boolean whether values are equal</returns>
		bool operator!=(const glm::vec4& other);


		/// <summary>
		/// Inequality Comparison Operator for Datum to matrix
		/// </summary>
		/// <param name="other">reference to other datum</param>
		/// <returns>Boolean whether values are equal</returns>
		bool operator!=(const glm::mat4& other);

		/// <summary>
		/// Inequality Comparison Operator for Datum to string
		/// </summary>
		/// <param name="other">reference to other datum</param>
		/// <returns>Boolean whether values are equal</returns>
		bool operator!=(const std::string& other);

		/// <summary>
		/// Inequality Comparison Operator for Datum to Pointer (RTTI)
		/// </summary>
		/// <param name="other">reference to other datum</param>
		/// <returns>Boolean whether values are equal</returns>
		bool operator!=(RTTI* const other);

		/// <summary>
		/// operator [] allows syntactically simplified access to nested Scopes
		/// </summary>
		/// <param name="index">index of nested scope</param>
		/// <returns>Scope pointer</returns>
		Scope& operator[](size_t index) { return GetTable(index); }

		/// <summary>
		/// Return Type enum associated with this object.
		/// </summary>
		/// <returns>DatumType of this object</returns>
		[[nodiscard]] DatumTypes Type() const;

		/// <summary>
		/// Return boolean for this datum being external
		/// </summary>
		/// <returns>boolean isExternal</returns>
		[[nodiscard]] bool IsExternal() const;

		/// <summary>
		/// Set Type associated with this object.
		/// </summary>
		/// <param name="type">type inputted to set the Datumtype to</param>
		void SetType(DatumTypes type);

		/// <summary>
		/// Return unsigned integer number of values for the size/population of Datum.
		/// </summary>
		/// <returns>Size of the Datum</returns>
		[[nodiscard]] size_t Size() const;

		/// <summary>
		/// Given integer number of values, set number of values and reserve memory if needed. This allows shrinking or growing. After a Resize call the Datum's Size and Capacity are the same.
		/// </summary>
		/// <param name="size">value to use for setting the new size/capacity of datum</param>
		/// <exception cref="Type Unknown">throw exception if type is unknown</exception>
		void Resize(size_t size);

		/// <summary>
		/// Clear the array without shrinking the capacity.
		/// </summary>
		void Clear();

		/// <summary>
		/// Reduce capacity to match size.
		/// </summary>
		void ShrinkToFit();

		/// <summary>
		/// Return unsigned integer number of values for the capacity of Datum.
		/// </summary>
		/// <returns>Capacity of the Datum</returns>
		[[nodiscard]] size_t Capacity() const;

		/// <summary>
		/// Increases the capacity to given parameter, but does not shrink
		/// </summary>
		/// <param name="capacity">capacity value to increase to</param>
		/// <exception cref="Type Unknown">throw exception if type is unknown</exception>
		void Reserve(size_t capacity);


		/// <summary>
		/// Given a value and an optional index (default is 0), assign the appropriate element in the values array to the given value. 
		/// </summary>
		/// <param name="value"> string value to set </param>
		/// <param name="index"> index to place value, defaulted to 0 </param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		void SetString(const std::string& value, size_t index = 0);

		/// <summary>
		/// Given a value and an optional index (default is 0), assign the appropriate element in the values array to the given value. 
		/// </summary>
		/// <param name="value"> Integer value to set </param>
		/// <param name="index"> index to place value, defaulted to 0 </param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		void SetInteger(std::int32_t value, size_t index = 0);

		/// <summary>
		/// Given a value and an optional index (default is 0), assign the appropriate element in the values array to the given value. 
		/// </summary>
		/// <param name="value"> Float value to set </param>
		/// <param name="index"> index to place value, defaulted to 0 </param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		void SetFloat(float value, size_t index = 0);

		/// <summary>
		/// Given a value and an optional index (default is 0), assign the appropriate element in the values array to the given value. 
		/// </summary>
		/// <param name="value"> Vector value to set </param>
		/// <param name="index"> index to place value, defaulted to 0 </param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		void SetVector(glm::vec4& value, size_t index = 0);

		/// <summary>
		/// Given a value and an optional index (default is 0), assign the appropriate element in the values array to the given value. 
		/// </summary>
		/// <param name="value"> Matrix value to set </param>
		/// <param name="index"> index to place value, defaulted to 0 </param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		void SetMatrix(glm::mat4& value, size_t index = 0);

		/// <summary>
		/// Given a value and an optional index (default is 0), assign the appropriate element in the values array to the given value. 
		/// </summary>
		/// <param name="value"> pointer value to set </param>
		/// <param name="index"> index to place value, defaulted to 0 </param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		void SetPointer(RTTI* value, size_t index = 0);

		/// <summary>
		/// Given a value and an optional index (default is 0), assign the appropriate element in the values array to the given value. 
		/// </summary>
		/// <param name="value"> pointer to a scope to set </param>
		/// <param name="index"> index to place value, defaulted to 0 </param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		void SetTable(Scope* value, size_t index = 0);

		/// <summary>
		/// Given an optional index (default is 0), return the appropriate value from the values array.
		/// </summary>
		/// <param name="index">index to place value, defaulted to 0</param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		/// <returns> Reference to String at given index</returns>
		[[nodiscard]] std::string& GetString(size_t index = 0);

		/// <summary>
		/// Given an optional index (default is 0), return the appropriate value from the values array.
		/// </summary>
		/// <param name="index">index to place value, defaulted to 0</param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		/// <returns> Reference to Integer at given index</returns>
		[[nodiscard]] std::int32_t& GetInteger(size_t index = 0);

		/// <summary>
		/// Given an optional index (default is 0), return the appropriate value from the values array.
		/// </summary>
		/// <param name="index">index to place value, defaulted to 0</param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		/// <returns> Reference to Float at given index</returns>
		[[nodiscard]] float& GetFloat(size_t index = 0);

		/// <summary>
		/// Given an optional index (default is 0), return the appropriate value from the values array.
		/// </summary>
		/// <param name="index">index to place value, defaulted to 0</param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		/// <returns> Reference to Vector at given index</returns>
		[[nodiscard]] glm::vec4& GetVector(size_t index = 0);

		/// <summary>
		/// Given an optional index (default is 0), return the appropriate value from the values array.
		/// </summary>
		/// <param name="index">index to place value, defaulted to 0</param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		/// <returns> Reference to Matrix at given index</returns>
		[[nodiscard]] glm::mat4& GetMatrix(size_t index = 0);

		/// <summary>
		/// Given an optional index (default is 0), return the appropriate value from the values array.
		/// </summary>
		/// <param name="index">index to place value, defaulted to 0</param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		/// <returns> Returns Pointer at given index</returns>
		[[nodiscard]] RTTI* GetPointer(size_t index = 0);

		/// <summary>
		/// Given an optional index (default is 0), return the appropriate value from the values array.
		/// </summary>
		/// <param name="index">index to place value, defaulted to 0</param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		/// <returns> Returns Reference to Table at given index</returns>
		[[nodiscard]] Scope& GetTable(size_t index = 0);


		/// <summary>
		/// Given an optional index (default is 0), return the appropriate value from the values array.
		/// </summary>
		/// <param name="index">index to place value, defaulted to 0</param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		/// <returns> Reference to String at given index</returns>
		[[nodiscard]] const std::string& GetString(size_t index = 0) const;

		/// <summary>
		/// Given an optional index (default is 0), return the appropriate value from the values array.
		/// </summary>
		/// <param name="index">index to place value, defaulted to 0</param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		/// <returns> Reference to Integer at given index</returns>
		[[nodiscard]] const std::int32_t& GetInteger(size_t index = 0) const;

		/// <summary>
		/// Given an optional index (default is 0), return the appropriate value from the values array.
		/// </summary>
		/// <param name="index">index to place value, defaulted to 0</param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		/// <returns> Reference to Float at given index</returns>
		[[nodiscard]] const float& GetFloat(size_t index = 0) const;

		/// <summary>
		/// Given an optional index (default is 0), return the appropriate value from the values array.
		/// </summary>
		/// <param name="index">index to place value, defaulted to 0</param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		/// <returns> Reference to Vector at given index</returns>
		[[nodiscard]] const glm::vec4& GetVector(size_t index = 0) const;

		/// <summary>
		/// Given an optional index (default is 0), return the appropriate value from the values array.
		/// </summary>
		/// <param name="index">index to place value, defaulted to 0</param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		/// <returns> Reference to Matrix at given index</returns>
		[[nodiscard]] const glm::mat4& GetMatrix(size_t index = 0) const;

		/// <summary>
		/// Given an optional index (default is 0), return the appropriate value from the values array.
		/// </summary>
		/// <param name="index">index to place value, defaulted to 0</param>
		/// <exception cref="Index"> throw exception if Index >= size </exception>
		/// <returns> Returns Pointer at given index</returns>
		[[nodiscard]] RTTI* const GetPointer(size_t index = 0) const;

		/// <summary>
		/// Helper Function to call set storage on given type. If type is table, storage assumed to be internal.
		/// </summary>
		/// <param name="type">Type to switch on for specific set storage call</param>
		/// <param name="array">void pointer</param>
		/// <param name="size">size</param>
		void SetStorage(DatumTypes type, void* array, std::size_t size);

		/// <summary>
		///  Given an array and the number of elements in it, assign the internal values array to the given array, and the size and capacity to the given number of elements.
		/// </summary>
		/// <param name="values">Array of type string</param>
		/// <param name="size">Size of the array</param>
		void SetStorageString(std::string* array, std::size_t size);

		/// <summary>
		///  Given an array and the number of elements in it, assign the internal values array to the given array, and the size and capacity to the given number of elements.
		/// </summary>
		/// <param name="values">Array of type Integer</param>
		/// <param name="size">Size of the array</param>
		void SetStorageInteger(std::int32_t* array, std::size_t size);

		/// <summary>
		///  Given an array and the number of elements in it, assign the internal values array to the given array, and the size and capacity to the given number of elements.
		/// </summary>
		/// <param name="values">Array of type Float</param>
		/// <param name="size">Size of the array</param>
		void SetStorageFloat(float* array, std::size_t size);

		/// <summary>
		///  Given an array and the number of elements in it, assign the internal values array to the given array, and the size and capacity to the given number of elements.
		/// </summary>
		/// <param name="values">Array of type Vector</param>
		/// <param name="size">Size of the array</param>
		void SetStorageVector(glm::vec4* array, std::size_t size);

		/// <summary>
		///  Given an array and the number of elements in it, assign the internal values array to the given array, and the size and capacity to the given number of elements.
		/// </summary>
		/// <param name="values">Array of type Matrix</param>
		/// <param name="size">Size of the array</param>
		void SetStorageMatrix(glm::mat4* array, std::size_t size);

		/// <summary>
		///  Given an array and the number of elements in it, assign the internal values array to the given array, and the size and capacity to the given number of elements.
		/// </summary>
		/// <param name="values">Array of type Pointer (RTTI)</param>
		/// <param name="size">Size of the array</param>
		void SetStoragePointer(RTTI** array, std::size_t size);


		/// <summary>
		/// Push integer value to the back of the Datum, Reserves capacity if needed.
		/// </summary>
		/// <param name="value">value to push to back of the datum</param>
		void PushBack(const int value);

		/// <summary>
		/// Push float value to the back of the Datum, Reserves capacity if needed.
		/// </summary>
		/// <param name="value">value to push to back of the datum</param>
		void PushBack(const float value);

		/// <summary>
		/// Push Vector value to the back of the Datum, Reserves capacity if needed.
		/// </summary>
		/// <param name="value">value to push to back of the datum</param>
		void PushBack(const glm::vec4 value);

		/// <summary>
		/// Push Matrix value to the back of the Datum, Reserves capacity if needed.
		/// </summary>
		/// <param name="value">value to push to back of the datum</param>
		void PushBack(const glm::mat4 value);

		/// <summary>
		/// Push string value to the back of the Datum, Reserves capacity if needed.
		/// </summary>
		/// <param name="value">value to push to back of the datum</param>
		void PushBack(const std::string& value);

		/// <summary>
		/// Push Pointer (RTTI) value to the back of the Datum, Reserves capacity if needed.
		/// </summary>
		/// <param name="value">value to push to back of the datum</param>
		void PushBack(RTTI* const value);

		/// <summary>
		/// Push Scope (Table) value to the back of the Datum, Reserves capacity if needed.
		/// </summary>
		/// <param name="value">value to push to back of the datum</param>
		void PushBack(Scope* const value);

		/// <summary>
		/// Remove the last item in the container, but should not reduce the capacity of the container.
		/// </summary>
		/// <exception cref="Type Unknown"> throw exception if type unknown </exception>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		void PopBack();

		/// <summary>
		/// Returns the Front of the Integer Array
		/// </summary>
		/// <returns>First Integer in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] std::int32_t& FrontInteger();

		/// <summary>
		/// Returns the Front of the Float Array
		/// </summary>
		/// <returns>First Float in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] float& FrontFloat();

		/// <summary>
		/// Returns the Front of the Vector Array
		/// </summary>
		/// <returns>First Vector in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] glm::vec4& FrontVector();

		/// <summary>
		/// Returns the Front of the Matrix Array
		/// </summary>
		/// <returns>First MAtrix in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] glm::mat4& FrontMatrix();

		/// <summary>
		/// Returns the Front of the String Array
		/// </summary>
		/// <returns>First String in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] std::string& FrontString();

		/// <summary>
		/// Returns the Front of the Pointer Array
		/// </summary>
		/// <returns>First Pointer in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] RTTI* FrontPointer();

		/// <summary>
		/// Returns the Front of the Integer Array
		/// </summary>
		/// <returns>First Integer in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] const std::int32_t& FrontInteger() const;

		/// <summary>
		/// Returns the Front of the Float Array
		/// </summary>
		/// <returns>First Float in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] const float& FrontFloat() const;

		/// <summary>
		/// Returns the Front of the Vector Array
		/// </summary>
		/// <returns>First Vector in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] const glm::vec4& FrontVector() const;

		/// <summary>
		/// Returns the Front of the Matrix Array
		/// </summary>
		/// <returns>First MAtrix in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] const glm::mat4& FrontMatrix() const;

		/// <summary>
		/// Returns the Front of the String Array
		/// </summary>
		/// <returns>First String in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] const std::string& FrontString() const;

		/// <summary>
		/// Returns the Front of the Pointer Array
		/// </summary>
		/// <returns>First Pointer in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] RTTI* const FrontPointer() const;


		/// <summary>
		/// Returns the Back of the Integer Array
		/// </summary>
		/// <returns>First Integer in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] std::int32_t& BackInteger();

		/// <summary>
		/// Returns the Back of the Float Array
		/// </summary>
		/// <returns>First Float in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] float& BackFloat();

		/// <summary>
		/// Returns the Back of the Vector Array
		/// </summary>
		/// <returns>First Vector in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] glm::vec4& BackVector();

		/// <summary>
		/// Returns the Back of the Matrix Array
		/// </summary>
		/// <returns>First MAtrix in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] glm::mat4& BackMatrix();

		/// <summary>
		/// Returns the Back of the String Array
		/// </summary>
		/// <returns>First String in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] std::string& BackString();

		/// <summary>
		/// Returns the Back of the Pointer Array
		/// </summary>
		/// <returns>First Pointer in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] RTTI* BackPointer();


		/// <summary>
		/// Returns the Back of the Integer Array
		/// </summary>
		/// <returns>First Integer in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] const std::int32_t& BackInteger() const;

		/// <summary>
		/// Returns the Back of the Float Array
		/// </summary>
		/// <returns>First Float in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] const float& BackFloat() const;

		/// <summary>
		/// Returns the Back of the Vector Array
		/// </summary>
		/// <returns>First Vector in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] const glm::vec4& BackVector() const;

		/// <summary>
		/// Returns the Back of the Matrix Array
		/// </summary>
		/// <returns>First MAtrix in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] const glm::mat4& BackMatrix() const;

		/// <summary>
		/// Returns the Back of the String Array
		/// </summary>
		/// <returns>First String in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] const std::string& BackString() const;

		/// <summary>
		/// Returns the Back of the Pointer Array
		/// </summary>
		/// <returns>First Pointer in Array</returns>
		/// <exception cref="Size 0"> throw exception if size = 0 </exception>
		[[nodiscard]] RTTI* const BackPointer() const;



		/// <summary>
		/// Finds the given value and returns the first index for it in the array. If not found return Size_t(MAXSIZE);
		/// </summary>
		/// <param name="value">value to look for in array</param>
		/// <returns>size_T of index found, Size_t(MAXSIZE) if not found</returns>
		std::size_t Find(const std::int32_t value);

		/// <summary>
		/// Finds the given value and returns the first index for it in the array. If not found return Size_t(MAXSIZE);
		/// </summary>
		/// <param name="value">value to look for in array</param>
		/// <returns>size_T of index found, Size_t(MAXSIZE) if not found</returns>
		std::size_t Find(const float value);

		/// <summary>
		/// Finds the given value and returns the first index for it in the array. If not found return Size_t(MAXSIZE);
		/// </summary>
		/// <param name="value">value to look for in array</param>
		/// <returns>size_T of index found, Size_t(MAXSIZE) if not found</returns>
		std::size_t Find(const glm::vec4 value);

		/// <summary>
		/// Finds the given value and returns the first index for it in the array. If not found return Size_t(MAXSIZE);
		/// </summary>
		/// <param name="value">value to look for in array</param>
		/// <returns>size_T of index found, Size_t(MAXSIZE) if not found</returns>
		std::size_t Find(const glm::mat4 value);

		/// <summary>
		/// Finds the given value and returns the first index for it in the array. If not found return Size_t(MAXSIZE);
		/// </summary>
		/// <param name="value">value to look for in array</param>
		/// <returns>size_T of index found, Size_t(MAXSIZE) if not found</returns>
		std::size_t Find(const std::string& value);

		/// <summary>
		/// Finds the given value and returns the first index for it in the array. If not found return Size_t(MAXSIZE);
		/// </summary>
		/// <param name="value">value to look for in array</param>
		/// <returns>size_T of index found, Size_t(MAXSIZE) if not found</returns>
		std::size_t Find(const RTTI* value);

		/// <summary>
		/// Remove the element at the given index in the array. Return true or false if succesful.
		/// </summary>
		/// <param name="index">index for value to remove</param>
		/// <returns>Boolean for success of removal</returns>
		bool RemoveAt(size_t index);

		/// <summary>
		/// Remove the give element, first searches for the element than attempts to remove. Returns true or false if succesful.
		/// </summary>
		/// <param name="value">Value to find and remove</param>
		/// <returns>Boolean for success of removal</returns>
		bool Remove(const std::int32_t value);

		/// <summary>
		/// Remove the give element, first searches for the element than attempts to remove. Returns true or false if succesful.
		/// </summary>
		/// <param name="value">Value to find and remove</param>
		/// <returns>Boolean for success of removal</returns>
		bool Remove(const float value);

		/// <summary>
		/// Remove the give element, first searches for the element than attempts to remove. Returns true or false if succesful.
		/// </summary>
		/// <param name="value">Value to find and remove</param>
		/// <returns>Boolean for success of removal</returns>
		bool Remove(const glm::vec4 value);

		/// <summary>
		/// Remove the give element, first searches for the element than attempts to remove. Returns true or false if succesful.
		/// </summary>
		/// <param name="value">Value to find and remove</param>
		/// <returns>Boolean for success of removal</returns>
		bool Remove(const glm::mat4 value);

		/// <summary>
		/// Remove the give element, first searches for the element than attempts to remove. Returns true or false if succesful.
		/// </summary>
		/// <param name="value">Value to find and remove</param>
		/// <returns>Boolean for success of removal</returns>
		bool Remove(const std::string& value);

		/// <summary>
		/// Remove the give element, first searches for the element than attempts to remove. Returns true or false if succesful.
		/// </summary>
		/// <param name="value">Value to find and remove</param>
		/// <returns>Boolean for success of removal</returns>
		bool Remove(const RTTI* value);


		/// <summary>
		/// given an optional index (default is 0) return an STL string representing the appropriate element in the values array.
		/// </summary>
		/// <param name="index">index to get and assign to string</param>
		/// <returns>String representation of value at given index</returns>
		std::string ToString(size_t index = 0);

		/// <summary>
		///  given an STL string and an optional index (default 0) assign the appropriate element in the values array to the given value (enforce that the datum’s type has already been specified).
		/// </summary>
		/// <param name="value">value of type string representing an Integer </param>
		/// <param name="index">Index to assign value to, defaulted to 0</param>
		void SetFromStringInteger(const std::string& value, size_t index = 0);

		/// <summary>
		///  given an STL string and an optional index (default 0) assign the appropriate element in the values array to the given value (enforce that the datum’s type has already been specified).
		/// </summary>
		/// <param name="value">value of type string representing a float </param>
		/// <param name="index">Index to assign value to, defaulted to 0</param>
		void SetFromStringFloat(const std::string& value, size_t index = 0);

		/// <summary>
		///  given an STL string and an optional index (default 0) assign the appropriate element in the values array to the given value (enforce that the datum’s type has already been specified).
		/// </summary>
		/// <param name="value">value of type string representing a Vector </param>
		/// <param name="index">Index to assign value to, defaulted to 0</param>
		void SetFromStringVector(const std::string& value, size_t index = 0);

		/// <summary>
		///  given an STL string and an optional index (default 0) assign the appropriate element in the values array to the given value (enforce that the datum’s type has already been specified).
		/// </summary>
		/// <param name="value">value of type string representing a Matrix </param>
		/// <param name="index">Index to assign value to, defaulted to 0</param>
		void SetFromStringMatrix(const std::string& value, size_t index = 0);

		/// <summary>
		/// Call Pushback with an integer, but converting the inputted string to an integer. 
		/// </summary>
		/// <param name="input">inputted string representing an integer</param>
		void PushBackFromStringInteger(const std::string& input);

		/// <summary>
		/// Call Pushback with an Float, but converting the inputted string to an Float. 
		/// </summary>
		/// <param name="input">inputted string representing an Float</param>
		void PushBackFromStringFloat(const std::string& input);

		/// <summary>
		/// Call Pushback with an Vector, but converting the inputted string to an Vector. 
		/// </summary>
		/// <param name="input">inputted string representing an Vector</param>
		void PushBackFromStringVector(const std::string& input);

		/// <summary>
		/// Call Pushback with an Matrix, but converting the inputted string to an Matrix. 
		/// </summary>
		/// <param name="input">inputted string representing an Matrix</param>
		void PushBackFromStringMatrix(const std::string& input);

	private:
		union DatumValues final
		{
			int32_t* i;
			float* f;
			glm::vec4* v;
			glm::mat4* m;
			std::string* s;
			RTTI** p;
			Scope** t;
			void* vp{nullptr};
			std::byte* b;
		};

		/// <summary>
		/// Sizes of each Type stored for quick access by indexing Enum Type value
		/// </summary>
		inline static const size_t _typeSizes[8]
		{
			0,					//UNKNOWN
			sizeof(int32_t),	//INTEGER
			sizeof(float),		//FLOAT
			sizeof(glm::uvec4), //VECTOR
			sizeof(glm::mat4),  //MATRIX
			sizeof(Scope*),		//TABLE
			sizeof(std::string),//STRING
			sizeof(RTTI*)		//POINTER

		};
		
		/// <summary>
		/// Union of possible data types to store our Datum Dynamically
		/// </summary>
		DatumValues _data; 
		/// <summary>
		/// Size of our Datum, the number of elements stored
		/// </summary>
		std::size_t _size{ 0 };
		/// <summary>
		/// Capacity of our Datum, the number of elements we can fit
		/// </summary>
		std::size_t _capacity{ 0 };
		/// <summary>
		/// Type of our Datum
		/// </summary>
		DatumTypes _type{ DatumTypes::Unknown };
		/// <summary>
		/// Whether our memory is external or internal.
		/// </summary>
		bool _isExternal{ false };

	};

}
