#ifndef __MAGIC_RENDERER_FUNC_H
#define __MAGIC_RENDERER_FUNC_H

#include "vector2.h"
#include "vector3.h"
#include "matrix4.h"

namespace Magic
{
    //https://stackoverflow.com/a/2049593/5634114
    inline float signOfY(const Vector2 &a_p, const Vector2 &a_xp1, const Vector2 &a_xp2)
    {
        return (a_p.x - a_xp2.x) * (a_xp1.y - a_xp2.y) - (a_xp1.x - a_xp2.x) * (a_p.y - a_xp2.y);
    }

    inline bool isPointInTriangle(const Vector2 &a_p, const Vector2 &a_t1,
                                  const Vector2 &a_t2, const Vector2 &a_t3)
    {
        return signOfY(a_p, a_t1, a_t2) > 0 &&
               signOfY(a_p, a_t2, a_t3) > 0 &&
               signOfY(a_p, a_t3, a_t1) > 0;
    }

    inline Matrix4 transf(const Vector3 &a_from, const Vector3 &a_to, const Vector3 &a_up)
    {
        //https://msdn.microsoft.com/ru-ru/library/windows/desktop/bb205342(v=vs.85).aspx
        const Vector3 l_za(normalized(a_to - a_from));
        const Vector3 l_xa(normalized(cross(a_up, l_za)));
        const Vector3 l_ya(cross(l_za, l_xa));
        return Matrix4{ l_xa.x, l_xa.y, l_xa.z, -dot(l_xa, a_from),
                        l_ya.x, l_ya.y, l_ya.z, -dot(l_ya, a_from),
                        l_za.x, l_za.y, l_za.z, -dot(l_za, a_from),
                        0, 0, 0, 1 };
    }

    inline Matrix4 translate(const Vector3 &a)
    {
        return Matrix4{ 1, 0, 0, a.x,
                        0, 1, 0, a.y,
                        0, 0, 1, a.z,
                        0, 0, 0, 1 };
    }

    inline Matrix4 rotateXY(const Vector3 &a)
    {
        const float l_length = length(a);
        const float l_sin = a.y / l_length, l_cos = a.x / l_length;
        return Matrix4{ l_cos, -l_sin, 0, 0,
                        l_sin, l_cos, 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1 };
    }

    inline Matrix4 scale(const Vector3 &a)
    {
        return Matrix4{ a.x, 0, 0, 0,
                        0, a.y, 0, 0,
                        0, 0, a.z, 0,
                        0, 0, 0, 1 };
    }
}

#endif // __MAGIC_RENDERER_FUNC_H
