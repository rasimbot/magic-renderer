#ifndef __MAGIC_RENDERER_BALL_H
#define __MAGIC_RENDERER_BALL_H

#include "object.h"
#include "vector3.h"

namespace Magic
{
    class Ball : public Object
    {
    public:
        Ball(const Vector3 &a_p, float a_r, bool a_light, const RGBf &a_rgbf);
        virtual ~Ball();

        virtual bool hit(const Matrix4 &a_ray, Matrix4 &a_normal, float &a_depth) const override;
        virtual bool light() const override;
        virtual RGBf rgbf() const override;

        void set(const Vector3 &a_p);

    private:
        Vector3 m_p;
        float m_r;
        bool m_light;
        RGBf m_rgbf;
    };
}

#endif // __MAGIC_RENDERER_BALL_H
