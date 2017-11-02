#ifndef __MAGIC_RENDERER_UTIL_H
#define __MAGIC_RENDERER_UTIL_H

#include "point.h"
#include <cmath>

namespace Magic
{
    float distance(const Point &a_one, const Point &a_another)
    {
        return std::sqrt((a_one.x - a_another.x) * (a_one.x - a_another.x) +
                         (a_one.y - a_another.y) * (a_one.y - a_another.y) +
                         (a_one.z - a_another.z) * (a_one.z - a_another.z));
    }
}

#endif // __MAGIC_RENDERER_UTIL_H
