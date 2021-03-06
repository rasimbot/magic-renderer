#ifndef __MAGIC_RENDERER_TRIANGLE_H
#define __MAGIC_RENDERER_TRIANGLE_H

#include "object.h"
#include "material.h"
#include <array>

namespace Magic
{
    class Triangle : public Object
    {
    public:
        Triangle(Renderer *a_renderer, const V3Triple &a_inWorld,
                 Material *a_material, const V2Triple &a_inMaterial);
        virtual ~Triangle();

        virtual bool hit(RenderVar &a) override;
        virtual bool light(RenderVar &a) override;
        virtual RGBf lightRgbf(RenderVar &a) override;
        virtual void genRay(RenderVar &a) override;
        virtual RGBf fract(RenderVar &a) override;

    private:
        V3Triple m_w;
        Material *m_material;
        Matrix4 m_p2m;
    };
}

#endif // __MAGIC_RENDERER_TRIANGLE_H
