#ifndef __MAGIC_RENDERER_BALL2_H
#define __MAGIC_RENDERER_BALL2_H

#include "object.h"
#include "material.h"

namespace Magic
{
    class Ball2 : public Object
    {
    public:
        Ball2(Renderer *a_renderer, const Vector3 &a_p, float a_r,
              const Vector3 &a_toNorth, float a_phase,
              Material *a_material, const V2Triple &a_inMaterial);
        virtual ~Ball2();

        virtual bool hit(RenderVar &a) override;
        virtual bool light(RenderVar &a) override;
        virtual RGBf lightRgbf(RenderVar &a) override;
        virtual void genRay(RenderVar &a) override;
        virtual RGBf fract(RenderVar &a) override;

        void set(const Vector3 &a_p);

    private:
        Vector3 m_p;
        float m_r;
        Vector3 m_to, m_up;
        Material *m_material;
        Matrix4 m_p2m;
    };
}

#endif // __MAGIC_RENDERER_BALL2_H
