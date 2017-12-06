#ifndef __MAGIC_RENDERER_TRIANGLE_H
#define __MAGIC_RENDERER_TRIANGLE_H

#include "object.h"
#include "material.h"

namespace Magic
{
    class Triangle : public Object
    {
    public:
        Triangle(const Vector3 &a_p1, const Vector3 &a_p2,
                 const Vector3 &a_p3, Material *a_material);
        virtual ~Triangle();

        virtual bool hit(RenderVar &a) override;
        virtual bool light() override;
        virtual RGBf lightRgbf() override;
        virtual void genRay(RenderVar &a) override;
        virtual RGBf fract(RenderVar &a) override;

    private:
        Vector3 m_p1, m_p2, m_p3;
        Material *m_material;
    };
}

#endif // __MAGIC_RENDERER_TRIANGLE_H
