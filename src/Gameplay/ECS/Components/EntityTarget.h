#pragma once
#include <entt.hpp>
#include "NetworkComponent.h"


struct EntityTarget : NetworkComponent
{
    EntityTarget() { }

    entt::entity target = entt::null;

    // Network Helpers
    bool Serialize(Bytebuffer* buffer) const
    {
        bool didFail = false;

        didFail |= !buffer->PutEnttId(target);

        return !didFail;
    }

    bool Deserialize(Bytebuffer* buffer)
    {
        bool didFail = false;

        didFail |= !buffer->GetEnttId(target);

        return !didFail;
    }

    static constexpr size_t GetPacketSize() 
    { 
        return sizeof(entt::entity); 
    };
};