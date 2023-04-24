#include "pch.h"
#include "Attributed.h"
#include "Vector.h"

using namespace std::string_literals;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Attributed);

	Attributed::Attributed(RTTI::IdType typeId)
	{
		Populate(typeId);
	}

	Attributed::Attributed(const Attributed& other) :
		Scope(other)
	{
		Populate(other.TypeIdInstance()); //repopulate so that prescribed attributes are set to this instance (called from other for proper dynamic dispatch)
	}

	Attributed& Attributed::operator=(const Attributed& other)
	{
		Scope::operator=(other);
		Populate(other.TypeIdInstance());
		return *this;
	}

	Attributed::Attributed(Attributed&& rhs) noexcept :
		Scope(std::move(rhs))
	{
		Populate(rhs.TypeIdInstance()); 
	}

	Attributed& Attributed::operator=(Attributed&& rhs) noexcept
	{
		Scope::operator=(std::move(rhs));
		Populate(rhs.TypeIdInstance());
		return *this;
	}

	Datum& Attributed::AppendAuxiliaryAttribute(const std::string& attributeName)
	{
		if (IsPrescribedAttribute(attributeName))
		{
			throw std::runtime_error("Attempting to append a prescribed attribute as auxiliary!");
		}
		return Append(attributeName);
	}


	bool Attributed::IsAttribute(const std::string& attributeName) const
	{
		return _tableMap.ContainsKey(attributeName);
	}

	bool Attributed::IsPrescribedAttribute(const std::string& attributeName) const
	{
		Vector<Signature>& typeSignatures = TypeRegistry::GetInstance()->GetSignaturesForTypeId(TypeIdInstance());
		for (auto& it : typeSignatures)
		{
			if (it.Name == attributeName)
			{
				return true;
			}
		}
		return false;
	}

	bool Attributed::IsAuxiliaryAttribute(const std::string& attributeName) const
	{
		return !IsPrescribedAttribute(attributeName) && IsAttribute(attributeName);
	}


	void Attributed::Populate(RTTI::IdType typeId)
	{
		Append("this"s) = reinterpret_cast<RTTI*>(this); //First Prescribed attribute is RTTI of this
		Vector<Signature>& typeSignatures = TypeRegistry::GetInstance()->GetSignaturesForTypeId(typeId);
		
		for (auto& it : typeSignatures)
		{
			if (it.Type == Datum::DatumTypes::Table) //scopes are internally stored ; cannot just call append scope
			{
				Datum& curPrescribed = Append(it.Name);
				curPrescribed.SetType(Datum::DatumTypes::Table);
				curPrescribed.Reserve(it.Size);
			}
			else //all other prescribed attributes are externally stored
			{
				void* pointerToPrescribed = reinterpret_cast<std::byte*>(this) + it.Offset;
				Datum& curPrescribed = Append(it.Name);
				curPrescribed.SetStorage(it.Type, pointerToPrescribed, it.Size);
			}
		}
	}

	std::pair<size_t, size_t> Attributed::Attributes() const
	{
		return std::make_pair(0, _orderVector.Size());
	}

	std::pair<size_t, size_t> Attributed::PrescribedAttributes() const
	{
		return std::make_pair(0, TypeRegistry::GetInstance()->GetSignaturesForTypeId(TypeIdInstance()).Size()+1); //+1 for "this" attribute

	}

	std::pair<size_t, size_t> Attributed::AuxiliaryAttributesRange() const
	{
		return std::make_pair(TypeRegistry::GetInstance()->GetSignaturesForTypeId(TypeIdInstance()).Size()+1, _orderVector.Size());

	}

	const Vector<std::pair<const std::string, Datum>*> Attributed::AuxiliaryAttributes() const
	{
		Vector<std::pair<const std::string, Datum>*> auxiliaryVector{};

		auto [start, end] = AuxiliaryAttributesRange();
		for (; start < end; ++start)
		{
			auxiliaryVector.PushBack(_orderVector[start]);
		}

		return auxiliaryVector;
	}

}