#include "stdafx.h"
#include "checkermaterial.h"
#include "sincostab.h"

Magic::CheckerMaterial::CheckerMaterial(const RGBf &a_rgbf1, const RGBf &a_rgbf2) :
    m_randGenRefl1(std::random_device()()), m_randGenRefl2(std::random_device()()),
    m_randRefl1(0, SinCosTab::staticInstance().size() / 4),
    m_randRefl2(0, SinCosTab::staticInstance().size()),
    m_rgbf1(a_rgbf1), m_rgbf2(a_rgbf2)
{}

Magic::CheckerMaterial::~CheckerMaterial()
{}

void Magic::CheckerMaterial::genRay(RenderVar &a)
{
    const size_t l_a = m_randRefl1(m_randGenRefl1), l_b = m_randRefl2(m_randGenRefl2);
    const SinCosTab &l_sct(SinCosTab::staticInstance());
    a.m_genRay = Vector3(l_sct.cos(l_a) * l_sct.sin(l_b),
                         l_sct.cos(l_a) * l_sct.cos(l_b), l_sct.sin(l_a));
}

Magic::RGBf Magic::CheckerMaterial::fract(RenderVar &a)
{
    const int l_intSum = int(a.m_surface.x) + int(a.m_surface.y);
    return l_intSum % 2 == 0 ? m_rgbf1 : m_rgbf2;
}
