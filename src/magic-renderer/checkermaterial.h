#ifndef __MAGIC_RENDERER_CHECKERMATERIAL_H
#define __MAGIC_RENDERER_CHECKERMATERIAL_H

#include "material.h"
#include <vector>
#include <random>

namespace Magic
{
    class CheckerMaterial : public Material
    {
        struct PerThreadData
        {
            std::mt19937 m_randGenRefl1, m_randGenRefl2;
            std::uniform_int_distribution<size_t> m_randRefl1, m_randRefl2;
        };

    public:
        CheckerMaterial(Renderer *a_renderer, const RGBf &a_rgbf1, const RGBf &a_rgbf2);
        virtual ~CheckerMaterial();

        virtual void genRay(RenderVar &a) override;
        virtual RGBf fract(RenderVar &a) override;

    private:
        std::vector<PerThreadData> m_vPtd;
        RGBf m_rgbf1, m_rgbf2;
    };
}

#endif // __MAGIC_RENDERER_CHECKERMATERIAL_H
