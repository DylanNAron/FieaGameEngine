#include "pch.h"
#include "ActionEvent.h"
#include "EventMessageAttributed.h"
#include "Event.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionEvent);

	ActionEvent::ActionEvent() :
		Action(TypeIdClass())
	{
	}

	const Vector<Signature> ActionEvent::Signatures()
	{
		return Vector<Signature>
		{
			{"Name", Datum::DatumTypes::String, 1, offsetof(ActionEvent, _name)},
			{"Subtype", Datum::DatumTypes::String, 1, offsetof(ActionEvent, _subtype)},
			{ "Delay", Datum::DatumTypes::String, 1, offsetof(ActionEvent, _delay) }
		};
	}

	void ActionEvent::Update(World& world)
	{
		EventMessageAttributed eventMessage;
		eventMessage.SetSubtype(_subtype);
		eventMessage.SetWorld(world);

		auto [auxPosition, endAux] = AuxiliaryAttributesRange();
		for (; auxPosition < endAux; ++auxPosition)
		{
			eventMessage.AppendAuxiliaryAttribute(_orderVector[auxPosition]->first) = _orderVector[auxPosition]->second;
		}

		auto event = std::make_shared<Event<EventMessageAttributed>>(eventMessage);
		world.GetEventQueue().Enqueue(event, world.GetGameTime(), std::chrono::milliseconds(_delay));

	}

}
