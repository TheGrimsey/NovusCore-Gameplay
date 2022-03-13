#pragma once
#include <entity/fwd.hpp>

class Bytebuffer;
struct GameEntity;
struct Transform;
struct EntityResources;
struct EntityAttributes;
struct EntityRatings;

class PacketWriter
{
public:
    static bool SMSG_CREATE_PLAYER(std::shared_ptr<Bytebuffer>& buffer, entt::entity entity, const GameEntity& gameEntity, const Transform& transform);
    static bool SMSG_CREATE_ENTITY(std::shared_ptr<Bytebuffer>& buffer, entt::entity entity, const GameEntity& gameEntity, const Transform& transform);
    static bool SMSG_DELETE_ENTITY(std::shared_ptr<Bytebuffer>& buffer, entt::entity entity);
    static bool SMSG_UPDATE_ENTITY(std::shared_ptr<Bytebuffer>& buffer, entt::entity entity, const Transform& transform);

    static bool SMSG_ENTITY_RESOURCES_UPDATE(std::shared_ptr<Bytebuffer>& buffer, entt::entity entity, const EntityResources& resources);
    static bool SMSG_ENTITY_ATTRIBUTES_UPDATE(std::shared_ptr<Bytebuffer>& buffer, entt::entity entity, const EntityAttributes& attributes);
    static bool SMSG_ENTITY_RATINGS_UPDATE(std::shared_ptr<Bytebuffer>& buffer, entt::entity entity, const EntityRatings& ratings);
};