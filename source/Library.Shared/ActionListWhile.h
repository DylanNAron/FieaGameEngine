#include "ActionList.h"

namespace FieaGameEngine
{
	/// <summary>
	/// While loop action list. contains an integer member condition. While condition is nonzero this ActionListWhile will loop through its actions and enact them (update)
	/// </summary>
	class ActionListWhile : public ActionList
	{

		RTTI_DECLARATIONS(ActionListWhile, ActionList);

	public:

		ActionListWhile();
		virtual ~ActionListWhile() = default;
		ActionListWhile(const ActionListWhile& other) = default;
		ActionListWhile(ActionListWhile&& rhs) = default;
		ActionListWhile& operator=(const ActionListWhile& other) = default;
		ActionListWhile& operator=(ActionListWhile&& rhs) = default;


		/// <summary>
		/// Signature for ActionList, used to register the ActionList type for instatiation.
		/// </summary>
		/// <returns>Vector of actionList signatures</returns>
		static const Vector<Signature> Signatures();

		/// <summary>
		/// Update each action from the Actions prescribed attribute
		/// </summary>
		/// <param name="world">const reference to the game world</param>
		virtual void Update(World& world) override;

		/// <summary>
		/// Getter for the condition attribute
		/// </summary>
		/// <returns>condition attributed integer value</returns>
		const int32_t& Condition() const;

		/// <summary>
		/// Setter for the condition attribute
		/// </summary>
		/// <param name="value">value to set condition to</param>
		void SetCondition(const int32_t& value);

		/// <summary>
		/// Cloning (virtual constructor) used for copying
		/// </summary>
		/// <returns>A scope Pointer to new clone of actionListWhile</returns>
		[[nodiscard]] virtual gsl::owner<Scope*> Clone() const override;

	protected:

		int32_t _condition{ 0 }; //used in place of a boolean so checking zero or nonzero

	};

	ConcreteFactory(ActionListWhile, Scope);


}