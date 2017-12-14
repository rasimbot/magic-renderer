#ifndef __MAGIC_RENDERER_SHINYMATERIAL_H
#define __MAGIC_RENDERER_SHINYMATERIAL_H

#include "material.h"
#include <random>

namespace Magic
{
    class ShinyMaterial : public Material
    {
    public:
        ShinyMaterial(const RGBf &a_rgbf);
        virtual ~ShinyMaterial();

        virtual void genRay(RenderVar &a) override;
        virtual RGBf fract(RenderVar &a) override;

    private:
        std::mt19937 m_randGenRefl1, m_randGenRefl2;
        std::vector<float> m_i, m_w;
        std::piecewise_linear_distribution<float> m_randRefl1;
        std::uniform_int_distribution<size_t> m_randRefl2;
        RGBf m_rgbf;
    };
}

#endif // __MAGIC_RENDERER_SHINYMATERIAL_H
