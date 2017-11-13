#ifndef __MAGIC_RENDERER_FUNC_H
#define __MAGIC_RENDERER_FUNC_H

#include "vector2.h"

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
}

#endif // __MAGIC_RENDERER_FUNC_H
