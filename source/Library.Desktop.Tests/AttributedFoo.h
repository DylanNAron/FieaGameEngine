#pragma once
#include "Attributed.h"
#include "RTTI.h"
#include "Vector.h"
#include "Signature.h"


namespace UnitTests
{

	class AttributedFoo final : public FieaGameEngine::Attributed
	{
		RTTI_DECLARATIONS(AttributedFoo, Attributed);

	public:
		AttributedFoo();
		
		AttributedFoo(const AttributedFoo& other) = default;
		AttributedFoo(AttributedFoo&& other) noexcept = default;
		AttributedFoo& operator=(const AttributedFoo& other) = default;
		AttributedFoo& operator=(AttributedFoo&& other) noexcept = default;

		static const FieaGameEngine::Vector<FieaGameEngine::Signature> Signatures();

		std::string ToString() const override;

		int32_t ExternalInteger;
		float ExternalFloat;
		std::string ExternalString;
		glm::vec4 ExternalVector;
		glm::mat4 ExternalMatrix;

		static const size_t ArraySize{ 7 };

		int32_t* ExternalIntegerArray;
		float* ExternalFloatArray;
		std::string* ExternalStringArray;
		glm::vec4* ExternalVectorArray;
		glm::mat4* ExternalMatrixArray;


	};


}

using namespace UnitTests;
namespace FieaGameEngine
{
	ConcreteFactory(AttributedFoo, Scope);
}

