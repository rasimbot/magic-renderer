#ifndef __MAGIC_RENDERER_OBJECT_H
#define __MAGIC_RENDERER_OBJECT_H

#include "matrix4.h"
#include "argb.h"
#include "rgbf.h"

namespace Magic
{
    class Object
    {
    public:
        virtual ~Object();

        virtual bool hit(const Matrix4 &a_ray, Matrix4 &a_normal) const;
        virtual bool light() const;
        virtual RGBf rgbf() const;
    };
}

#endif // __MAGIC_RENDERER_OBJECT_H
