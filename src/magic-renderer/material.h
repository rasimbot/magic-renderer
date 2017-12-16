#ifndef __MAGIC_RENDERER_MATERIAL_H
#define __MAGIC_RENDERER_MATERIAL_H

#include "rendervar.h"

namespace Magic
{
    class Renderer;

    class Material
    {
    public:
        Material(Renderer *a_renderer);
        virtual ~Material();
        Material(const Material &) = delete;
        Material &operator =(const Material &) = delete;

        virtual bool light(RenderVar &a);
        virtual RGBf lightRgbf(RenderVar &a);
        virtual void genRay(RenderVar &a);
        virtual RGBf fract(RenderVar &a);
    };
}

#endif // __MAGIC_RENDERER_MATERIAL_H
