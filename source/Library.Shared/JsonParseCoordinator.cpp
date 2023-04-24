#include "pch.h"
#include "JsonParseCoordinator.h"
#include "IJsonParseHelper.h"

namespace FieaGameEngine
{

	RTTI_DEFINITIONS(JsonParseCoordinator::Wrapper);

	void JsonParseCoordinator::Wrapper::IncrementDepth()
	{
		++_depth;
	}

	void JsonParseCoordinator::Wrapper::DecrementDepth()
	{
		--_depth;
	}

	std::size_t JsonParseCoordinator::Wrapper::Depth()
	{
		return _depth;
	}

	void JsonParseCoordinator::Wrapper::SetJsonParseCoordinator(JsonParseCoordinator* AssociatedJsonParseCoordinator)
	{
		_jsonParseCoordinator = AssociatedJsonParseCoordinator;
	}

	JsonParseCoordinator::~JsonParseCoordinator()
	{
		for (auto& helper : _helperList)
		{
			helper->Cleanup();
		}
	}

	JsonParseCoordinator* JsonParseCoordinator::Wrapper::GetJsonParseCoordinator()
	{
		return _jsonParseCoordinator;
	}

	JsonParseCoordinator::JsonParseCoordinator(std::shared_ptr<Wrapper> sharedData)
	{
		SetWrapper(sharedData);
		_wrapper->SetJsonParseCoordinator(this);
	}

	JsonParseCoordinator::JsonParseCoordinator(JsonParseCoordinator&& rhs) noexcept :
		_helperList(rhs._helperList)
	{
		_wrapper.swap(rhs._wrapper);
		_wrapper->SetJsonParseCoordinator(this);

		rhs._helperList.Clear();
	}

	JsonParseCoordinator& JsonParseCoordinator::operator=(JsonParseCoordinator&& rhs) noexcept
	{
		_helperList = std::move(rhs._helperList);
		_wrapper.swap(rhs._wrapper);
		rhs._wrapper = nullptr;
		_wrapper->SetJsonParseCoordinator(this);
		rhs._helperList.Clear();

		return *this;
	}

	std::shared_ptr<JsonParseCoordinator> JsonParseCoordinator::Clone()
	{
		std::shared_ptr<JsonParseCoordinator> clone(new JsonParseCoordinator(_wrapper->Create()));
		for (auto& helper : _helperList)
		{
			clone->AddHelper(helper->Create());
		}
		return clone;
	}

	const Vector<std::shared_ptr<IJsonParseHelper>>& JsonParseCoordinator::Helpers()
	{
		return _helperList;
	}

	void JsonParseCoordinator::DeserializeObject(std::string& jsonData)
	{
		Json::Value root;
		std::istringstream{jsonData} >> root;
		InitializeHelpers();
		ParseMembers(root);
	}

	void JsonParseCoordinator::DeserializeObject(std::istream& jsonData)
	{
		Json::Value root;
		jsonData >> root;
		InitializeHelpers();
		ParseMembers(root);
	}

	void JsonParseCoordinator::DeserializeObjectFromFile(std::string& fileName)
	{
		std::ifstream file{ fileName };
		DeserializeObject(file);
	}

	void JsonParseCoordinator::AddHelper(std::shared_ptr<IJsonParseHelper> helper)
	{
		for (auto& helperIt : _helperList)
		{
			if (helperIt->Is(helper->TypeIdInstance()))
			{
				throw std::runtime_error("Attempting to add duplicate helper");
			}
		}
		_helperList.PushBack(helper);
	}

	void JsonParseCoordinator::RemoveHelper(std::shared_ptr<IJsonParseHelper> helper)
	{
		_helperList.Remove(helper);
	}

	std::shared_ptr<JsonParseCoordinator::Wrapper> JsonParseCoordinator::GetWrapper()
	{
		return _wrapper;
	}
	
	void JsonParseCoordinator::SetWrapper(std::shared_ptr<Wrapper> wrapper)
	{
		_wrapper = wrapper;
	}

	void JsonParseCoordinator::ParseMembers(Json::Value& jsonObject)
	{
		_wrapper->IncrementDepth();
		for (auto& key : jsonObject.getMemberNames())
		{
			Parse(key, jsonObject[key], jsonObject[key].isArray());
			
		}
		_wrapper->DecrementDepth();

	}

	void JsonParseCoordinator::Parse(std::string& key, Json::Value& value, bool isArrayElement)
	{
		for (auto& helper : _helperList)
		{
			if (helper->StartHandler(*_wrapper, key, value, isArrayElement))
			{

				if (value.isObject())
				{
					ParseMembers(value);

				}
				else if (isArrayElement)
				{
					for (auto& element : value)
					{
						if (element.isObject())
						{
							ParseMembers(element);
						}
					}
				}
				//else its a primitive or we are exiting the callstack and ending an objects start call
				helper->EndHandler(*_wrapper, key);
			}
		}
	}


	void JsonParseCoordinator::InitializeHelpers()
	{
		for (auto& helper : _helperList)
		{
			helper->Initialize();
		}
	}


}

