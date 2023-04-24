#include "pch.h"
#include "GameObject.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(GameObject);

	GameObject::GameObject() :
		Attributed(TypeIdClass())
	{
	}

	const Vector<Signature> GameObject::Signatures()
	{
		return Vector<Signature>
		{
			{"Name", Datum::DatumTypes::String, 1, offsetof(GameObject, Name)},
			{ "Position", Datum::DatumTypes::Vector, 1, offsetof(GameObject, Position) },
			{ "Rotation", Datum::DatumTypes::Vector, 1, offsetof(GameObject, Rotation) },
			{ "Scale", Datum::DatumTypes::Vector, 1, offsetof(GameObject, Scale) },
			{ "Children", Datum::DatumTypes::Table, 0, 0 },
			{ "Actions", Datum::DatumTypes::Table, 0, 0 }
		};

	}

	void GameObject::Update(World& world)
	{
		Datum& children = Children();
		for (size_t i = 0; i < children.Size(); ++i)
		{
			Scope& child = children.GetTable(i);
			assert(child.Is(GameObject::TypeIdClass()));
			static_cast<GameObject&>(children.GetTable(i)).Update(world);
		}

		Datum& actions = Actions();
		for (size_t i = 0; i < actions.Size(); ++i)
		{
			Scope& child = actions.GetTable(i);
			assert(child.Is(Action::TypeIdClass()));
			static_cast<Action&>(actions.GetTable(i)).Update(world);
		}

	}

	Datum& GameObject::Children()
	{
		assert(_orderVector[_childrenIndex]->second != nullptr);
		Datum& children = _orderVector[_childrenIndex]->second;
		return children;
	}

	Datum& GameObject::Actions()
	{
		assert(_orderVector[_actionsIndex]->second != nullptr);
		Datum& actions = _orderVector[_actionsIndex]->second;
		return actions;
	}

	GameObject& GameObject::GetChild(size_t index)
	{
		Datum& children = Children();
		if (index >= children.Size())
		{
			throw std::runtime_error("Invalid index out of bounds");
		}
		return static_cast<GameObject&>(children.GetTable(index));
	}

	gsl::owner<Scope*> GameObject::Clone() const
	{
		return  new GameObject(*this);
	}
}