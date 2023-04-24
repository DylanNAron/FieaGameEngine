#pragma once
#include "Action.h"
#include "Factory.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Action that creates and enqueues an event on update. This is used for the reaction system.
	/// </summary>
	class ActionEvent final: public Action
	{
		RTTI_DECLARATIONS(ActionEvent, Action);

	public:

		/// <summary>
		/// Default ActionEvent constructor, which calls the Attributed construction via typeId
		/// </summary>
		ActionEvent();

		/// <summary>
		/// Signature for ActionEvent
		/// </summary>
		/// <returns>Vector of ActionEvent Signatures</returns>
		static const Vector<Signature> Signatures();

		/// <summary>
		/// update method which takes in the game time to update action.  Create an attributed event, assign its world and subtype, copy all auxiliary parameters into the event and queue the event with the given delay.
		/// </summary>
		/// <param name="time">const reference to Game World</param>
		void Update(World& time) override;

	private:

		std::string _subtype;
		std::int32_t _delay{ 0 };

	};

	ConcreteFactory(ActionEvent, Scope);
}