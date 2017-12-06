#ifndef __MAGIC_RENDERER_OBJECT_H
#define __MAGIC_RENDERER_OBJECT_H

#include "rendervar.h"

namespace Magic
{
    class Object
    {
    public:
        Object();
        virtual ~Object();
        Object(const Object &) = delete;
        Object &operator =(const Object &) = delete;

        virtual bool hit(RenderVar &a);
        virtual bool light();
        virtual RGBf lightRgbf();
        virtual void genRay(RenderVar &a);
        virtual RGBf fract(RenderVar &a);
    };
}

#endif // __MAGIC_RENDERER_OBJECT_H
