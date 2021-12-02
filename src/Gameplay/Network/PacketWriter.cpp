#include "PacketWriter.h"
#include <Networking/NetStructures.h>
#include <Networking/NetPacketHandler.h>

#include <Utils/ByteBuffer.h>
#include <Gameplay/ECS/Components/GameEntity.h>
#include <Gameplay/ECS/Components/Transform.h>

bool PacketWriter::SMSG_CREATE_PLAYER(std::shared_ptr<Bytebuffer>& buffer, entt::entity entity, const GameEntity& gameEntity, const Transform& transform)
{
    bool didFail = false;

    constexpr size_t packetHeaderSize = sizeof(Opcode) + sizeof(u16);
    constexpr size_t packetPayloadSize = sizeof(entt::entity) + GameEntity::GetPacketSize() + Transform::GetPacketSize();

    buffer = Bytebuffer::Borrow<packetHeaderSize + packetPayloadSize>();

    didFail |= !buffer->Put(Opcode::SMSG_CREATE_PLAYER);
    didFail |= !buffer->PutU16(packetPayloadSize);

    didFail |= !buffer->Put(entity);
    didFail |= !buffer->Serialize(gameEntity);
    didFail |= !buffer->Serialize(transform);

    return !didFail;
}

bool PacketWriter::SMSG_CREATE_ENTITY(std::shared_ptr<Bytebuffer>& buffer, entt::entity entity, const GameEntity& gameEntity, const Transform& transform)
{
    bool didFail = false;

    constexpr size_t packetHeaderSize = sizeof(Opcode) + sizeof(u16);
    constexpr size_t packetPayloadSize = sizeof(entt::entity) + GameEntity::GetPacketSize() + Transform::GetPacketSize();

    buffer = Bytebuffer::Borrow<packetHeaderSize + packetPayloadSize>();

    didFail |= !buffer->Put(Opcode::SMSG_CREATE_ENTITY);
    didFail |= !buffer->PutU16(packetPayloadSize);

    didFail |= !buffer->PutU32(entt::to_integral(entity));
    didFail |= !buffer->Serialize(gameEntity);
    didFail |= !buffer->Serialize(transform);

    return !didFail;
}

bool PacketWriter::SMSG_DELETE_ENTITY(std::shared_ptr<Bytebuffer>& buffer, entt::entity entity)
{
    bool didFail = false;

    constexpr size_t packetHeaderSize = sizeof(Opcode) + sizeof(u16);
    constexpr size_t packetPayloadSize = sizeof(entt::entity);

    buffer = Bytebuffer::Borrow<packetHeaderSize + packetPayloadSize>();

    didFail |= !buffer->Put(Opcode::SMSG_DELETE_ENTITY);
    didFail |= !buffer->PutU16(packetPayloadSize);

    didFail |= !buffer->Put(entity);

    return !didFail;
}

bool PacketWriter::SMSG_UPDATE_ENTITY(std::shared_ptr<Bytebuffer>& buffer, entt::entity entity, const Transform& transform)
{
    bool didFail = false;

    constexpr size_t packetHeaderSize = sizeof(Opcode) + sizeof(u16);
    constexpr size_t packetPayloadSize = sizeof(entt::entity) + Transform::GetPacketSize();

    buffer = Bytebuffer::Borrow<packetHeaderSize + packetPayloadSize>();

    didFail |= !buffer->Put(Opcode::SMSG_UPDATE_ENTITY);
    didFail |= !buffer->PutU16(packetPayloadSize);

    didFail |= !buffer->Put(entity);
    didFail |= !buffer->Serialize(transform);

    return !didFail;
}
