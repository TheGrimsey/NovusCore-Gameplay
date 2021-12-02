#pragma once
#include <NovusTypes.h>
#include <Utils/ByteBuffer.h>

struct NetworkComponent
{
    virtual bool Serialize(Bytebuffer* buffer) const = 0;
    virtual bool Deserialize(Bytebuffer* buffer) = 0;

    static constexpr size_t GetPacketSize() { return 0; };
};