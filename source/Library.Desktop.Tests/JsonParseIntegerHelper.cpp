#include "pch.h"
#include "JsonParseIntegerHelper.h"

namespace FieaGameEngine
{
    RTTI_DEFINITIONS(JsonParseIntegerHelper::Wrapper);
    RTTI_DEFINITIONS(JsonParseIntegerHelper);

    std::shared_ptr<JsonParseCoordinator::Wrapper> JsonParseIntegerHelper::Wrapper::Create()
    {
        return std::shared_ptr<JsonParseCoordinator::Wrapper>(new JsonParseIntegerHelper::Wrapper);
    }

    bool JsonParseIntegerHelper::StartHandler(JsonParseCoordinator::Wrapper& sharedData, const std::string& jsonKey, const Json::Value& jsonObject, bool isArrayElement)
    {
        if (!sharedData.Is(JsonParseIntegerHelper::Wrapper().TypeIdClass()))
        {
            return false;
        }

        if (jsonKey != "integer")
        {
            return false;
        }

        JsonParseIntegerHelper::Wrapper* rawWrapper = sharedData.As<JsonParseIntegerHelper::Wrapper>();
        isArrayElement;
        if (isArrayElement)
        {
            for (auto& element : jsonObject)
            {
                rawWrapper->integerData.PushBack(element.asInt());
            }
        }
        else
        {
            rawWrapper->integerData.PushBack(jsonObject.asInt());
        }

        return true;
    }

    bool JsonParseIntegerHelper::EndHandler(JsonParseCoordinator::Wrapper& sharedData, const std::string& jsonKey)
    {
        sharedData;
        jsonKey;
        return true;
    }

    std::shared_ptr<IJsonParseHelper> JsonParseIntegerHelper::Create()
    {
        return std::shared_ptr<IJsonParseHelper>();
    }


}
