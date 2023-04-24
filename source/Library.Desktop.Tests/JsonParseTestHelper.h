#pragma once
#include "pch.h"
#include "IJsonParseHelper.h"

namespace FieaGameEngine
{
	class JsonParseTestHelper final : public IJsonParseHelper
	{
		RTTI_DECLARATIONS(JsonParseTestHelper, FieaGameEngine::RTTI);
	public:
		class Wrapper : public JsonParseCoordinator::Wrapper
		{
			RTTI_DECLARATIONS(JsonParseTestHelper::Wrapper, FieaGameEngine::RTTI);

		public:
			std::shared_ptr<JsonParseCoordinator::Wrapper> Create() override;

			int32_t _data;
		};

		bool StartHandler(JsonParseCoordinator::Wrapper& sharedData, const std::string& jsonKey, const Json::Value& jsonObject, bool isArrayElement) override;

		bool EndHandler(JsonParseCoordinator::Wrapper& sharedData, const std::string& jsonKey) override;

		std::shared_ptr<IJsonParseHelper> Create() override;


		size_t MaxDepth{ 0 };
		size_t StartsCalled{ 0 };
		size_t EndsCalled{ 0 };
	};

}

