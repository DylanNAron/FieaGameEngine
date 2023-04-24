#include "pch.h"
#include "ActionIncrement.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionIncrement);

	ActionIncrement::ActionIncrement() :
		Action(TypeIdClass())
	{
	}

	const Vector<Signature> ActionIncrement::Signatures()
	{
		return Vector<Signature>
		{
			{"Name", Datum::DatumTypes::String, 1, offsetof(ActionIncrement, _name)},
			{"Target", Datum::DatumTypes::String, 1, offsetof(ActionIncrement, _target)},
			{"Step", Datum::DatumTypes::Integer, 1, offsetof(ActionIncrement, _step)},
		};
	}

	void ActionIncrement::Update([[maybe_unused]] World& world)
	{
		Scope* foundScope{ nullptr };
		Datum* foundDatum = Search(_target, foundScope);
		assert(foundDatum != nullptr);
		foundDatum->SetInteger(foundDatum->GetInteger() += _step);
	}


	gsl::owner<Scope*> ActionIncrement::Clone() const
	{
		return  new ActionIncrement(*this);
	}
}
