#ifndef __MAGIC_RENDERER_RGBF_H
#define __MAGIC_RENDERER_RGBF_H

namespace Magic
{
    struct RGBf
    {
        float b = 0, g = 0, r = 0;
    };

    inline RGBf operator *(const RGBf &o, const RGBf &a)
    {
        return RGBf{ o.b * a.b, o.g * a.g, o.r * a.r };
    }
}

#endif // __MAGIC_RENDERER_RGBF_H
