#pragma once
#include "EventSubscriber.h"
#include <cstdint>


namespace UnitTests
{
	class FooSubscriber final : public FieaGameEngine::EventSubscriber
	{
	public:
		FooSubscriber() = default;
		~FooSubscriber() = default;

		void Notify(const FieaGameEngine::EventPublisher& eventPublisher) override;


		bool isNotified{ false };
		std::int32_t _data{ 0 };
	};
}