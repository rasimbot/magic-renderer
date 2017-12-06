#ifndef __MAGIC_RENDERER_MATERIAL2_H
#define __MAGIC_RENDERER_MATERIAL2_H

#include "material.h"
#include <random>

namespace Magic
{
    class Material2 : public Material
    {
    public:
        Material2(const RGBf &a_rgbf);
        virtual ~Material2();

        virtual void genRay(RenderVar &a) override;
        virtual RGBf fract(RenderVar &a) override;

    private:
        std::mt19937 m_randGenRefl1, m_randGenRefl2;
        std::uniform_int_distribution<size_t> m_randRefl1, m_randRefl2;
        RGBf m_rgbf;
    };
}

#endif // __MAGIC_RENDERER_MATERIAL2_H
