#ifndef __MAGIC_RENDERER_BALL_H
#define __MAGIC_RENDERER_BALL_H

#include "object.h"
#include "material.h"

namespace Magic
{
    class Ball : public Object
    {
    public:
        Ball(Renderer *a_renderer, const Vector3 &a_p, float a_r, Material *a_material);
        virtual ~Ball();

        virtual bool hit(RenderVar &a) override;
        virtual bool light(RenderVar &a) override;
        virtual RGBf lightRgbf(RenderVar &a) override;
        virtual void genRay(RenderVar &a) override;
        virtual RGBf fract(RenderVar &a) override;

        void set(const Vector3 &a_p);

    private:
        Vector3 m_p;
        float m_r;
        Material *m_material;
    };
}

#endif // __MAGIC_RENDERER_BALL_H
