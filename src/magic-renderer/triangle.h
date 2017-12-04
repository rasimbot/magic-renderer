#ifndef __MAGIC_RENDERER_TRIANGLE_H
#define __MAGIC_RENDERER_TRIANGLE_H

#include "object.h"

namespace Magic
{
    class Triangle : public Object
    {
    public:
        Triangle(const Vector3 &a_p1, const Vector3 &a_p2,
                 const Vector3 &a_p3, bool a_light, const RGBf &a_rgbf);
        virtual ~Triangle();

        virtual bool hit(ReflArg &a) override;
        virtual bool light() override;
        virtual RGBf rgbf() override;

    private:
        Vector3 m_p1, m_p2, m_p3;
        bool m_light;
        RGBf m_rgbf;
    };
}

#endif // __MAGIC_RENDERER_TRIANGLE_H
