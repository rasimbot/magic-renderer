#ifndef __MAGIC_RENDERER_OBJECT_H
#define __MAGIC_RENDERER_OBJECT_H

#include "rendervar.h"

namespace Magic
{
    class Renderer;

    typedef std::array<Vector2, 3> V2Triple;
    typedef std::array<Vector3, 3> V3Triple;

    class Object
    {
    public:
        Object(Renderer *a_renderer);
        virtual ~Object();
        Object(const Object &) = delete;
        Object &operator =(const Object &) = delete;

        virtual bool hit(RenderVar &a);
        virtual bool light(RenderVar &a);
        virtual RGBf lightRgbf(RenderVar &a);
        virtual void genRay(RenderVar &a);
        virtual RGBf fract(RenderVar &a);

        static Matrix4 proportionalToMaterial(const V2Triple &a_inMaterial);
    };
}

#endif // __MAGIC_RENDERER_OBJECT_H
