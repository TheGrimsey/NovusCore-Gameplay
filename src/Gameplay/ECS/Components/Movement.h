#pragma once
#include <NovusTypes.h>
#include <glm/matrix.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/euler_angles.hpp>

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

            u16 value = 0;
        };
    };

    vec3 velocity = hvec3(0.f, 0.f, 0.f);

    f32 moveSpeed = f16(7.1111f);
    f32 fallSpeed = f16(19.5f);
    f32 fallAcceleration = f16(7.33f);

    Flags flags;
};