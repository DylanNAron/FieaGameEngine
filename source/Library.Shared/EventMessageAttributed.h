#pragma once
#include "Attributed.h"
#include "World.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Generic Event message attributed class to be used for sending a payload in our reactions system.
	/// </summary>
	class EventMessageAttributed final : public Attributed
	{
		RTTI_DECLARATIONS(EventMessageAttributed, Attributed);

	public:

		/// <summary>
		/// Default Constructor, calls the attributed constructor with type id.
		/// </summary>
		EventMessageAttributed();

		/// <summary>
		/// Constructor, that initializes the subtype and world
		/// </summary>
		/// <param name="subtype">subtype</param>
		/// <param name="world">game world</param>
		EventMessageAttributed(const std::string& subtype, World* world);

		/// <summary>
		/// Signature for EventMessageAttributed, used to register the EventMessageAttributed type for instantiation.
		/// </summary>
		/// <returns></returns>
		static const Vector<Signature> Signatures();

		/// <summary>
		/// Getter for the subtype for this event message.
		/// </summary>
		/// <returns>const string reference that represents the subtype</returns>
		[[nodiscard]] const std::string& GetSubtype() const;

		/// <summary>
		/// Set the subtype of this eventmessage.
		/// </summary>
		/// <param name="subtype">const string ref to subtype to set to</param>
		void SetSubtype(const std::string& subtype);

		/// <summary>
		/// Getter for the World for this event message.
		/// </summary>
		/// <returns>World reference</returns>
		[[nodiscard]] World & GetWorld() const;

		/// <summary>
		/// Set the World of this eventmessage.
		/// </summary>
		/// <param name="World">World refernece to set our world to</param>
		void SetWorld(World& world);


	private:

		std::string _subtype;
		World* _world{ nullptr };
	};

}