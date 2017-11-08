#ifndef __MAGIC_RENDERER_OBJECT_H
#define __MAGIC_RENDERER_OBJECT_H

#include "matrix4.h"
#include "argb.h"

namespace Magic
{
    class Object
    {
    public:
        virtual ~Object();

        virtual float hit(const Matrix4 &a_ray) const;
        virtual ARGB color() const;
    };
}

#endif // __MAGIC_RENDERER_OBJECT_H
