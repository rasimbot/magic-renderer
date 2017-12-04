#ifndef __MAGIC_RENDERER_OBJECT_H
#define __MAGIC_RENDERER_OBJECT_H

#include "matrix4.h"
#include "argb.h"
#include "rgbf.h"
#include "reflarg.h"

namespace Magic
{
    class Object
    {
    public:
        virtual ~Object();

        virtual bool hit(ReflArg &a);
        virtual bool light();
        virtual RGBf rgbf();
    };
}

#endif // __MAGIC_RENDERER_OBJECT_H
