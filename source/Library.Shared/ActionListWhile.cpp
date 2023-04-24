#include "pch.h"
#include "ActionListWhile.h"

namespace FieaGameEngine
{

	RTTI_DEFINITIONS(ActionListWhile);

	ActionListWhile::ActionListWhile() :
		ActionList(TypeIdClass())
	{
	}


	const Vector<Signature> ActionListWhile::Signatures()
	{
		return Vector<Signature>
		{
			{"Name", Datum::DatumTypes::String, 1, offsetof(ActionListWhile, _name)},
			{ "Actions", Datum::DatumTypes::Table, 0, 0 },
			{ "Condition", Datum::DatumTypes::Integer, 1,  offsetof(ActionListWhile, _condition) },
		};
	}

	void ActionListWhile::Update([[maybe_unused]] World& world)
	{
		if (_condition)
		{
			Datum& actions = Actions();
			for (size_t i = 0; i < actions.Size(); ++i)
			{
				Scope& child = actions.GetTable(i);
				assert(child.Is(Action::TypeIdClass()));
				static_cast<Action&>(actions.GetTable(i)).Update(world);
			}
		}

	}

	void ActionListWhile::SetCondition(const int32_t& value)
	{
		_condition = value;
	}

	const int32_t& ActionListWhile::Condition() const
	{
		return _condition;
	}

	gsl::owner<Scope*> ActionListWhile::Clone() const
	{
		return  new ActionListWhile(*this);
	}

}