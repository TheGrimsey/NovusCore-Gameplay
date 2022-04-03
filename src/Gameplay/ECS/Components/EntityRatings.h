#pragma once
#include <NovusTypes.h>
#include <Utils/ByteBuffer.h>
#include "NetworkComponent.h"

enum class EntityRatingType : u8
{
    HASTE,
    
    PARRY_CHANCE,
    DODGE_CHANCE,
    
    CRITICAL_STRIKE_CHANCE,
    MELEE_HIT_CHANCE,
    SPELL_HIT_CHANCE,
    HIT_CHANCE,
    
    COUNT
};

struct EntityRatings: NetworkComponent
{
    static constexpr u8 RatingsCount = static_cast<u8>(EntityRatingType::COUNT);
    f16 current[RatingsCount] = { f16(0.0f) };

    static constexpr size_t GetPacketSize()
    {
        return RatingsCount * sizeof(f16);
    }

    // Network Helpers
    bool Serialize(Bytebuffer* buffer) const
    {
        bool didFail = false;

        constexpr size_t RatingsArraySize = GetPacketSize();
        didFail |= !buffer->PutBytes(reinterpret_cast<const u8*>(&current[0]), RatingsArraySize);

        return !didFail;
    }

    bool Deserialize(Bytebuffer* buffer)
    {
        bool didFail = false;

        constexpr size_t RatingsArraySize = GetPacketSize();
        didFail |= !buffer->GetBytes(reinterpret_cast<u8*>(&current[0]), RatingsArraySize);

        return !didFail;
    }

};