#ifndef __MAGIC_RENDERER_OBJECT_H
#define __MAGIC_RENDERER_OBJECT_H

#include "matrix4.h"
#include "argb.h"
#include "rgbf.h"
#include "rendervar.h"

namespace Magic
{
    class Object
    {
    public:
        virtual ~Object();

        virtual bool hit(RenderVar &a);
        virtual bool light();
        virtual RGBf lightRgbf();
        virtual void genRay(RenderVar &a);
        virtual RGBf fract(RenderVar &a);
    };
}

#endif // __MAGIC_RENDERER_OBJECT_H
