#pragma once
#include "GameObject.h"
namespace FieaGameEngine
{
	class TestGameObject : public GameObject
	{

	public:
		virtual ~TestGameObject() = default;
		virtual void Update(World& time) override 
		{
			GameObject::Update(time);
			++incrementValue;
		};

		size_t incrementValue{ 0 };

	};
}