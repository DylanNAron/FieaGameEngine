#pragma once
#include "json/json.h"
#include "RTTI.h"
#include "gsl/gsl"
#include "fstream"
#include "Vector.h"

namespace FieaGameEngine
{
	class IJsonParseHelper;

	/// <summary>
	/// Class to wrap JsonCpp functionality
	/// </summary>
	class JsonParseCoordinator final
	{
	public:
		/// <summary>
		/// Embedded Wrapper class. This class will represent data that all helpers share with each other and with the coordinator. This is a base class.
		/// </summary>
		class Wrapper : public RTTI
		{
			RTTI_DECLARATIONS(JsonParseCoordinator::Wrapper, FieaGameEngine::RTTI);

			friend JsonParseCoordinator;
		public:

			/// <summary>
			/// overridden implementations will create an instance of the shared data. This is a so-called “virtual constructor”.
			/// </summary>
			virtual std::shared_ptr<JsonParseCoordinator::Wrapper> Create() = 0;

			/// <summary>
			/// Default Destructed
			/// </summary>
			virtual ~Wrapper() = default;

			/// <summary>
			/// return the address of the JsonParseCoordinator associated with this object.
			/// </summary>
			/// <returns></returns>
			JsonParseCoordinator* GetJsonParseCoordinator();

			/// <summary>
			/// return the current nesting depth.
			/// </summary>
			/// <returns></returns>
			std::size_t Depth();

		private:
			/// <summary>
			/// increment a “nesting depth” counter. This gets incremented upon the start of each element.
			/// </summary>
			void IncrementDepth();

			/// <summary>
			/// decrement a “nesting depth” counter. This gets decremented upon the end of each element.
			/// </summary>
			void DecrementDepth();

			/// <summary>
			/// Called by the constructor. given the address of an JsonParseCoordinator, assign it to a private member.
			/// </summary>
			/// <param name="AssociatedJsonParseCoordinator">Associated JsonParseCoordinator to set private member</param>
			void SetJsonParseCoordinator(JsonParseCoordinator* AssociatedJsonParseCoordinator);

			std::size_t _depth;
			JsonParseCoordinator* _jsonParseCoordinator;
		};

		/// <summary>
		/// given a reference to a SharedData object, initialize this object.
		/// </summary>
		/// <param name="sharedData">shared pointer to sharedData wrapper (wrapper)</param>
		JsonParseCoordinator(std::shared_ptr<Wrapper> sharedData);

		/// <summary>
		/// Destructor, cleans up all helpers
		/// </summary>
		~JsonParseCoordinator();

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs">rvalue JsonParseCoordinator to move</param>
		/// <returns>Move Constructed JsonParseCoordinator</returns>
		JsonParseCoordinator(JsonParseCoordinator&& rhs) noexcept;

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="rhs">rvalue JsonParseCoordinator to move</param>
		/// <returns>Move Assigned JsonParseCoordinator</returns>
		JsonParseCoordinator& operator=(JsonParseCoordinator&& rhs) noexcept;

		JsonParseCoordinator(JsonParseCoordinator& other) = delete;
		JsonParseCoordinator& operator=(JsonParseCoordinator& other) = delete;

		/// <summary>
		/// duplicate this object and return it as shared pointer. Making sure to "Create" its associated wrappers and helpers.
		/// </summary>
		/// <returns>A clone of this object as shared pointer</returns>
		std::shared_ptr<JsonParseCoordinator> Clone();

		/// <summary>
		/// given a reference to an IJsonParseHelper object, add it to the list.
		/// </summary>
		/// <param name="helper">helper reference to add</param>
		void AddHelper(std::shared_ptr<IJsonParseHelper> helper);

		/// <summary>
		/// given a reference to an IJsonParseHelper object, remove it from the list.
		/// </summary>
		/// <param name="helper">helper reference to remove</param>
		void RemoveHelper(std::shared_ptr<IJsonParseHelper> helper);

		/// <summary>
		/// Return reference to the helper list
		/// </summary>
		/// <returns>Reference to the vector of helper shared pointers</returns>
		const Vector<std::shared_ptr<IJsonParseHelper>>& Helpers();

		/// <summary>
		/// Deserialize Json Object from given string formatted in json
		/// </summary>
		/// <param name="jsonData">String of Json</param>
		void DeserializeObject(std::string& jsonData);

		/// <summary>
		/// Deserialize Json Object as an istream of json
		/// </summary>
		/// <param name="jsonData">Istream of Json</param>
		void DeserializeObject(std::istream& jsonData);

		/// <summary>
		/// Deserialize Json Object from file. Given fileName, will open and deserialize.
		/// </summary>
		/// <param name="fileName">String name of file</param>
		void DeserializeObjectFromFile(std::string& fileName);

		/// <summary>
		/// return the address of the Wrapper associated with this object.
		/// </summary>
		/// <returns>Address of wrapper associated with this Coordinator</returns>
		std::shared_ptr<Wrapper> GetWrapper();

		/// <summary>
		/// given the address of a Wrapper object, associate it with this object.
		/// </summary>
		/// <param name="wrapper">wrapper to associate with this Coordinator</param>
		void SetWrapper(std::shared_ptr<Wrapper> wrapper);

	private:

		/// <summary>
		/// Retrieves the members from a Json::Value object and Parse's each of them.
		/// </summary>
		/// <param name="jsonObject">JsonValue object to parse</param>
		void ParseMembers(Json::Value& jsonObject);

		/// <summary>
		/// Given a key/value pair (string/Json::Value) and a bool indicating if the value is an element of an array, trigger the chain of responsibility. In other words, walk through the list of helpers and invoke the StartHander methods until one responds that it has handled the pair. 
		/// </summary>
		/// <param name="key">Json Key (as string)</param>
		/// <param name="value">Json Value</param>
		/// <param name="isArrayElement">Boolean is array</param>
		void Parse(std::string& key, Json::Value& value, bool isArrayElement);

		/// <summary>
		/// Helper function to initialize all the helpers, called before a file is parsed.
		/// </summary>
		void InitializeHelpers();

		Vector<std::shared_ptr<IJsonParseHelper>> _helperList;
		std::shared_ptr<Wrapper> _wrapper;

	};



}