#ifndef __MAGIC_RENDERER_MATERIAL1_H
#define __MAGIC_RENDERER_MATERIAL1_H

#include "material.h"

namespace Magic
{
    class Material1 : public Material
    {
    public:
        Material1(Renderer *a_renderer, const RGBf &a_rgbf);
        virtual ~Material1();

        virtual bool light(RenderVar &a) override;
        virtual RGBf lightRgbf(RenderVar &a) override;

    private:
        RGBf m_rgbf;
    };
}

#endif // __MAGIC_RENDERER_MATERIAL1_H
