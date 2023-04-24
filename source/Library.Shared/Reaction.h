#pragma once
#include "EventSubscriber.h"
#include "ActionList.h"
 
namespace FieaGameEngine
{
	/// <summary>
	/// Reaction Abstace base class. This inherits from ActionList and EventSubscriber so when Reaction::Notify is called it will invoke ActionList::Update
	/// </summary>
	class Reaction : public ActionList, public EventSubscriber
	{
		RTTI_DECLARATIONS(Reaction, ActionList);

	protected:
		explicit Reaction(RTTI::IdType typeId);
		virtual ~Reaction() = default;

	};

}