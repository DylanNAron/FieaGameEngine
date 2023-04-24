#include "pch.h"
#include "CppUnitTest.h"
#include "ToStringSpecializations.h"
#include "AttributedFoo.h"
#include "TypeRegistry.h"
#include "RTTI.h"
#include "Factory.h"
#include "GameObject.h"
#include "ActionIncrement.h"
#include "ActionList.h"
#include "ActionListWhile.h"
#include "EventMessageAttributed.h"
#include "ReactionAttributed.h"
#include "ActionEvent.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;


namespace LibraryDesktopTests
{

	TEST_MODULE_INITIALIZE(InitializeModule)
	{

		TypeRegistry* typeRegistry = TypeRegistry::GetInstance();
		typeRegistry->RegisterType(AttributedFoo::TypeIdClass(), AttributedFoo::Signatures());
		typeRegistry->RegisterType(GameObject::TypeIdClass(), GameObject::Signatures());
		typeRegistry->RegisterType(Action::TypeIdClass(), Action::Signatures());
		typeRegistry->RegisterType(ActionIncrement::TypeIdClass(), ActionIncrement::Signatures());
		typeRegistry->RegisterType(ActionList::TypeIdClass(), ActionList::Signatures());
		typeRegistry->RegisterType(ActionListWhile::TypeIdClass(), ActionListWhile::Signatures());
		typeRegistry->RegisterType(EventMessageAttributed::TypeIdClass(), EventMessageAttributed::Signatures());
		typeRegistry->RegisterType(ReactionAttributed::TypeIdClass(), ReactionAttributed::Signatures());
		typeRegistry->RegisterType(ActionEvent::TypeIdClass(), ActionEvent::Signatures());

		Factory<Scope>::Add(std::make_unique<ScopeFactory>());
		Factory<Scope>::Add(std::make_unique<AttributedFooFactory>());
		Factory<Scope>::Add(std::make_unique<GameObjectFactory>());
		Factory<Scope>::Add(std::make_unique<ActionIncrementFactory>());
		Factory<Scope>::Add(std::make_unique<ActionListFactory>());
		Factory<Scope>::Add(std::make_unique<ActionListWhileFactory>());
		Factory<Scope>::Add(std::make_unique<ReactionAttributedFactory>());
		Factory<Scope>::Add(std::make_unique<ActionEventFactory>());
	}

	TEST_MODULE_CLEANUP(CleanUpModule)
	{
		TypeRegistry* typeRegistry = TypeRegistry::GetInstance();
		typeRegistry->DestroyInstance();

		Factory<Scope>::Remove(std::make_unique<ScopeFactory>());
		Factory<Scope>::Remove(std::make_unique<AttributedFooFactory>());
		Factory<Scope>::Remove(std::make_unique<GameObjectFactory>());
		Factory<Scope>::Remove(std::make_unique<ActionIncrementFactory>());
		Factory<Scope>::Remove(std::make_unique<ActionListFactory>());
		Factory<Scope>::Remove(std::make_unique<ActionListWhileFactory>());
		Factory<Scope>::Remove(std::make_unique<ReactionAttributedFactory>());
		Factory<Scope>::Remove(std::make_unique<ActionEventFactory>());

	}

}