#pragma once
#include "EventSubscriber.h"
#include <cstdint>


namespace UnitTests
{
	class TestSubscriber final : public FieaGameEngine::EventSubscriber
	{
	public:
		TestSubscriber() = default;
		~TestSubscriber() = default;

		void Notify(const FieaGameEngine::EventPublisher& eventPublisher) override;

		std::int32_t _data{ 0 };
	};
}