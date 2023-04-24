#pragma once
#include "json/json.h"
#include "JsonParseCoordinator.h"
#include "RTTI.h"

namespace FieaGameEngine
{

	/// <summary>
	/// Interface for Json Parsing.
	/// </summary>
	class IJsonParseHelper : public RTTI
	{
		RTTI_DECLARATIONS(IJsonParseHelper, FieaGameEngine::RTTI);

	public:
		/// <summary>
		/// Initialize this helper. This will get called just before each file is parsed.
		/// </summary>
		virtual void Initialize() {};

		/// <summary>
		/// Cleanup this helper. This will get called after parsing.
		/// </summary>
		virtual void Cleanup() {};

		/// <summary>
		/// Given a shared data reference, a string for the Json key, a reference to the Json::Value object, and a bool indicating if the value is an array element, attempt to handle the key/value pair. If this routine does indeed handle the pair, return true, otherwise return false.
		/// </summary>
		/// <param name="sharedData"> Reference to Data Wrapper found in JsonParseCoordinator </param>
		/// <param name="jsonKey"> Json Key</param>
		/// <param name="jsonObject"> Json Object</param>
		/// <param name="isArrayElement"> boolean whether is array or not</param>
		/// <returns> Boolean on if routine handles the pair or not</returns>
		virtual bool StartHandler(JsonParseCoordinator::Wrapper& sharedData, const std::string& jsonKey, const Json::Value& jsonObject, bool isArrayElement) = 0;

		/// <summary>
		///  Given a shared data reference, a string for the Json key, attempt to complete the handling of the element pair. If this routine does indeed handle the pair, return true, otherwise return false. 
		/// </summary>
		/// <param name="sharedData">Reference to Data Wrapper found in JsonParseCoordinator</param>
		/// <param name="jsonKey">Json Key</param>
		/// <returns>Boolean on if routine handles the pair or not</returns>
		virtual bool EndHandler(JsonParseCoordinator::Wrapper& sharedData, const std::string& jsonKey) = 0;

		/// <summary>
		/// overridden implementations will create an instance of the helper. This is a so-called “virtual constructor”.
		/// </summary>
		virtual std::shared_ptr<IJsonParseHelper> Create() = 0;

		virtual ~IJsonParseHelper() = default;
		
	};



}


