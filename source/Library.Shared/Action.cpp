#include "pch.h"
#include "Action.h"
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Action);

	const std::string& Action::Name() const
	{
		return _name;
	}
	void Action::SetName(const std::string& name)
	{
		_name = name;
	}
	const Vector<Signature> Action::Signatures()
	{
		return Vector<Signature>
		{
			{"Name", Datum::DatumTypes::String, 1, offsetof(Action, _name)}
		};
	}

	Action::Action(RTTI::IdType typeId) :
		Attributed(typeId)
	{
	}
}