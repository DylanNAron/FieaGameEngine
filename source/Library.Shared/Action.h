#pragma once
#include "Attributed.h"
#include "GameTime.h"
#include "World.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Abstract base class that extends attributed to represent the "verbs" in our game engine.
	/// </summary>
	class Action : public Attributed
	{
		RTTI_DECLARATIONS(Action, Attributed);
		
	public:
		/// <summary>
		/// Pure virtual update method which takes in the game time to update action
		/// </summary>
		/// <param name="world">const reference to the game World</param>
		virtual void Update(World& world) = 0;

		/// <summary>
		/// Getter for the prescribed attribute Name
		/// </summary>
		/// <returns>const string reference of the Name attribute</returns>
		const std::string& Name() const;

		/// <summary>
		/// Setter for the prescribed attribute Name
		/// </summary>
		/// <param name="name">const string reference</param>
		void SetName(const std::string& name);

		/// <summary>
		/// Signature for Action
		/// </summary>
		/// <returns>Vector of Action Signatures</returns>
		static const Vector<Signature> Signatures();

	protected:
		Action(RTTI::IdType typeId);

		std::string _name;

	};

}

