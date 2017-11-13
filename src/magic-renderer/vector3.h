#ifndef __MAGIC_RENDERER_VECTOR3_H
#define __MAGIC_RENDERER_VECTOR3_H

#include "vector2.h"
#include <cmath>

namespace Magic
{
    struct Vector3
    {
        float x, y, z;

        Vector3(float a_x = 0, float a_y = 0, float a_z = 0) : x(a_x), y(a_y), z(a_z) {}
        Vector3(const Vector2 &a_v2, float a_w = 1) : x(a_v2.x), y(a_v2.y), z(a_w) {}

        operator Vector2() const { return Vector2{ x, y }; }
    };

    inline Vector3 perpendicular(const Vector3 &a)
    {
        //https://stackoverflow.com/questions/11132681
        return std::abs(a.z) < std::abs(a.x) ? Vector3(a.y, -a.x, 0) : Vector3(0, -a.z, a.y);
    }

    inline float length(const Vector3 &a)
    {
        return std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    }

    inline Vector3 normalized(const Vector3 &a)
    {
        const float l = length(a);
        return Vector3(a.x / l, a.y / l, a.z / l);
    }

    inline Vector3 operator +(const Vector3 &o, const Vector3 &a)
    {
        return Vector3(o.x + a.x, o.y + a.y, o.z + a.z);
    }

    inline Vector3 operator -(const Vector3 &o, const Vector3 &a)
    {
        return Vector3(o.x - a.x, o.y - a.y, o.z - a.z);
    }

    inline float dot(const Vector3 &o, const Vector3 &a)
    {
        return o.x * a.x + o.y * a.y + o.z * a.z;
    }

    inline Vector3 cross(const Vector3 &o, const Vector3 &a)
    {
        return Vector3(o.y * a.z - o.z * a.y,
                       o.z * a.x - o.x * a.z,
                       o.x * a.y - o.y * a.x);
    }
}

#endif // __MAGIC_RENDERER_VECTOR3_H
