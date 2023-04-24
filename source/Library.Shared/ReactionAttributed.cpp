#include "pch.h"
#include "ReactionAttributed.h"
#include "EventMessageAttributed.h"
#include "EventPublisher.h"
#include <Event.h>


namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ReactionAttributed);

	ReactionAttributed::ReactionAttributed() :
		Reaction(TypeIdClass())
	{
	}

	const Vector<Signature> ReactionAttributed::Signatures()
	{
		return Vector<Signature>
		{
			{"Name", Datum::DatumTypes::String, 1, offsetof(ReactionAttributed, _name)},
			{"Actions", Datum::DatumTypes::Table, 0, 0 },
			{"Subtype", Datum::DatumTypes::String, 1, offsetof(ReactionAttributed, _subtype)},
		};
	}

	void ReactionAttributed::Notify(const EventPublisher& eventPublisher)
	{
		auto event = eventPublisher.As<Event<EventMessageAttributed>>();
		if (event != nullptr)
		{
			auto message = event->Message().As<EventMessageAttributed>();
			if (message->GetSubtype() == _subtype)
			{
				for (auto& messageAuxAttr : message->AuxiliaryAttributes())
				{
					AppendAuxiliaryAttribute(messageAuxAttr->first) = messageAuxAttr->second;
				}

				Update(message->GetWorld());
			}
		}

	}



}
