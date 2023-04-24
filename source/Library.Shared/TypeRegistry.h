#pragma once
#include "Signature.h"
#include "Vector.h"
#include "Hashmap.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Type Registry which will store the Signatures for each Attributed class. This uses the singleton pattern so there is only one instance of type registry we need to call.
	/// </summary>
	class TypeRegistry final
	{
	public:
		/// <summary>
		/// Return the single instance of the type registry
		/// </summary>
		/// <returns>Pointer to TypeRegistry</returns>
		static TypeRegistry* GetInstance();

		/// <summary>
		/// Create a new Instance of Type Registry (There can only be one, this is asserted)
		/// </summary>
		static void CreateInstance();

		/// <summary>
		/// Destroys Instance of TypeRegistry
		/// </summary>
		static void DestroyInstance();

		/// <summary>
		/// Register a new signature of attributed class to the TypeRegistry.
		/// </summary>
		/// <param name="typeID">IDType of Attributed class</param>
		/// <param name="signatures">Signatures from attributed class</param>
		void RegisterType(RTTI::IdType typeID, Vector<Signature> signatures);

		/// <summary>
		/// Gets the Signatures for the the Attributed class based on the given typeId.
		/// </summary>
		/// <param name="typeID">typeId of the Attributed Class</param>
		/// <returns>Vector of signatures (Prescribed Attributes)</returns>
		[[nodiscard]] Vector<Signature>& GetSignaturesForTypeId(RTTI::IdType typeID);

	private:

		inline static TypeRegistry* _instance{ nullptr };
		Hashmap<RTTI::IdType, Vector<Signature>> _signatures;
	};

}