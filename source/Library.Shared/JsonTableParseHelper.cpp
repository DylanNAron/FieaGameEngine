#include "pch.h"
#include "JsonTableParseHelper.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(JsonTableParseHelper::Wrapper);
	RTTI_DEFINITIONS(JsonTableParseHelper);

	std::shared_ptr<JsonParseCoordinator::Wrapper> JsonTableParseHelper::Wrapper::Create()
	{
		return std::shared_ptr<JsonParseCoordinator::Wrapper>(new JsonTableParseHelper::Wrapper(root));
	}

	JsonTableParseHelper::Wrapper::Wrapper(std::shared_ptr<Scope> scope) :
		root(scope)
	{
	}

	bool JsonTableParseHelper::StartHandler(JsonParseCoordinator::Wrapper& sharedData, const std::string& jsonKey, const Json::Value& jsonObject, bool isArrayElement)
	{
		if (!sharedData.Is(JsonTableParseHelper::Wrapper::TypeIdClass()))
		{
			return false;
		}
		JsonTableParseHelper::Wrapper* rawWrapper = sharedData.As<JsonTableParseHelper::Wrapper>();
		if (_scopeStack.IsEmpty())
		{
			_scopeStack.Push(rawWrapper->root.get()); //root of the contextFrame
			_callStack.Push(ContextFrame{ rawWrapper->root.get() }); //root of the contextFrame
		}

				
		_callStack.Push(ContextFrame{ _callStack.Top().currentScope,  _callStack.Top().currentDatum });
		_curDatum = _callStack.Top().currentDatum;


		if (jsonKey == "type")
		{
			Datum::DatumTypes type = Datum::DatumTypeStringMap.At(jsonObject.asString());
			_curDatum->SetType(type);

			if (type == Datum::DatumTypes::Table) //if type is table do "append scope" then push to top of context frame : Not always scope, class grammar can denote what we append (derived from scope)
			{
				Scope* table = Factory<Scope>::Create(_tableClass);
				assert(table != nullptr); //if a jsonfile parsed a class that was not present in the factories
				_curDatum->PushBack(table);
				table->_parent = _scopeStack.Top();
				_scopeStack.Push(table);
				_tableClass = std::string("Scope");

			}
		}
		else if (jsonKey == "value")
		{
			if (_curDatum->Type() == Datum::DatumTypes::Integer)
			{
				std::function<void(const std::string&, size_t index)> externalIntegerSet([this](const std::string& str, size_t index) { _curDatum->SetFromStringInteger(str, index); });
				std::function<void(const std::string&)> internalIntegerSet([this](const std::string& str) { _curDatum->PushBackFromStringInteger(str); });
				DatumInsertionLoopAndCheck(externalIntegerSet, internalIntegerSet, isArrayElement, jsonObject);
			}
			else if (_curDatum->Type() == Datum::DatumTypes::Float)
			{
				std::function<void(const std::string&, size_t index)> externalFloatSet([this](const std::string& str, size_t index) { _curDatum->SetFromStringFloat(str, index); });
				std::function<void(const std::string&)> internalFloatSet([this](const std::string& str) { _curDatum->PushBackFromStringFloat(str); });
				DatumInsertionLoopAndCheck(externalFloatSet, internalFloatSet, isArrayElement, jsonObject);
			}
			else if (_curDatum->Type() == Datum::DatumTypes::Vector)
			{
				std::function<void(const std::string&, size_t index)> externalVectorSet([this](const std::string& str, size_t index) { _curDatum->SetFromStringVector(str, index); });
				std::function<void(const std::string&)> internalVectorSet([this](const std::string& str) { _curDatum->PushBackFromStringVector(str); });
				DatumInsertionLoopAndCheck(externalVectorSet, internalVectorSet, isArrayElement, jsonObject);
			}
			else if (_curDatum->Type() == Datum::DatumTypes::Matrix)
			{
				std::function<void(const std::string&, size_t index)> externalMatrixSet([this](const std::string& str, size_t index) { _curDatum->SetFromStringMatrix(str, index); });
				std::function<void(const std::string&)> internalMatrixSet([this](const std::string& str) { _curDatum->PushBackFromStringMatrix(str); });
				DatumInsertionLoopAndCheck(externalMatrixSet, internalMatrixSet, isArrayElement, jsonObject);
			}
			else if (_curDatum->Type() == Datum::DatumTypes::String)
			{
				std::function<void(const std::string&, size_t index)> externalStringSet([this](const std::string& str, size_t index) { _curDatum->SetString(str, index); });
				std::function<void(const std::string&)> internalStringSet([this](const std::string& str) { _curDatum->PushBack(str); });
				DatumInsertionLoopAndCheck(externalStringSet, internalStringSet, isArrayElement, jsonObject);
			}
		}
		else if (jsonKey == "class")
		{
			_tableClass = jsonObject.asString();
		}
		else //it is an attribute name
		{
			_curDatum = &_scopeStack.Top()->Append(jsonKey);
			_callStack.Top().currentDatum = _curDatum;
		}
		return true;
	}

	bool JsonTableParseHelper::EndHandler(JsonParseCoordinator::Wrapper& sharedData, const std::string& jsonKey)
	{
		JsonTableParseHelper::Wrapper* rawWrapper = sharedData.As<JsonTableParseHelper::Wrapper>();
		rawWrapper;

		//If we are ending a table, pop the table from the stack and set our currentDatum to the found one.
		Scope* foundScope{ nullptr };
		Datum* foundDatum = _scopeStack.Top()->Search(jsonKey, foundScope); 
		if (foundScope != nullptr)
		{
			if (foundDatum->Type() == Datum::DatumTypes::Table)
			{
				_scopeStack.Pop();
				_curDatum = foundDatum;
			}
		}
		_callStack.Pop();

		return true;
	}


	std::shared_ptr<IJsonParseHelper> JsonTableParseHelper::Create()
	{
		return std::shared_ptr<IJsonParseHelper>(new JsonTableParseHelper());
	}

	void JsonTableParseHelper::DatumInsertionLoopAndCheck(std::function<void(const std::string&, size_t)> externalFunctor, std::function<void(const std::string&)> internalFunctor, bool isArrayElement, const Json::Value& jsonObject)
	{
		if (_curDatum->IsExternal())
		{
			if (isArrayElement)
			{
				size_t index = 0;
				for (auto& element : jsonObject)
				{
					externalFunctor(element.asString(), index);
					++index;
				}
			}
			else
			{
				externalFunctor(jsonObject.asString(), 0);
			}
		}
		else
		{
			if (isArrayElement)
			{
				for (auto& element : jsonObject)
				{
					internalFunctor(element.asString());
				}
			}
			else
			{
				internalFunctor(jsonObject.asString());
			}
		}

	}


}