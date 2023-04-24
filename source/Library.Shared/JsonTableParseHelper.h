#pragma once
#include "IJsonParseHelper.h"
#include "Scope.h"
#include "Datum.h"
#include "Stack.h"
#include <functional>

namespace FieaGameEngine
{

	class JsonTableParseHelper final: public IJsonParseHelper
	{
		RTTI_DECLARATIONS(JsonTableParseHelper, FieaGameEngine::RTTI);
	public:
		class Wrapper : public JsonParseCoordinator::Wrapper
		{
			RTTI_DECLARATIONS(JsonTableParseHelper::Wrapper, FieaGameEngine::RTTI);

		public:
			Wrapper(std::shared_ptr<Scope> scope);

			std::shared_ptr<JsonParseCoordinator::Wrapper> Create() override;

			std::shared_ptr<Scope> root;

		};

		bool StartHandler(JsonParseCoordinator::Wrapper& sharedData, const std::string& jsonKey, const Json::Value& jsonObject, bool isArrayElement) override;

		bool EndHandler(JsonParseCoordinator::Wrapper& sharedData, const std::string& jsonKey) override;

		std::shared_ptr<IJsonParseHelper> Create() override;

	private:
		struct ContextFrame final
		{
			Scope* currentScope{ nullptr };
			Datum* currentDatum{ nullptr };
			std::string tableClass{ "Scope" };
		};
		Stack<ContextFrame> _callStack;
		Stack<Scope*> _scopeStack;
		Datum* _curDatum;
		std::string _tableClass{ "Scope" }; 

		/// <summary>
		/// Helper function for code reuse in checking if we are in array and if we are handling internal or external storage. This is done so that we utilize the correct Datum functions for inserting values depending on the type, and isExternal.
		/// </summary>
		/// <param name="externalFunctor"> Functor used to execute external datum set from string call</param>
		/// <param name="internalFunctor"> Functor used to execute internal datum pushback from string call</param>
		/// <param name="isArrayElement"> isArray bool that we use in the handler</param>
		/// <param name="jsonObject"> jsonObject that we use in the handler</param>
		void DatumInsertionLoopAndCheck(std::function<void(const std::string&, size_t)> externalFunctor, std::function<void(const std::string&)> internalFunctor, bool isArrayElement, const Json::Value& jsonObject);

	};

}

