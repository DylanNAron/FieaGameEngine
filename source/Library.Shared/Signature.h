#pragma once
#include "Datum.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Signature for a single prescribed attribute. A vector of signatures will be needed from each Attributed class to describe its prescribed attributes and be added to the type registry. Stores Name, Type, Size, & Offset.
	/// </summary>
	struct Signature final
	{
		std::string Name;
		Datum::DatumTypes Type;
		std::size_t Size;
		std::size_t Offset;
	};
}