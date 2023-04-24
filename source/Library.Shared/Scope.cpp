#include "pch.h"
#include "Scope.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Scope);

	Scope::~Scope()
	{
		Clear();
	}

	Scope::Scope(size_t capacity) :
		_tableMap(capacity)
	{
	}

	Scope::Scope(const Scope& other)
	{
		for (auto& otherIterator : other._orderVector)
		{
			Datum& otherDatum = otherIterator->second;
			Datum newDatum = otherIterator->second;
			if (newDatum.Type() == Datum::DatumTypes::Table)
			{
				for (size_t i = 0; i < newDatum.Size(); ++i)
				{
					Scope* scopeClone = otherDatum[i].Clone();
					scopeClone->_parent = this;
					newDatum.SetTable(scopeClone, i);
				}
			}

			auto insertionPair = _tableMap.Insert(std::make_pair(otherIterator->first, newDatum));
			_orderVector.PushBack(&(*insertionPair.first));
		}
	}

	Scope& Scope::operator=(const Scope& other)
	{
		Scope copy(other);
		std::swap(*this, copy);
		return *this;
	}

	Scope::Scope(Scope&& rhs) noexcept :
		_tableMap(std::move(rhs._tableMap)), _orderVector(std::move(rhs._orderVector))
	{

		//rhs get rid of parent and clear ; parent of moved scope will be null (so it may be stack allocated (root scope) )
		if (rhs._parent != nullptr)
		{
			rhs.Orphan();
			delete &rhs;
		}
		else
		{
			rhs.Clear();
		}

		//fix parents of any scopes
		for (auto& it : _orderVector)
		{
			Datum& curDatum = it->second;
			if (curDatum.Type() == Datum::DatumTypes::Table)
			{
				for (size_t i = 0; i < curDatum.Size(); ++i)
				{
					curDatum[i]._parent = this;
				}
			}
		}


	}

	Scope& Scope::operator=(Scope&& rhs) noexcept
	{
		//clear and orphan scope we are assigning 
		if (_parent != nullptr)
		{
			Orphan();
		}
		Clear();
	
		//rhs get rid of parent and clear ; parent of moved scope will be null (so it may be stack allocated (root scope) )
		_tableMap = std::move(rhs._tableMap);
		_orderVector = std::move(rhs._orderVector);
		if (rhs._parent != nullptr)
		{
			rhs.Orphan();
			rhs._parent = nullptr;
			delete& rhs;
		}
		else
		{
			rhs.Clear();
		}


		//fix parents of any scopes
		for (auto& it : _orderVector)
		{
			Datum& curDatum = it->second;
			if (curDatum.Type() == Datum::DatumTypes::Table)
			{
				for (size_t i = 0; i < curDatum.Size(); ++i)
				{
					curDatum[i]._parent = this;
				}
			}
		}


		return *this;
	}

	bool Scope::operator==(const Scope& other) const
	{
		if (Size() != other.Size())
		{
			return false;
		}

		for (size_t i = 0; i < other.Size(); ++i)
		{
			if (_orderVector[i]->first == "this" && other._orderVector[i]->first == "this")
			{
				continue;
			}

			if (_orderVector[i]->second != other._orderVector[i]->second)
			{
				return false;
			}
		}

		return true;
	}

	bool Scope::operator!=(const Scope& other) const
	{
		return !(operator==(other));
	}

	bool Scope::Equals(const RTTI* rhs) const
	{
		if (rhs == nullptr)
		{
			return false;
		}
		return operator==(*(rhs->As<Scope>()));
	}

	Datum& Scope::operator[](const std::string& key)
	{
		return Append(key);
	}

	Datum& Scope::operator[](size_t index)
	{
		return _orderVector[index]->second;
	}

	Datum& Scope::Append(const std::string& key)
	{
		assert(!key.empty());
		
		std::pair<Hashmap<std::string, Datum>::Iterator, bool> insertionPair = _tableMap.Insert(std::make_pair(key, Datum()));

		if (insertionPair.second) // if is inserted
		{
			_orderVector.PushBack( &(*insertionPair.first) );
		}

		return (*insertionPair.first).second;
	}

	Scope& Scope::AppendScope(const std::string& key)
	{
		assert(!key.empty());

		Datum& tableDatum = Append(key);

		Scope* scope = new Scope();
		scope->_parent = this;
		tableDatum.PushBack(scope);

		return *scope;
	}

	gsl::owner<Scope*> Scope::Clone() const
	{
		return new Scope(*this);
	}

	Scope* Scope::GetParent() const
	{
		return _parent;
	}

	size_t Scope::Size() const
	{
		return _orderVector.Size();
	}

	Datum* Scope::Search(const std::string& key, Scope*& foundscope)
	{
		foundscope = nullptr;
		if (_tableMap.ContainsKey(key))
		{
			foundscope = this;
			return &_tableMap.At(key);
		}
		else
		{
			if (_parent != nullptr)
			{
				//Searching Up the hierarchy 
				return _parent->Search(key, foundscope); 
			}
			else
			{
				return nullptr;
			}
		}
	}


	Datum* Scope::Find(const std::string& key)
	{
		if (_tableMap.ContainsKey(key))
		{
			return &_tableMap.At(key);
		}
		else
		{
			return nullptr;
		}
	}

	std::pair<Datum*, size_t> Scope::FindContainedScope(const Scope* scopeToFind)
	{
		std::pair<Datum*, size_t> resultPair(nullptr, 0);
		for (auto& it : _orderVector)
		{
			Datum& curDatum = it->second;
			if (curDatum.Type() == Datum::DatumTypes::Table)
			{
				for (size_t i = 0; i < curDatum.Size(); ++i)
				{
					if (scopeToFind == &curDatum.GetTable(i))
					{
						return resultPair = std::make_pair(&curDatum, i);
					}
				}
			}
		}
		assert(resultPair.first != nullptr); //Find Contained Scope not allowed to return null , has to find scope!
		return resultPair;
	}

	gsl::owner<Scope*> Scope::Orphan()
	{
		Scope* parent = _parent;
		if (parent != nullptr)
		{
			auto [foundDatum, index] = parent->FindContainedScope(this);
			foundDatum->RemoveAt(index);
			_parent = nullptr;
		}

		return this;
	}

	void Scope::Adopt(Scope& child, const std::string& key)
	{

		if (&child == this || key.empty() || IsAncestor(child) )
		{
			throw std::runtime_error("Attempted self adoption, ancestor adoption , or provided an empty key.");
		}

		Datum& datum = Append(key);
		if (datum.Type() != Datum::DatumTypes::Table && datum.Type() != Datum::DatumTypes::Unknown)
		{
			throw std::runtime_error("Datum found that was not of type table to adopt scope");
		}

		Scope* orphanedChild = child.Orphan();
		orphanedChild->_parent = this;
		datum.PushBack(orphanedChild);
	}

	void Scope::Clear()
	{
		for (auto& it : _orderVector)
		{
			Datum& curDatum = it->second;
			if (curDatum.Type() == Datum::DatumTypes::Table)
			{
				for (size_t i = 0; i < (it->second).Size(); ++i)
				{
					delete &curDatum[i];
				}
			}
		}

		_tableMap.Clear();
		_orderVector.Clear();
	}


	bool Scope::IsAncestor(const Scope& scopeToCheck) const
	{
		bool result = false;
		Scope* parent = this->_parent;

		while (parent != nullptr)
		{
			if (parent == scopeToCheck._parent)
			{
				result = true;
			}
			parent = parent->_parent;
		}
		return result;
	}


}


