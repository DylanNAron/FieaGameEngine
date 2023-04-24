#pragma once
#include "Datum.h"
#include "Vector.h"
#include "Hashmap.h"
#include "gsl/gsl"
#include "Factory.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Tables of string , Datum entries. This provides a dynamic hierarchical database. All nested scopes are heap allocated, while root scopes may be stack allocated.
	/// </summary>
	class Scope : public RTTI
	{
		friend class JsonTableParseHelper;

		RTTI_DECLARATIONS(Scope, FieaGameEngine::RTTI);

	public:

		/// <summary>
		/// Scope Constructor, with capacity parameter defaulted to 5. This capacity is used to set the size of our scope unordered map. scope vector will default to empty and grow as needed.
		/// </summary>
		/// <param name="capacity">capacity to set for scopeMap</param>
		explicit Scope(size_t capacity = 5);

		/// <summary>
		/// Scope Copy Constructor : Loop through scope copy every datum, if datum is of type table clone all the nested scopes
		/// </summary>
		/// <param name="other">other scope that we are copying from</param>
		Scope(const Scope& other);
		
		/// <summary>
		/// Copy assignment operator : Clone all contained scopes for copy.
		/// </summary>
		/// <param name="other">other scope that we are copying from</param>
		/// <returns>Reference to copied scope</returns>
		Scope& operator=(const Scope& other);

		/// <summary>
		/// Move Constructor. Parents are not preserved in move construction, and moved scope will be deleted from the heap.
		/// </summary>
		/// <param name="rhs">right hand scope that we are moving</param>
		Scope(Scope&& rhs) noexcept;

		/// <summary>
		/// Move assignment operator. Parents are not preserved in move assignment.
		/// </summary>
		/// <param name="rhs">right hand scope that we are moving</param>
		/// <returns>Reference to moved scope</returns>
		Scope& operator=(Scope&& rhs) noexcept;

		/// <summary>
		///  takes a constant string and which wraps Append, for syntactic convenience.
		/// </summary>
		/// <param name="key">Key for datum</param>
		/// <returns>Reference to Datum (existing or newly created)</returns>
		Datum& operator[](const std::string& key);

		/// <summary>
		///  takes an unsigned integer and which returns a reference to a Datum at the given index. The index values correspond to the order in which items were appended.
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		Datum& operator[](size_t index);

		/// <summary>
		/// Destructor. Marked virtual as scope can be derived from.
		/// </summary>
		virtual ~Scope() override;

		/// <summary>
		/// Equals virtual function overrided from RTTI base class. This calls our == operator.
		/// </summary>
		/// <param name="rhs">right hand RTTI that we are comparing to</param>
		/// <returns>Boolean for equality</returns>
		virtual bool Equals(const RTTI* rhs) const override;

		/// <summary>
		/// Order Dependent comparison of scopes, parents are not factored in comparison.
		/// </summary>
		/// <param name="other">other scope we are comparing to</param>
		/// <returns>boolean for equality</returns>
		bool operator==(const Scope& other) const;

		/// <summary>
		/// Order Dependent comparison of scopes, parents are not factored in comparison.
		/// </summary>
		/// <param name="other">other scope we are comparing to</param>
		/// <returns>boolean for inequality</returns>
		bool operator!=(const Scope& other) const;

		/// <summary>
		/// takes a constant string and returns the address of a Datum. This should return the address of the Datum associated with the given name in this Scope, if it exists, and nullptr otherwise.
		/// </summary>
		/// <param name="key">Key to find</param>
		/// <returns>Datum pointer found from key, null if not found</returns>
		[[nodiscard]] Datum* Find(const std::string& key);


		/// <summary>
		/// takes the constant address of a Scope and returns the Datum pointer and index at which the Scope was found. Scope must be present and we assert not find nullptr.
		/// </summary>
		/// <param name="scopeToFind">pointer to the scope we are searching for</param>
		/// <returns>Pair of datum pointer and index at which datum is found.</returns>
		[[nodiscard]] std::pair<Datum*, size_t> FindContainedScope(const Scope* scopeToFind);

		/// <summary>
		/// which takes a constant string and the address of a Scope double pointer variable (whose default value could be nullptr), and which returns the address of a Datum. This should return the address of the most-closely nested Datum associated with the given name in this Scope or its ancestors, if it exists, and nullptr otherwise. You could implement this as a recursive algorithm. The Scope pointer variable, if provided, shall contain the address of the Scope object which contains the match.
		/// </summary>
		/// <param name="key">key to search for</param>
		/// <param name="foundscope">output parameter of the found scope</param>
		/// <returns></returns>
		Datum* Search(const std::string& key, Scope*& foundscope);

		/// <summary>
		///  takes a constant string and returns a reference to a Datum. This should return a reference to a Datum with the associated name. If it already exists, return that one, otherwise create one. Does not allow empty keys.
		/// </summary>
		/// <param name="key">Key to find or insert new datum at.</param>
		/// <returns>Returns a Datum reference that is newly created or already present</returns>
		Datum& Append(const std::string& key);

		/// <summary>
		/// akes a constant string and returns a reference to Scope. This should return a reference to a Scope with the associated name.  If a Datum already exists at that key reuse it (and append to it a new Scope), otherwise create a new Datum.
		/// </summary>
		/// <param name="key">Key to find or insert a new datum of type table</param>
		/// <returns>A reference to the newly appended scope</returns>
		Scope& AppendScope(const std::string& key);

		/// <summary>
		/// Cloning (virtual constructor) used for copying
		/// </summary>
		/// <returns>A scope Pointer to new clone</returns>
		[[nodiscard]] virtual gsl::owner<Scope*> Clone() const;

		/// <summary>
		/// Makes the parent of the given scope null and deletes the reference of this scope from the parent
		/// </summary>
		/// <returns>A pointer to the orphaned child</returns>
		gsl::owner<Scope*> Orphan();

		/// <summary>
		/// takes a reference to a Scope (the child to adopt), a string (the name of key for the Datum to use for storing the child).
		/// </summary>
		/// <param name="child">child scope to adopt</param>
		/// <param name="key">key for the datum to store child</param>
		/// <exception cref="Key empty">throw exception if key is empty</exception>
		/// <exception cref="Self Assign">throw exception if attempting self assignment</exception>
		/// <exception cref="Ancestor Adopt">throw exception if attempting ancestor adoption</exception>
		void Adopt(Scope& child, const std::string& key);

		/// <summary>
		/// Clear all memory of heap allocated scopes, used by destuctor and for copy semantics
		/// </summary>
		void Clear();
		
		/// <summary>
		/// Retrieves the parent scope
		/// </summary>
		/// <returns>Scope pointer to parent</returns>
		[[nodiscard]] Scope* GetParent() const;

		/// <summary>
		/// Returns the size of the scope.
		/// </summary>
		/// <returns>unsigned integer of the size of the scope</returns>
		[[nodiscard]] size_t Size() const;

		/// <summary>
		/// Check if a scope is an ancestor by searching up its parents
		/// </summary>
		/// <param name="scopeToCheck">Scope that we are checking to see if it is an ancestor of this scope</param>
		/// <returns></returns>
		[[nodiscard]] bool IsAncestor(const Scope& scopeToCheck) const;

	protected:

		Scope* _parent{ nullptr };
		Hashmap<std::string, Datum> _tableMap;
		Vector<std::pair<const std::string, Datum>*> _orderVector{};

	};

	ConcreteFactory(Scope, Scope);

}


