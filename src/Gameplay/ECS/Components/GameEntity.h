#pragma once
#include <NovusTypes.h>
#include <entt.hpp>
#include "NetworkComponent.h"

struct SeenEntityInfo
{
    vec2 position = vec2(0.0f, 0.0f);
    entt::entity entityID = entt::null;
};

struct GameEntity : NetworkComponent
{
    enum class Type : u8
    {
        Player,
        Creature,
        Gameobject,
        Invalid
    };

    GameEntity() { }
    GameEntity(Type inType) : type(inType) { }
    GameEntity(Type inType, u32 inDisplayID) : type(inType), displayID(inDisplayID) { }

    Type type = Type::Invalid;
    u32 displayID = 0;
    std::vector<entt::entity> seenEntities;

    // Network Helpers
    bool Serialize(Bytebuffer* buffer) const
    {
        bool didFail = false;

        didFail |= !buffer->Put<Type>(type);
        didFail |= !buffer->PutU32(displayID);

        return !didFail;
    }

    bool Deserialize(Bytebuffer* buffer)
    {
        bool didFail = false;

        didFail |= !buffer->Get<Type>(type);
        didFail |= !buffer->GetU32(displayID);

        return !didFail;
    }

    static constexpr size_t GetPacketSize()
    {
        return sizeof(Type) + sizeof(u32);
    }
};