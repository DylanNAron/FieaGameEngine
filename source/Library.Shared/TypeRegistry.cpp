#include "pch.h"
#include "TypeRegistry.h"

namespace FieaGameEngine
{
    TypeRegistry* TypeRegistry::GetInstance()
    {
        if (_instance == nullptr)
        {
            CreateInstance();
        }
        return _instance;
    }
    inline void TypeRegistry::CreateInstance()
    {
        assert(_instance == nullptr);
        _instance = new TypeRegistry;
    }

    void TypeRegistry::DestroyInstance()
    {
        delete _instance;
    }

    void TypeRegistry::RegisterType(RTTI::IdType typeID, Vector<Signature> signatures)
    {
        _signatures.Insert(std::make_pair(typeID, signatures));
    }

    Vector<Signature>& FieaGameEngine::TypeRegistry::GetSignaturesForTypeId(RTTI::IdType typeID)
    {
        return _signatures.At(typeID);
    }

}
