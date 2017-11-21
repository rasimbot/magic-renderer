#ifndef __MAGIC_RENDERER_ARGB_H
#define __MAGIC_RENDERER_ARGB_H

#include "rgbf.h"
#include <cmath>

namespace Magic
{
    struct ARGB
    {
        unsigned char b, g, r, a;

        ARGB(unsigned char a_b = 0, unsigned char a_g = 0,
             unsigned char a_r = 0, unsigned char a_a = 255) :
            b(a_b), g(a_g), r(a_r), a(a_a)
        {}

        ARGB(const RGBf &a, unsigned char a_a = 255) :
            b(sat(a.b)), g(sat(a.g)), r(sat(a.r)), a(a_a)
        {}

        unsigned char sat(float a) { return unsigned char(a > 255 ? 255 : std::nearbyint(a)); }
    };
}

#endif // __MAGIC_RENDERER_ARGB_H
