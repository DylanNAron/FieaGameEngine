#include "pch.h"
#include "AttributedFoo.h"
using namespace FieaGameEngine;

namespace UnitTests
{

	RTTI_DEFINITIONS(AttributedFoo);

	AttributedFoo::AttributedFoo() :
		Attributed(TypeIdClass())
	{
	}

	const Vector<Signature> AttributedFoo::Signatures()
	{

		return Vector<Signature>
		{
			{"ExternalInteger", Datum::DatumTypes::Integer, 1, offsetof(AttributedFoo, ExternalInteger)},
			{"ExternalFloat", Datum::DatumTypes::Float, 1, offsetof(AttributedFoo, ExternalFloat)},
			{"ExternalString", Datum::DatumTypes::String, 1, offsetof(AttributedFoo, ExternalString)},
			{"ExternalVector", Datum::DatumTypes::Vector, 1, offsetof(AttributedFoo, ExternalVector)},
			{"ExternalMatrix", Datum::DatumTypes::Matrix, 1, offsetof(AttributedFoo, ExternalMatrix)},

			{ "ExternalIntegerArray", Datum::DatumTypes::Integer, ArraySize, offsetof(AttributedFoo, ExternalIntegerArray) },
			{ "ExternalFloatArray", Datum::DatumTypes::Float, ArraySize, offsetof(AttributedFoo, ExternalFloatArray) },
			{ "ExternalStringArray", Datum::DatumTypes::String, ArraySize, offsetof(AttributedFoo, ExternalStringArray) },
			{ "ExternalVectorArray", Datum::DatumTypes::Vector, ArraySize, offsetof(AttributedFoo, ExternalVectorArray) },
			{ "ExternalMatrixArray", Datum::DatumTypes::Matrix, ArraySize, offsetof(AttributedFoo, ExternalMatrixArray) },

			{ "NestedScope", Datum::DatumTypes::Table, 0, 0 },
			{ "NestedScopeArray", Datum::DatumTypes::Table, ArraySize, 0 },
		};
	
	}

	std::string AttributedFoo::ToString() const
	{
		return "AttributedFoo";
	}

}