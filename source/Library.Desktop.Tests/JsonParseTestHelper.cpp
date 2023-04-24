#include "pch.h"
#include "JsonParseTestHelper.h"

namespace FieaGameEngine
{

	RTTI_DEFINITIONS(JsonParseTestHelper::Wrapper);
	RTTI_DEFINITIONS(JsonParseTestHelper);

	bool JsonParseTestHelper::StartHandler(JsonParseCoordinator::Wrapper& sharedData, const std::string& jsonKey, const Json::Value& jsonObject, bool isArrayElement)
	{
		jsonKey;
		jsonObject;
		isArrayElement;
		JsonParseTestHelper::Wrapper* dataWrapper = sharedData.As<JsonParseTestHelper::Wrapper>();
		
		if (dataWrapper->Depth() > MaxDepth)
		{
			MaxDepth = dataWrapper->Depth();
		}

		++StartsCalled;

		return true;
	}

	bool JsonParseTestHelper::EndHandler(JsonParseCoordinator::Wrapper& sharedData, const std::string& jsonKey)
	{
		sharedData;
		jsonKey;

		++EndsCalled;

		return true;
	}

	std::shared_ptr<IJsonParseHelper> JsonParseTestHelper::Create()
	{
		return std::shared_ptr<IJsonParseHelper>(new JsonParseTestHelper);

	}

	std::shared_ptr<JsonParseCoordinator::Wrapper> JsonParseTestHelper::Wrapper::Create()
	{
		return std::shared_ptr<JsonParseCoordinator::Wrapper>(new JsonParseTestHelper::Wrapper);
	}

}
