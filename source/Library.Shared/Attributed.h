#pragma once
#include "Scope.h"
#include "TypeRegistry.h"
#include "Signature.h"
#include "Vector.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Abstract base class derived from Scope. Acts as the glue to our scope and datum recursive data structure. This allows us to bind a schema or attributed objects at compile time to mirror the native classes.
	/// </summary>
	class Attributed : public Scope
	{
		RTTI_DECLARATIONS(Attributed, Scope);

	public:
		/// <summary>
		/// Attributed Destructor (defaulted because we utilize scopes destructor)
		/// </summary>
		virtual ~Attributed() = default;

		/// <summary>
		/// Copy Constructor. Utilizes Scopes copy constructor and then repopulates the prescribed attributes with its own.
		/// </summary>
		/// <param name="other">other Attributed class we are copying</param>
		Attributed(const Attributed& other);

		/// <summary>
		/// Copy Assignment Operator. Utilizes Scopes copy assignment operator and then repopulates the prescribed attributes with its own.
		/// </summary>
		/// <param name="other">other Attributed class we are copying</param>
		/// <returns>Reference to Attributed object copy</returns>
		Attributed& operator=(const Attributed& other);

		/// <summary>
		/// Move Constructor. Utilizes Scopes move constructor and then repopulates the prescribed attributes with its own.
		/// </summary>
		/// <param name="rhs">Rvalue Attributed class we are moving</param>
		Attributed(Attributed&& rhs) noexcept;

		/// <summary>
		/// Move Assignment Operator. Utilizes Scopes move assignment and then repopulates the prescribed attributes with its own.
		/// </summary>
		/// <param name="rhs">Rvalue Attributed class we are moving</param>
		/// <returns> Reference to moved attributed object</returns>
		Attributed& operator=(Attributed&& rhs) noexcept;

		/// <summary>
		/// Given a string (which must not be the name of a prescribed attribute), append a Datum to this Scope with the given name, and return a reference to that Datum. Wrapper to scope append but with name check.
		/// </summary>
		/// <param name="attributeName">attribute to append</param>
		/// <returns>Reference to the newly created datum or existing datum</returns>
		virtual Datum& AppendAuxiliaryAttribute(const std::string& attributeName);

		/// <summary>
		/// Given a string, return a bool indicating whether it is the name of an attribute for this object.
		/// </summary>
		/// <param name="attributeName"> string representing name of attribute or the key to find</param>
		/// <returns>Boolean of if is an attribute</returns>
		virtual bool IsAttribute(const std::string& attributeName) const;

		/// <summary>
		/// Given a string, return a bool indicating whether it is the name of a prescribed attribute for this class.
		/// </summary>
		/// <param name="attributeName">string representing name of prescribed attribute or the key to find</param>
		/// <returns>Boolean of if is a prescribed attribute</returns>
		virtual bool IsPrescribedAttribute(const std::string& attributeName) const;

		/// <summary>
		/// Given a string, return a bool indicating whether it is the name of an auxiliary attribute for this object. 
		/// </summary>
		/// <param name="attributeName">string representing name of auxiliary attribute or the key to find</param>
		/// <returns>Boolean of if is an auxiliary attribute</returns>
		virtual bool IsAuxiliaryAttribute(const std::string& attributeName) const;

		/// <summary>
		/// Accessorr for Attributes. Returns a range of [start, end). Inclusive start and exclusive end indexes. 
		/// </summary>
		/// <returns>Pair of Start, and End indexes</returns>
		virtual std::pair<size_t, size_t>  Attributes() const;

		/// <summary>
		/// Accessor for Prescribed Attributes. Returns a range of [start, end). Inclusive start and exclusive end indexes. 
		/// </summary>
		/// <returns>Pair of Start, and End indexes</returns>
		virtual std::pair<size_t, size_t>  PrescribedAttributes() const;

		/// <summary>
		/// Accessor for Auxiliary Attributes. Returns a range of [start, end). Inclusive start and exclusive end indexes. 
		/// </summary>
		/// <returns>Pair of Start, and End indexes</returns>
		virtual std::pair<size_t, size_t>  AuxiliaryAttributesRange() const;

		/// <summary>
		/// Returns a vector only of the auxiliary attributes present (string , datum pairs).
		/// </summary>
		/// <returns>Vector of auxiliary attributes</returns>
		virtual const Vector<std::pair<const std::string, Datum>*> AuxiliaryAttributes() const;

	protected:
		/// <summary>
		/// Attributed Constructor.
		/// </summary>
		/// <param name="typeId">TypeId of the Attributed object. We use this for the TypeRegistry so that we can get the signatures (precribed attributes) of the specific type.</param>
		Attributed(RTTI::IdType typeId);

		/// <summary>
		/// Populate the Attributed object with its specific prescribed attributes, or repopulate. Used for construction, copying, and moving. Prescribed attributes for the specific type of attribute are retrieved from the TypeRegistry.
		/// </summary>
		/// <param name="typeId">TypeId of the Attributed object. We use this for the TypeRegistry so that we can get the signatures (precribed attributes) of the specific type.</param>
		void Populate(RTTI::IdType typeId);

	};

}

