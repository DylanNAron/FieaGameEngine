#pragma once
#include "GameClock.h"
#include "GameTime.h"
#include "EventQueue.h"

namespace FieaGameEngine
{
	class GameObject;
	/// <summary>
	/// The root game object that will hold all game objects in the scene and update them. This is the Game World.
	/// </summary>
	class World final
	{
	public:

		World() = default;
		World(GameObject& rootobject);
		~World() = default;

		void Update();

		EventQueue& GetEventQueue();

		const GameTime& GetGameTime() const;

	private:
		GameObject* _rootObject{ nullptr };

		GameClock _gameClock{};
		GameTime _gameTime{};
		EventQueue _eventQueue{};
	};

}