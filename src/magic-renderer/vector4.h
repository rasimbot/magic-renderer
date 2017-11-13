#ifndef __MAGIC_RENDERER_VECTOR4_H
#define __MAGIC_RENDERER_VECTOR4_H

#include "vector3.h"

namespace Magic
{
    struct Vector4
    {
        float x, y, z, w;

        Vector4(float a_x = 0, float a_y = 0, float a_z = 0, float a_w = 1) : x(a_x), y(a_y), z(a_z), w(a_w) {}
        Vector4(const Vector3 &a_v3, float a_w = 1) : x(a_v3.x), y(a_v3.y), z(a_v3.z), w(a_w) {}

        operator Vector3() const { return Vector3(x, y, z); }
    };
}

#endif // __MAGIC_RENDERER_VECTOR4_H
