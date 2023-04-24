#pragma once
#include "Reaction.h"
#include "Factory.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Reaction Attributed class that can be notified. A Gameobject can contain a reactionAttributed auxiliary attribute and this reaction can subscribe to events and be notified by accepting a payload and causing its actions to update.
	/// </summary>
	class ReactionAttributed : public Reaction
	{
		RTTI_DECLARATIONS(ReactionAttributed, Reaction);

	public:

		/// <summary>
		/// Default ReactionAttributed constructor which implements attributed construction.
		/// </summary>
		ReactionAttributed();

		/// <summary>
		/// Signature for EventMessageAttributed, used to register the EventMessageAttributed type for instantiation.
		/// </summary>
		/// <returns></returns>
		static const Vector<Signature> Signatures();

		/// <summary>
		/// Notify method override for the abstract base class event subscriber.
		/// </summary>
		/// <param name="eventPublisher"> passed in reference to the event Publishere </param>
		void Notify(const EventPublisher& eventPublisher) override;

	private:

		std::string _subtype{};

	};
	
	ConcreteFactory(ReactionAttributed, Scope);
}
