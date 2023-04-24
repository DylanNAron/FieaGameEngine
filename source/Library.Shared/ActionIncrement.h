#pragma once
#include "Action.h"
#include "RTTI.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Increment Action. Contains a string target attribute and a integer step attribute. Every update it will increment the found target by the step.
	/// </summary>
	class ActionIncrement : public Action
	{
		RTTI_DECLARATIONS(ActionIncrement, Action);

	public:
		ActionIncrement();
		virtual ~ActionIncrement() = default;
		ActionIncrement(const ActionIncrement& other) = default;
		ActionIncrement(ActionIncrement&& rhs) = default;
		ActionIncrement& operator=(const ActionIncrement& other) = default;
		ActionIncrement& operator=(ActionIncrement&& rhs) = default;

		/// <summary>
		/// Signature for Action Increment: name, target, step
		/// </summary>
		/// <returns></returns>
		static const Vector<Signature> Signatures();

		/// <summary>
		/// Increments the target by the step
		/// </summary>
		/// <param name="world">const reference to game world</param>
		virtual void Update(World& world) override;

		/// <summary>
		/// Cloning (virtual constructor) used for copying
		/// </summary>
		/// <returns>A scope Pointer to new clone of actionList</returns>
		[[nodiscard]] virtual gsl::owner<Scope*> Clone() const override;

	private:
		std::string _target;
		int32_t _step { 1 }; //default 1 increment

	};

	ConcreteFactory(ActionIncrement, Scope);
}

