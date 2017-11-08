#ifndef __MAGIC_RENDERER_BALL_H
#define __MAGIC_RENDERER_BALL_H

#include "object.h"
#include "vector3.h"

namespace Magic
{
    class Ball : public Object
    {
    public:
        Ball(const Vector3 &a_p, float a_r, const ARGB &a_c);
        virtual ~Ball();

        virtual float hit(const Matrix4 &a_ray) const override;
        virtual ARGB color() const override;

    private:
        Vector3 m_p;
        float m_r;
        ARGB m_c;
    };
}

#endif // __MAGIC_RENDERER_BALL_H
