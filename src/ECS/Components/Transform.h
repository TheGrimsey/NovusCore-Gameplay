#pragma once
#include <NovusTypes.h>
#include <glm/matrix.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/euler_angles.hpp>

struct Transform
{
    hvec3 position  = hvec3(0.f, 0.f, 0.f);
    hvec3 rotation  = hvec3(0.f, 0.f, 0.f);
    hvec3 scale     = hvec3(1.f, 1.f, 1.f);
};

struct TransformIsDirty
{
    TransformIsDirty() {}
}; // Empty struct

struct Movement
{
    struct Flags
    {
        union
        {
            struct
            {
                u8 FORWARD : 1;
                u8 BACKWARD : 1;
                u8 LEFT : 1;
                u8 RIGHT : 1;
                u8 GROUNDED : 1;
            };

            u16 value;
        };
    };

    hvec3 velocity = hvec3(0.f, 0.f, 0.f);

    f16 moveSpeed = f16(7.1111f);
    f16 fallSpeed = f16(19.5f);
    f16 fallAcceleration = f16(7.33f);

    f16 yaw = f16(0.0f);
    f16 pitch = f16(0.0f);

    f16 yawBase = f16(0.0f);
    f16 yawOffset = f16(0.0f);

    Flags flags;

    // Roll, Pitch, Yaw
    vec3 GetEulerAngles() const { return vec3(0, pitch, yaw); }
    quaternion GetQuaternion() const { return glm::quat(glm::vec3(0.0f, glm::radians(pitch), glm::radians(yaw))); }

    mat4x4 GetRotationMatrix()
    {
        glm::quat rotQuat = glm::quat(glm::vec3(0.0f, glm::radians(pitch), glm::radians(yaw)));
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
};