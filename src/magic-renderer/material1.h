#ifndef __MAGIC_RENDERER_MATERIAL1_H
#define __MAGIC_RENDERER_MATERIAL1_H

#include "material.h"

namespace Magic
{
    class Material1 : public Material
    {
    public:
        Material1(const RGBf &a_rgbf);
        virtual ~Material1();

        virtual bool light() override;
        virtual RGBf lightRgbf() override;

    private:
        RGBf m_rgbf;
    };
}

#endif // __MAGIC_RENDERER_MATERIAL1_H
