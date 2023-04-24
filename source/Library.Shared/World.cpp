#include "pch.h"
#include "World.h"
#include "GameObject.h"

namespace FieaGameEngine
{
	EventQueue& World::GetEventQueue()
	{
		return _eventQueue;
	}

	const GameTime& World::GetGameTime() const
	{
		return _gameTime;
	}

	void World::Update()
	{
		_gameClock.UpdateGameTime(_gameTime);
		assert(_rootObject != nullptr);
		_rootObject->Update(*this);
		_eventQueue.Update(_gameTime);
	}

	World::World(GameObject& rootobject) :
		_rootObject(&rootobject)
	{
	}

}