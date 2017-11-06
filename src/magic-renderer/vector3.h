#ifndef __MAGIC_RENDERER_VECTOR3_H
#define __MAGIC_RENDERER_VECTOR3_H

#include <cmath>

namespace Magic
{
    struct Vector3
    {
        float x = 0, y = 0, z = 0;
    };

    inline Vector3 normalized(const Vector3 &a)
    {
        const float l = std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
        return Vector3{ a.x / l, a.y / l, a.z / l };
    }

    inline Vector3 operator -(const Vector3 &o, const Vector3 &a)
    {
        return Vector3{ o.x - a.x, o.y - a.y, o.z - a.z };
    }

    inline float dot(const Vector3 &o, const Vector3 &a)
    {
        return o.x * a.x + o.y * a.y + o.z * a.z;
    }

    inline Vector3 cross(const Vector3 &o, const Vector3 &a)
    {
        return Vector3{ o.y * a.z - o.z * a.y,
                        o.z * a.x - o.x * a.z,
                        o.x * a.y - o.y * a.x };
    }
}

#endif // __MAGIC_RENDERER_VECTOR3_H
