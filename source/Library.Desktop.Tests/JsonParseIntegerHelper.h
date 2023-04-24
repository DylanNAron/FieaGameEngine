#pragma once
#include "pch.h"
#include "IJsonParseHelper.h"
#include "Vector.h"

namespace FieaGameEngine
{
	class JsonParseIntegerHelper final : public IJsonParseHelper
	{
		RTTI_DECLARATIONS(JsonParseTestHelper, FieaGameEngine::RTTI);
	public:
		class Wrapper : public JsonParseCoordinator::Wrapper
		{
			RTTI_DECLARATIONS(JsonParseIntegerHelper::Wrapper, FieaGameEngine::RTTI);

		public:
			std::shared_ptr<JsonParseCoordinator::Wrapper> Create() override;

			Vector<size_t> integerData{};
		};

		bool StartHandler(JsonParseCoordinator::Wrapper& sharedData, const std::string& jsonKey, const Json::Value& jsonObject, bool isArrayElement) override;

		bool EndHandler(JsonParseCoordinator::Wrapper& sharedData, const std::string& jsonKey) override;

		std::shared_ptr<IJsonParseHelper> Create() override;

	};

}
