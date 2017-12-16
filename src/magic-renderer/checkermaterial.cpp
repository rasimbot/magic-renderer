#include "stdafx.h"
#include "checkermaterial.h"
#include "sincostab.h"
#include "renderer.h"

Magic::CheckerMaterial::CheckerMaterial(Renderer *a_renderer, const RGBf &a_rgbf1, const RGBf &a_rgbf2) :
    Material(a_renderer),
    m_vPtd(a_renderer->threadNumber(),
        { decltype(PerThreadData::m_randGenRefl1)(),
          decltype(PerThreadData::m_randGenRefl2)(),
          decltype(PerThreadData::m_randRefl1)(0, SinCosTab::staticInstance().size() / 4),
          decltype(PerThreadData::m_randRefl2)(0, SinCosTab::staticInstance().size()) }),
    m_rgbf1(a_rgbf1), m_rgbf2(a_rgbf2)
{
    std::random_device l_dev;
    for (auto &u : m_vPtd) { u.m_randGenRefl1.seed(l_dev()); u.m_randGenRefl2.seed(l_dev()); }
}

Magic::CheckerMaterial::~CheckerMaterial()
{}

void Magic::CheckerMaterial::genRay(RenderVar &a)
{
    assert(a.m_ti < m_vPtd.size());
    PerThreadData &l_ptd = m_vPtd[a.m_ti];
    const size_t l_a = l_ptd.m_randRefl1(l_ptd.m_randGenRefl1),
                 l_b = l_ptd.m_randRefl2(l_ptd.m_randGenRefl2);
    const SinCosTab &l_sct(SinCosTab::staticInstance());
    a.m_genRay = Vector3(l_sct.cos(l_a) * l_sct.sin(l_b),
                         l_sct.cos(l_a) * l_sct.cos(l_b), l_sct.sin(l_a));
}

Magic::RGBf Magic::CheckerMaterial::fract(RenderVar &a)
{
    const int l_intSum = int(a.m_surface.x) + int(a.m_surface.y);
    return l_intSum % 2 == 0 ? m_rgbf1 : m_rgbf2;
}
