#include "pch.h"
#include "ActionList.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionList);

	ActionList::ActionList() :
		Action(TypeIdClass())
	{
	}

	ActionList::ActionList(RTTI::IdType typeId) :
		Action(typeId)
	{
	}

	const Vector<Signature> ActionList::Signatures()
	{
		return Vector<Signature>
		{
			{"Name", Datum::DatumTypes::String, 1, offsetof(ActionList, _name)},
			{"Actions", Datum::DatumTypes::Table, 0, 0 },
		};
	}

	void ActionList::Update(World& world)
	{
		Datum& actions = Actions();
		for (size_t i = 0; i < actions.Size(); ++i)
		{
			Scope& child = actions.GetTable(i);
			assert(child.Is(Action::TypeIdClass()));
			static_cast<Action&>(actions.GetTable(i)).Update(world);
		}
	}
	Datum& ActionList::Actions()
	{
		assert(_orderVector[2]->second != nullptr); //"Actions" attribute at index 2
		Datum& actions = _orderVector[2]->second;
		return actions;
	}

	gsl::owner<Scope*> ActionList::Clone() const
	{
		return  new ActionList(*this);
	}
}