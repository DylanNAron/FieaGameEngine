#include "pch.h"
#include "EventMessageAttributed.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(EventMessageAttributed);

	EventMessageAttributed::EventMessageAttributed() :
		Attributed(TypeIdClass())
	{
	}

	EventMessageAttributed::EventMessageAttributed(const std::string& subtype, World* world) :
		Attributed(TypeIdClass()), _world(world), _subtype(subtype)
	{
	}

	const Vector<Signature> EventMessageAttributed::Signatures()
	{
		return Vector<Signature>
		{
			{"Subtype", Datum::DatumTypes::String, 1, offsetof(EventMessageAttributed, _subtype)},
		};
	}

	const std::string& EventMessageAttributed::GetSubtype() const
	{
		return _subtype;
	}

	void EventMessageAttributed::SetSubtype(const std::string& subtype)
	{
		_subtype = subtype;
	}

	World& EventMessageAttributed::GetWorld() const
	{
		return *_world;
	}

	void EventMessageAttributed::SetWorld(World& world)
	{
		_world = &world;
	}
}
