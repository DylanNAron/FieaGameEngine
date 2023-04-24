#include "pch.h"
#include "Datum.h"

namespace FieaGameEngine
{
	Datum::Datum(size_t size, DatumTypes type) :
		_type{ type }
	{
		if (size > 0)
		{
			Resize(size);
		}
	}

	Datum::Datum(std::initializer_list<int32_t> list)
	{
		for (auto& item : list)
		{
			PushBack(item);
		}
	}

	Datum::Datum(std::initializer_list<float> list)
	{
		for (auto& item : list)
		{
			PushBack(item);
		}
	}

	Datum::Datum(std::initializer_list<glm::vec4> list)
	{
		for (auto& item : list)
		{
			PushBack(item);
		}
	}

	Datum::Datum(std::initializer_list<glm::mat4> list)
	{
		for (auto& item : list)
		{
			PushBack(item);
		}
	}

	Datum::Datum(std::initializer_list<std::string> list)
	{
		for (auto& item : list)
		{
			PushBack(item);
		}
	}

	Datum::Datum(std::initializer_list<RTTI*> list)
	{
		for (auto& item : list)
		{
			PushBack(item);
		}
	}

	Datum::~Datum()
	{ 
		if (!_isExternal)
		{
			Clear();
			ShrinkToFit();
		}
	}

	Datum::Datum(const Datum& other) :
		_type(other._type), _isExternal(other._isExternal)
	{
		if (_isExternal || _type == DatumTypes::Unknown)
		{
			_data = other._data;
			_size = _capacity = other._size;
		}
		else
		{
			Reserve(other._capacity);
			switch (_type)
			{
			case DatumTypes::Integer:
				for (size_t i = 0; i < other._size; ++i)
				{
					PushBack(other._data.i[i]);
				}
				break;
			case DatumTypes::Float:
				for (size_t i = 0; i < other._size; ++i)
				{
					PushBack(other._data.f[i]);
				}
				break;
			case DatumTypes::String:
				for (size_t i = 0; i < other._size; ++i)
				{
					PushBack(other._data.s[i]);
				}
				break;
			case DatumTypes::Vector:
				for (size_t i = 0; i < other._size; ++i)
				{
					PushBack(other._data.v[i]);
				}
				break;
			case DatumTypes::Matrix:
				for (size_t i = 0; i < other._size; ++i)
				{
					PushBack(other._data.m[i]);
				}
				break;
			case DatumTypes::Pointer:
				for (size_t i = 0; i < other._size; ++i)
				{
					PushBack(other._data.p[i]);
				}
				break;
			case DatumTypes::Table:
				for (size_t i = 0; i < other._size; ++i)
				{
					PushBack(other._data.t[i]);
				}
				break;
			}

		}
	}

	Datum& Datum::operator=(const Datum& other)
	{
		Clear();
		ShrinkToFit();
		_type = other._type;
		_isExternal = other._isExternal;

		if (_isExternal)
		{
			_data = other._data;
			_size = _capacity = other._size;
		}
		else
		{
			Reserve(other._capacity);
			switch (_type)
			{
			case DatumTypes::Integer:
				for (size_t i = 0; i < other._size; ++i)
				{
					PushBack(other._data.i[i]);
				}
				break;
			case DatumTypes::Float:
				for (size_t i = 0; i < other._size; ++i)
				{
					PushBack(other._data.f[i]);
				}
				break;
			case DatumTypes::String:
				for (size_t i = 0; i < other._size; ++i)
				{
					PushBack(other._data.s[i]);
				}
				break;
			case DatumTypes::Vector:
				for (size_t i = 0; i < other._size; ++i)
				{
					PushBack(other._data.v[i]);
				}
				break;
			case DatumTypes::Matrix:
				for (size_t i = 0; i < other._size; ++i)
				{
					PushBack(other._data.m[i]);
				}
				break;
			case DatumTypes::Pointer:
				for (size_t i = 0; i < other._size; ++i)
				{
					PushBack(other._data.p[i]);
				}
				break;
			}

		}


		return *this;
	}

	Datum& Datum::operator=(const std::int32_t other)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::Integer);
		_type = DatumTypes::Integer;
		Clear();
		ShrinkToFit();
		PushBack(other);
		return *this;
	}

	Datum& Datum::operator=(const float other)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::Float);
		_type = DatumTypes::Float;
		Clear();
		ShrinkToFit();
		PushBack(other);
		return *this;
	}

	Datum& Datum::operator=(const glm::vec4 other)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::Vector);
		_type = DatumTypes::Vector;
		Clear();
		ShrinkToFit();
		PushBack(other);
		return *this;
	}

	Datum& Datum::operator=(const glm::mat4 other)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::Matrix);
		_type = DatumTypes::Matrix;
		Clear();
		ShrinkToFit();
		PushBack(other);
		return *this;
	}

	Datum& Datum::operator=(const std::string& other)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::String);
		_type = DatumTypes::String;
		Clear();
		ShrinkToFit();
		PushBack(other);
		return *this;
	}

	Datum& Datum::operator=(RTTI* const other)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::Pointer);
		_type = DatumTypes::Pointer;
		Clear();
		ShrinkToFit();
		PushBack(other);
		return *this;
	}

	Datum& Datum::operator=(Scope* const other)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::Table);
		_type = DatumTypes::Table;
		Clear();
		ShrinkToFit();
		PushBack(other);
		return *this;
	}

	Datum::Datum(Datum&& rhs) noexcept :
		_size{ rhs._size }, _capacity{ rhs._capacity }, _type{ rhs._type }, _data{ rhs._data }, _isExternal{ rhs._isExternal }
	{
		rhs._size = 0;
		rhs._capacity = 0;
		rhs._type = DatumTypes::Unknown;
		rhs._isExternal = true;
	}

	Datum& Datum::operator=(Datum&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Clear();

			_size = rhs._size;
			_capacity = rhs._capacity;
			_data = rhs._data;
			_type = rhs._type;
			_isExternal = rhs._isExternal;

			rhs._size = 0;
			rhs._capacity = 0;
			rhs._type = DatumTypes::Unknown;
			rhs._isExternal = true;


		}
		return *this;
	}

	bool Datum::operator==(const Datum& other)
	{
		if ( (_type == other._type) && (_size == other._size) )
		{
			if (_type == DatumTypes::Unknown)
			{
				return true; //default datums are equal
			}

			if (_type == DatumTypes::String)
			{
				for (size_t i = 0; i < _size; ++i)
				{
					if (other._data.s[i] != _data.s[i])
					{
						return false;
					}
				}
			}
			else if (_type == DatumTypes::Table || _type == DatumTypes::Pointer)
			{
				for (size_t i = 0; i < _size; ++i)
				{
					if (!other._data.p[i]->Equals(_data.p[i]))
					{
						return false;
					}
				}
			}
			else
			{
				return (memcmp(other._data.vp, _data.vp, _typeSizes[static_cast<int>(_type)]*_size) == 0);
			}
		}
		else
		{
			return false;
		}

		return true;
	}

	bool Datum::operator==(const std::int32_t& other)
	{
		if (_type != DatumTypes::Integer)
		{
			return false;
		}
		return (_size == 1 && _data.i[0] == other);
	}

	bool Datum::operator==(const float& other)
	{
		if (_type != DatumTypes::Float)
		{
			return false;
		}
		return (_size == 1 && _data.f[0] == other);
	}

	bool Datum::operator==(const glm::vec4& other)
	{
		if (_type != DatumTypes::Vector)
		{
			return false;
		}
		return (_size == 1 && _data.v[0] == other);
	}

	bool Datum::operator==(const glm::mat4& other)
	{
		if (_type != DatumTypes::Matrix)
		{
			return false;
		}
		return (_size == 1 && _data.m[0] == other);
	}

	bool Datum::operator==(const std::string& other)
	{
		if (_type != DatumTypes::String)
		{
			return false;
		}
		return (_size == 1 && _data.s[0] == other);
	}

	bool Datum::operator==(RTTI* const other)
	{
		if (_type != DatumTypes::Pointer)
		{
			return false;
		}
		return (_size == 1 && _data.p[0] == other);
	}

	bool Datum::operator!=(const Datum& other)
	{
		return !(*this == other);
	}

	bool Datum::operator!=(const std::int32_t& other)
	{
		return !(*this == other);
	}

	bool Datum::operator!=(const float& other)
	{
		return !(*this == other);
	}

	bool Datum::operator!=(const glm::vec4& other)
	{
		return !(*this == other);
	}

	bool Datum::operator!=(const glm::mat4& other)
	{
		return !(*this == other);
	}

	bool Datum::operator!=(const std::string& other)
	{
		return !(*this == other);
	}

	bool Datum::operator!=(RTTI* const other)
	{
		return !(*this == other);
	}

	Datum::DatumTypes Datum::Type() const
	{
		return _type;
	}

	bool Datum::IsExternal() const
	{
		return _isExternal;
	}

	void Datum::SetType(DatumTypes type)
	{
		_type = type;
	}

	size_t Datum::Size() const
	{
		return _size;
	}

	void Datum::Resize(size_t size)
	{
		if (_isExternal)
		{
			throw std::runtime_error("Cannot Resize External Datum");

		}
		if (_type == DatumTypes::Unknown)
		{
			throw std::runtime_error("Cannot Reserve Unknown Type");
		}

		if (size < _size)
		{
			if (_type == DatumTypes::String) //if we are shrinking destroy strings
			{
				for (size_t i = size - 1; i < _size; ++i)
				{
					_data.s[i].~basic_string();
				}
			}
		}
		else
		{
			Reserve(size);
		}

		_size = size;
		ShrinkToFit();
	}

	void Datum::Clear()
	{
		if (!_isExternal)
		{
			if (_type == DatumTypes::String)
			{
				for (size_t i = 0; i < _size; ++i)
				{
					_data.s[i].~basic_string();
				}
			}
		}
		_size = 0;
	}

	void Datum::ShrinkToFit()
	{
		if (!_isExternal)
		{
			if (_size == 0)
			{
				free(_data.vp);
				_data.vp = nullptr;
			}
			else if (_capacity > _size)
			{
				void* data = realloc(_data.vp, _size * _typeSizes[static_cast<int>(_type)]);
				assert(data != nullptr);
				_data.vp = data;
			}
			_capacity = _size;
		}

	}

	size_t Datum::Capacity() const
	{
		return _capacity;
	}

	void Datum::Reserve(size_t capacity)
	{
		if (_type == DatumTypes::Unknown)
		{
			throw std::runtime_error("Cannot Reserve Unknown Type");
		}

		if (capacity > _capacity)
		{
			assert(_typeSizes[static_cast<int>(_type)] > 0);
			void* data = (realloc(_data.vp, capacity * (_typeSizes[static_cast<int>(_type)])));
			assert(data != nullptr);
			_data.vp = data;
			_capacity = capacity;
		}
	}

	void Datum::SetString(const std::string& value, size_t index)
	{
		assert(_type == DatumTypes::String);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		_data.s[index] = value;
	}

	void Datum::SetInteger(std::int32_t value, size_t index)
	{
		assert(_type == DatumTypes::Integer);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		_data.i[index] = value;
	}

	void Datum::SetFloat(float value, size_t index)
	{
		assert(_type == DatumTypes::Float);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		_data.f[index] = value;
	}

	void Datum::SetVector(glm::vec4& value, size_t index)
	{
		assert(_type == DatumTypes::Vector);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		_data.v[index] = value;
	}

	void Datum::SetMatrix(glm::mat4& value, size_t index)
	{
		assert(_type == DatumTypes::Matrix);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		_data.m[index] = value;
	}

	void Datum::SetPointer(RTTI* value, size_t index)
	{
		assert(_type == DatumTypes::Pointer);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		_data.p[index] = value;
	}

	void Datum::SetTable(Scope* value, size_t index)
	{
		assert(_type == DatumTypes::Table);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		_data.t[index] = value;
	}



	std::string& Datum::GetString(size_t index)
	{
		assert(_type == DatumTypes::String);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		return _data.s[index];
	}

	std::int32_t& Datum::GetInteger(size_t index)
	{
		assert(_type == DatumTypes::Integer);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		return _data.i[index];
	}

	float& Datum::GetFloat(size_t index)
	{
		assert(_type == DatumTypes::Float);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		return _data.f[index];
	}

	glm::vec4& Datum::GetVector(size_t index)
	{
		assert(_type == DatumTypes::Vector);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		return _data.v[index];
	}

	glm::mat4& Datum::GetMatrix(size_t index)
	{
		assert(_type == DatumTypes::Matrix);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		return _data.m[index];
	}

	RTTI* Datum::GetPointer(size_t index)
	{
		assert(_type == DatumTypes::Pointer);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		return _data.p[index];
	}

	Scope& Datum::GetTable(size_t index)
	{
		assert(_type == DatumTypes::Table);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		return *_data.t[index];
	}

	const std::string& Datum::GetString(size_t index) const
	{
		assert(_type == DatumTypes::String);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		return _data.s[index];
	}

	const std::int32_t& Datum::GetInteger(size_t index) const
	{
		assert(_type == DatumTypes::Integer);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		return _data.i[index];

	}

	const float& Datum::GetFloat(size_t index) const
	{
		assert(_type == DatumTypes::Float);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		return _data.f[index];
	}

	const glm::vec4& Datum::GetVector(size_t index) const
	{
		assert(_type == DatumTypes::Vector);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		return _data.v[index];
	}

	const glm::mat4& Datum::GetMatrix(size_t index) const
	{
		assert(_type == DatumTypes::Matrix);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		return _data.m[index];
	}

	RTTI* const Datum::GetPointer(size_t index) const
	{
		assert(_type == DatumTypes::Pointer);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		return _data.p[index];
	}


	void Datum::SetStorage(DatumTypes type, void* array, std::size_t size)
	{
		switch (type)
		{
		case Datum::DatumTypes::Integer:
			SetStorageInteger(reinterpret_cast<int32_t*>(array), size);
			break;
		case Datum::DatumTypes::Float:
			SetStorageFloat(reinterpret_cast<float*>(array), size);
			break;
		case Datum::DatumTypes::String:
			SetStorageString(reinterpret_cast<std::string*>(array), size);
			break;
		case Datum::DatumTypes::Vector:
			SetStorageVector(reinterpret_cast<glm::vec4*>(array), size);
			break;
		case Datum::DatumTypes::Matrix:
			SetStorageMatrix(reinterpret_cast<glm::mat4*>(array), size);
			break;
		case Datum::DatumTypes::Pointer:
			SetStoragePointer(reinterpret_cast<RTTI**>(array), size);
			break;
		default:
			assert(false); //should not reach here - maybe attempted externally storing a table or missing a type
			break;
		}
	}
	

	void Datum::SetStorageString(std::string* array, std::size_t size)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::String);
		_type = DatumTypes::String;
		_isExternal = true;
		_size = _capacity = size;

		_data.s = array;
	}

	void Datum::SetStorageInteger(std::int32_t* array, std::size_t size)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::Integer);
		_type = DatumTypes::Integer;
		_isExternal = true;
		_size = _capacity = size;

		_data.i = array;
	}

	void Datum::SetStorageFloat(float* array, std::size_t size)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::Float);
		_type = DatumTypes::Float;
		_isExternal = true;
		_size = _capacity = size;

		_data.f = array;
	}

	void Datum::SetStorageVector(glm::vec4* array, std::size_t size)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::Vector);
		_type = DatumTypes::Vector;
		_isExternal = true;
		_size = _capacity = size;

		_data.v = array;
	}

	void Datum::SetStorageMatrix(glm::mat4* array, std::size_t size)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::Matrix);
		_type = DatumTypes::Matrix;
		_isExternal = true;
		_size = _capacity = size;

		_data.m = array;
	}

	void Datum::SetStoragePointer(RTTI** array, std::size_t size)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::Pointer);
		_type = DatumTypes::Pointer;
		_isExternal = true;
		_size = _capacity = size;

		_data.p = array;
	}

	void Datum::PushBack(const int value)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::Integer);
		_type = DatumTypes::Integer;

		if (_size == _capacity)
		{
			Reserve(_size + 1);
		}
		++_size;
		_data.i[_size - 1] = value;
	}

	void Datum::PushBack(const float value)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::Float);
		_type = DatumTypes::Float;

		if (_size == _capacity)
		{
			Reserve(_size + 1);
		}
		++_size;
		_data.f[_size - 1] = value;
	}

	void Datum::PushBack(const glm::vec4 value)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::Vector);
		_type = DatumTypes::Vector;

		if (_size == _capacity)
		{
			Reserve(_size + 1);
		}
		++_size;
		_data.v[_size - 1] = value;
	}

	void Datum::PushBack(const glm::mat4 value)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::Matrix);
		_type = DatumTypes::Matrix;

		if (_size == _capacity)
		{
			Reserve(_size + 1);
		}
		++_size;
		_data.m[_size - 1] = value;
	}

	void Datum::PushBack(const std::string& value)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::String);
		_type = DatumTypes::String;

		if (_size == _capacity)
		{
			Reserve(_size + 1);
		}
		++_size;
		new (_data.s + _size - 1) std::string(value);
	}

	void Datum::PushBack(RTTI* const value)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::Pointer);
		_type = DatumTypes::Pointer;

		if (_size == _capacity)
		{
			Reserve(_size + 1);
		}
		++_size;
		_data.p[_size - 1] = value;
	}

	void Datum::PushBack(Scope* const value)
	{
		assert(_type == DatumTypes::Unknown || _type == DatumTypes::Table);
		_type = DatumTypes::Table;

		if (_size == _capacity)
		{
			Reserve(_size + 1);
		}
		++_size;
		_data.t[_size - 1] = value;
	}

	void Datum::PopBack()
	{
		if (_type == DatumTypes::Unknown || _size == 0)
		{
			throw std::runtime_error("Empty Datum or Unknown Datum, nothing to popback");
		}

		if (_type == DatumTypes::String)
		{
			_data.s[_size - 1].~basic_string();
		}
		--_size;

	}

	std::int32_t& Datum::FrontInteger()
	{
		assert(_type == DatumTypes::Integer);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.i[0];
	}

	float& Datum::FrontFloat()
	{
		assert(_type == DatumTypes::Float);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.f[0];
	}

	glm::vec4& Datum::FrontVector()
	{
		assert(_type == DatumTypes::Vector);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.v[0];
	}

	glm::mat4& Datum::FrontMatrix()
	{
		assert(_type == DatumTypes::Matrix);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.m[0];
	}

	std::string& Datum::FrontString()
	{
		assert(_type == DatumTypes::String);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.s[0];
	}

	RTTI* Datum::FrontPointer()
	{
		assert(_type == DatumTypes::Pointer);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.p[0];
	}

	const std::int32_t& Datum::FrontInteger() const
	{
		assert(_type == DatumTypes::Integer);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.i[0];
	}

	const float& Datum::FrontFloat() const
	{
		assert(_type == DatumTypes::Float);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.f[0];
	}

	const glm::vec4& Datum::FrontVector() const
	{
		assert(_type == DatumTypes::Vector);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.v[0];
	}

	const glm::mat4& Datum::FrontMatrix() const
	{
		assert(_type == DatumTypes::Matrix);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.m[0];
	}

	const std::string& Datum::FrontString() const
	{
		assert(_type == DatumTypes::String);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.s[0];
	}

	RTTI* const Datum::FrontPointer() const
	{
		assert(_type == DatumTypes::Pointer);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.p[0];
	}

	std::int32_t& Datum::BackInteger()
	{
		assert(_type == DatumTypes::Integer);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.i[_size-1];
	}

	float& Datum::BackFloat()
	{
		assert(_type == DatumTypes::Float);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.f[_size - 1];
	}

	glm::vec4& Datum::BackVector()
	{
		assert(_type == DatumTypes::Vector);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.v[_size - 1];
	}

	glm::mat4& Datum::BackMatrix()
	{
		assert(_type == DatumTypes::Matrix);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.m[_size - 1];
	}

	std::string& Datum::BackString()
	{
		assert(_type == DatumTypes::String);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.s[_size - 1];
	}

	RTTI* Datum::BackPointer()
	{
		assert(_type == DatumTypes::Pointer);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.p[_size - 1];
	}

	const std::int32_t& Datum::BackInteger() const
	{
		assert(_type == DatumTypes::Integer);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.i[_size - 1];
	}

	const float& Datum::BackFloat() const
	{
		assert(_type == DatumTypes::Float);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.f[_size - 1];
	}

	const glm::vec4& Datum::BackVector() const
	{
		assert(_type == DatumTypes::Vector);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.v[_size - 1];
	}

	const glm::mat4& Datum::BackMatrix() const
	{
		assert(_type == DatumTypes::Matrix);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.m[_size - 1];
	}

	const std::string& Datum::BackString() const
	{
		assert(_type == DatumTypes::String);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.s[_size - 1];
	}

	RTTI* const Datum::BackPointer() const
	{
		assert(_type == DatumTypes::Pointer);
		if (_size == 0)
		{
			throw std::runtime_error("Empty Datum, theres nothing there!");
		}
		return _data.p[_size - 1];
	}

	std::size_t Datum::Find(const std::int32_t value)
	{
		assert(_type == DatumTypes::Integer);
		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.i[i] == value)
			{
				return i;
			}
		}
		return size_t(SIZE_MAX);
	}

	std::size_t Datum::Find(const float value)
	{
		assert(_type == DatumTypes::Float);
		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.f[i] == value)
			{
				return i;
			}
		}
		return size_t(SIZE_MAX);
	}

	std::size_t Datum::Find(const glm::vec4 value)
	{
		assert(_type == DatumTypes::Vector);
		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.v[i] == value)
			{
				return i;
			}
		}
		return size_t(SIZE_MAX);
	}

	std::size_t Datum::Find(const glm::mat4 value)
	{
		assert(_type == DatumTypes::Matrix);
		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.m[i] == value)
			{
				return i;
			}
		}
		return size_t(SIZE_MAX);
	}

	std::size_t Datum::Find(const std::string& value)
	{
		assert(_type == DatumTypes::String);
		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.s[i] == value)
			{
				return i;
			}
		}
		return size_t(SIZE_MAX);
	}

	std::size_t Datum::Find(const RTTI* value)
	{
		assert(_type == DatumTypes::Pointer);
		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.p[i] == value)
			{
				return i;
			}
		}
		return size_t(SIZE_MAX);
	}

	bool Datum::RemoveAt(size_t index)
	{
		assert(!_isExternal);
		assert(_type != DatumTypes::Unknown);

		if (index >= _size) //out of bounds or sizemax from a failed find
		{
			return false;
		}

		if (_type == DatumTypes::String)
		{
			_data.s[index].~basic_string();
		}

		memmove((_data.b + index * _typeSizes[static_cast<int>(_type)]), _data.b + (index + 1) * _typeSizes[static_cast<int>(_type)], _typeSizes[static_cast<int>(_type)] * (_size - index));


		--_size;
		return true;
	}

	bool Datum::Remove(const std::int32_t value)
	{
		assert(_type == DatumTypes::Integer);
		return RemoveAt(Find(value));
	}

	bool Datum::Remove(const float value)
	{
		assert(_type == DatumTypes::Float);
		return RemoveAt(Find(value));

	}

	bool Datum::Remove(const glm::vec4 value)
	{
		assert(_type == DatumTypes::Vector);
		return RemoveAt(Find(value));
	}

	bool Datum::Remove(const glm::mat4 value)
	{
		assert(_type == DatumTypes::Matrix);
		return RemoveAt(Find(value));
	}

	bool Datum::Remove(const std::string& value)
	{
		assert(_type == DatumTypes::String);
		return RemoveAt(Find(value));
	}

	bool Datum::Remove(const RTTI* value)
	{
		assert(_type == DatumTypes::Pointer);
		return RemoveAt(Find(value));
	}

	std::string Datum::ToString(size_t index)
	{
		assert(_type != DatumTypes::Unknown);
		if (index >= _size)
		{
			throw std::out_of_range("Index greater than or equal to size");
		}
		
		switch (_type) 
		{
			case DatumTypes::Integer:
				return std::to_string(_data.i[index]);
				break;
			case DatumTypes::Float:
				return std::to_string(_data.f[index]);
				break;
			case DatumTypes::String:
				return (_data.s[index]);
				break;
			case DatumTypes::Vector:
				return glm::to_string(_data.v[index]);
				break;
			case DatumTypes::Matrix:
				return glm::to_string(_data.m[index]);
				break;
			case DatumTypes::Pointer:
				return (_data.p[index])->ToString();
				break;
			default:
				assert(false);
				return "null";
		}
	}


	void Datum::SetFromStringInteger(const std::string& value, size_t index)
	{
		assert(_type == DatumTypes::Integer);
		SetInteger(std::stoi(value), index);
	}

	void Datum::SetFromStringFloat(const std::string& value, size_t index)
	{
		assert(_type == DatumTypes::Float);
		SetFloat(std::stof(value), index);
	}

	void Datum::SetFromStringVector(const std::string& value, size_t index)
	{
		assert(_type == DatumTypes::Vector);
		glm::vec4 v{};
		
		sscanf_s(value.c_str(), "vec4(%f, %f, %f, %f)", &v.x, &v.y, &v.z, &v.w);
		SetVector(v, index);
	}

	void Datum::SetFromStringMatrix(const std::string& value, size_t index)
	{
		assert(_type == DatumTypes::Matrix);
		glm::mat4 m{};

		sscanf_s(value.c_str(), "mat4((%f, %f, %f, %f ), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))",
			&m[0][0], &m[0][1], &m[0][2], &m[0][3],
			&m[1][0], &m[1][1], &m[1][2], &m[1][3],
			&m[2][0], &m[2][1], &m[2][2], &m[2][3],
			&m[3][0], &m[3][1], &m[3][2], &m[3][3] );

		SetMatrix(m, index);
	}

	void Datum::PushBackFromStringInteger(const std::string& input)
	{
		PushBack(std::stoi(input));
	}

	void Datum::PushBackFromStringFloat(const std::string& input)
	{
		PushBack(std::stof(input));
	}

	void Datum::PushBackFromStringVector(const std::string& input)
	{
		glm::vec4 v{};
		sscanf_s(input.c_str(), "vec4(%f, %f, %f, %f)", &v.x, &v.y, &v.z, &v.w);
		PushBack(v);
	}

	void Datum::PushBackFromStringMatrix(const std::string& input)
	{
		glm::mat4 m{};
		sscanf_s(input.c_str(), "mat4((%f, %f, %f, %f ), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))",
			&m[0][0], &m[0][1], &m[0][2], &m[0][3],
			&m[1][0], &m[1][1], &m[1][2], &m[1][3],
			&m[2][0], &m[2][1], &m[2][2], &m[2][3],
			&m[3][0], &m[3][1], &m[3][2], &m[3][3]);
		PushBack(m);
	}

}
