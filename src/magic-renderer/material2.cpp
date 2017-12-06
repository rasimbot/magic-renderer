#include "stdafx.h"
#include "material2.h"
#include "sincostab.h"

Magic::Material2::Material2(const RGBf &a_rgbf) :
    m_randGenRefl1(std::random_device()()), m_randGenRefl2(std::random_device()()),
    m_randRefl1(0, SinCosTab::staticInstance().size() / 4),
    m_randRefl2(0, SinCosTab::staticInstance().size()),
    m_rgbf(a_rgbf)
{}

Magic::Material2::~Material2()
{}

void Magic::Material2::genRay(RenderVar &a)
{
    const size_t l_a = m_randRefl1(m_randGenRefl1), l_b = m_randRefl2(m_randGenRefl2);
    const SinCosTab &l_sct(SinCosTab::staticInstance());
    a.m_genRay = Vector3(l_sct.cos(l_a) * l_sct.sin(l_b),
                         l_sct.cos(l_a) * l_sct.cos(l_b), l_sct.sin(l_a));
}

Magic::RGBf Magic::Material2::fract(RenderVar &a)
{
    return m_rgbf;
}
