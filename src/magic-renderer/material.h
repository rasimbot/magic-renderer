#ifndef __MAGIC_RENDERER_MATERIAL_H
#define __MAGIC_RENDERER_MATERIAL_H

#include "rendervar.h"

namespace Magic
{
    class Material
    {
    public:
        Material();
        virtual ~Material();
        Material(const Material &) = delete;
        Material &operator =(const Material &) = delete;

        virtual bool light();
        virtual RGBf lightRgbf();
        virtual void genRay(RenderVar &a);
        virtual RGBf fract(RenderVar &a);
    };
}

#endif // __MAGIC_RENDERER_MATERIAL_H
