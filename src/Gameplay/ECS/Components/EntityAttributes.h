#pragma once
#include <NovusTypes.h>
#include <Utils/ByteBuffer.h>
#include "NetworkComponent.h"

enum class EntityAttributeType : u8
{
    INVALID,

    STRENGTH,
    AGILITY,
    INTELLECT,

    STAMINA,
    SPIRIT,
    ARMOR,

    COUNT
};

struct EntityAttributes : NetworkComponent
{
    static constexpr u8 AttributeCount = static_cast<u8>(EntityAttributeType::COUNT);
    f32 attributes[AttributeCount] = { 0.0f };

    static constexpr size_t GetPacketSize()
    {
        return AttributeCount * sizeof(f32) * 2;
    }

    // Network Helpers
    bool Serialize(Bytebuffer* buffer) const
    {
        bool didFail = false;

        constexpr size_t AttributeArraySize = GetPacketSize();
        didFail |= !buffer->PutBytes(reinterpret_cast<const u8*>(&attributes[0]), AttributeArraySize);

        return !didFail;
    }

    bool Deserialize(Bytebuffer* buffer)
    {
        bool didFail = false;

        constexpr size_t AttributeArraySize = GetPacketSize();
        didFail |= !buffer->GetBytes(reinterpret_cast<u8*>(&attributes[0]), AttributeArraySize);

        return !didFail;
    }

};