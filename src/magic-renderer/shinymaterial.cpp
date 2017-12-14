#include "stdafx.h"
#include "shinymaterial.h"
#include "sincostab.h"

Magic::ShinyMaterial::ShinyMaterial(const RGBf &a_rgbf) :
    m_randGenRefl1(std::random_device()()), m_randGenRefl2(std::random_device()()),
    m_i{ 0,
         SinCosTab::staticInstance().size() / 36.0f,
         SinCosTab::staticInstance().size() / 18.0f,
         SinCosTab::staticInstance().size() / 7.2f,
         SinCosTab::staticInstance().size() / 2.0f },
    m_w{ 1, 0.4f, 0.25f, 0.125f, 0 },
    m_randRefl1(m_i.begin(), m_i.end(), m_w.begin()),
    m_randRefl2(0, SinCosTab::staticInstance().size()),
    m_rgbf(a_rgbf)
{}

Magic::ShinyMaterial::~ShinyMaterial()
{}

void Magic::ShinyMaterial::genRay(RenderVar &a)
{
    const size_t l_a = size_t(m_randRefl1(m_randGenRefl1)), l_b = m_randRefl2(m_randGenRefl2);
    const SinCosTab &l_sct(SinCosTab::staticInstance());
    a.m_genRay = Vector3(l_sct.sin(l_a) * l_sct.cos(l_b),
                         l_sct.sin(l_a) * l_sct.sin(l_b), l_sct.cos(l_a));
}

Magic::RGBf Magic::ShinyMaterial::fract(RenderVar &a)
{
    return m_rgbf;
}
