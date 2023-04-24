#pragma once
#include "Action.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Concrete action list, holds a list of actions while itself is also an action. Used to be derived for other types of actions such as ActionListWhile
	/// </summary>
	class ActionList : public Action
	{
		RTTI_DECLARATIONS(ActionList, Action);

	public:

		ActionList();
		virtual ~ActionList() = default;
		ActionList(const ActionList& other) = default;
		ActionList(ActionList&& rhs) = default;
		ActionList& operator=(const ActionList& other) = default;
		ActionList& operator=(ActionList&& rhs) = default;


		/// <summary>
		/// Signature for ActionList, used to register the ActionList type for instatiation.
		/// </summary>
		/// <returns>Vector of actionList signatures</returns>
		static const Vector<Signature> Signatures();

		/// <summary>
		/// Update each action from the Actions prescribed attribute
		/// </summary>
		/// <param name="time">const reference to the game world</param>
		virtual void Update(World& world) override;

		/// <summary>
		/// Getter for the Actions prescribed attribute
		/// </summary>
		/// <returns>reference to the actions datum</returns>
		Datum& Actions();

		/// <summary>
		/// Cloning (virtual constructor) used for copying
		/// </summary>
		/// <returns>A scope Pointer to new clone of actionList</returns>
		[[nodiscard]] virtual gsl::owner<Scope*> Clone() const override;

	protected:
		ActionList(RTTI::IdType typeId);

	};

	ConcreteFactory(ActionList, Scope);
}

