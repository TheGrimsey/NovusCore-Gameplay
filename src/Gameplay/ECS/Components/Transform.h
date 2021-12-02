#pragma once
#include <NovusTypes.h>
#include <Utils/ByteBuffer.h>
#include "NetworkComponent.h"

struct Transform : NetworkComponent
{
    vec3 position  = vec3(0.f, 0.f, 0.f);
    vec3 rotation  = vec3(0.f, 0.f, 0.f);
    vec3 scale     = vec3(1.f, 1.f, 1.f);

    f32 yawOffset = 0.0f;

    // Roll, Pitch, Yaw
    vec3 GetEulerAngles() const { return rotation; }
    quaternion GetQuaternion() const { return glm::quat(glm::radians(rotation)); }
    mat4x4 GetRotationMatrix()
    {
        return glm::mat4_cast(GetQuaternion());
    }
    mat4x4 GetRotationMatrix(vec3& front, vec3& up, vec3& left)
    {
        mat4x4 rotationMatrix = GetRotationMatrix();

        front = rotationMatrix[0];
        up = rotationMatrix[2];
        left = rotationMatrix[1];

        return rotationMatrix;
    }
    mat4x4 GetInstanceMatrix()
    {
        // When we pass 1 into the constructor, it will construct an identity matrix
        mat4x4 matrix(1);

        // Order is important here (Go lookup how matrices work if confused)
        matrix = glm::translate(matrix, position);
        matrix *= GetRotationMatrix();
        matrix = glm::scale(matrix, scale);

        return matrix;
    }

    // Network Helpers
    bool Serialize(Bytebuffer* buffer) const
    {
        bool didFail = false;

        didFail |= !buffer->Put<vec3>(position);
        didFail |= !buffer->Put<vec3>(rotation);
        didFail |= !buffer->Put<vec3>(scale);

        return !didFail;
    }

    bool Deserialize(Bytebuffer* buffer)
    {
        bool didFail = false;

        didFail |= !buffer->Get<vec3>(position);
        didFail |= !buffer->Get<vec3>(rotation);
        didFail |= !buffer->Get<vec3>(scale);

        return !didFail;
    }

    static constexpr size_t GetPacketSize()
    {
        return sizeof(vec3) * 3;
    }
};

struct TransformIsDirty
{
    TransformIsDirty() {}
}; // Empty struct