#pragma once
#include <NovusTypes.h>
#include <Utils/ByteBuffer.h>
#include "NetworkComponent.h"

enum class EntityResourceType : u8
{
    INVALID,
    HEALTH,
    MANA,
    ENERGY,
    RAGE,
    FOCUS,
    RUNICPOWER,
    
    COUNT
};

struct EntityResources : NetworkComponent
{
    static constexpr u8 ResourceCount = static_cast<u8>(EntityResourceType::COUNT);
    f32 current[ResourceCount] = { 0.0f };
    f32 max[ResourceCount] = { 0.0f };

    static constexpr size_t GetPacketSize()
    {
        return ResourceCount * sizeof(f32) * 2;
    }

    // Network Helpers
    bool Serialize(Bytebuffer* buffer) const
    {
        bool didFail = false;

        constexpr size_t ResourceArraySize = GetPacketSize() / 2;
        didFail |= !buffer->PutBytes(reinterpret_cast<const u8*>(&current[0]), ResourceArraySize);
        didFail |= !buffer->PutBytes(reinterpret_cast<const u8*>(&max[0]), ResourceArraySize);

        return !didFail;
    }

    bool Deserialize(Bytebuffer* buffer)
    {
        bool didFail = false;

        constexpr size_t ResourceArraySize = GetPacketSize() / 2;
        didFail |= !buffer->GetBytes(reinterpret_cast<u8*>(&current[0]), ResourceArraySize);
        didFail |= !buffer->GetBytes(reinterpret_cast<u8*>(&max[0]), ResourceArraySize);

        return !didFail;
    }

};