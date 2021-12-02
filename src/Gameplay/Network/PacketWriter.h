#pragma once
#include <entity/fwd.hpp>

class Bytebuffer;
struct GameEntity;
struct Transform;

class PacketWriter
{
public:
    static bool SMSG_CREATE_PLAYER(std::shared_ptr<Bytebuffer>& buffer, entt::entity entity, const GameEntity& gameEntity, const Transform& transform);
    static bool SMSG_CREATE_ENTITY(std::shared_ptr<Bytebuffer>& buffer, entt::entity entity, const GameEntity& gameEntity, const Transform& transform);
    static bool SMSG_DELETE_ENTITY(std::shared_ptr<Bytebuffer>& buffer, entt::entity entity);
    static bool SMSG_UPDATE_ENTITY(std::shared_ptr<Bytebuffer>& buffer, entt::entity entity, const Transform& transform);
};