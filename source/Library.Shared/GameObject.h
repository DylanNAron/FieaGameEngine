#pragma once
#include "Attributed.h"
#include "RTTI.h"
#include "glm/glm.hpp"
#include "Vector.h"
#include "Signature.h"
#include "Factory.h"
#include "GameTime.h"
#include "Action.h"
#include "World.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Another Wrapper for a table (Attributed Scope), to be used as basis for all object used in our game engine that will be updated.
	/// </summary>
	class GameObject : public Attributed
	{
		RTTI_DECLARATIONS(GameObject, Attributed);

	public:
		GameObject();
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = default;
		GameObject(GameObject&& rhs) = default;
		GameObject& operator=(const GameObject& other) = default;
		GameObject& operator=(GameObject&& rhs) = default;

		std::string Name;
		glm::vec4 Position;
		glm::vec4 Rotation;
		glm::vec4 Scale;

		/// <summary>
		/// Signature for GameObject, used to register the GameObject type for instatiation.
		/// </summary>
		/// <returns></returns>
		static const Vector<Signature> Signatures();

		/// <summary>
		/// ToString Method for GameObject
		/// </summary>
		/// <returns>String representation of GameObject</returns>
		//std::string ToString() const override;

		/// <summary>
		/// takes a const reference to a GameTime instance and calls Update on all of its children.
		/// </summary>
		/// <param name="world">Game World</param>
		virtual void Update(World& world);

		/// <summary>
		/// Getter for the children of a gameobject
		/// </summary>
		/// <returns>Datum reference to the children attribute</returns>
		Datum& Children();

		/// <summary>
		/// Get the child of a gameobject, based on index (defaulted to 0)
		/// </summary>
		/// <param name="index">size_t child index</param>
		/// <returns>Child reference of Gameobject</returns>
		/// <exception cref="Index">throw exception if out of bounds</exception>
		GameObject& GetChild(size_t index = 0);

		/// <summary>
		/// Getter for the actions of a gameobject
		/// </summary>
		/// <returns>Datum reference to the actions attribute</returns>
		Datum& Actions();


		/// <summary>
		/// Cloning (virtual constructor) used for copying
		/// </summary>
		/// <returns>A scope Pointer to new clone of gameobject</returns>
		[[nodiscard]] virtual gsl::owner<Scope*> Clone() const override;

	private:
		const size_t _childrenIndex{ 5 };
		const size_t _actionsIndex{ 6 };
	};

	ConcreteFactory(GameObject, Scope);
}

