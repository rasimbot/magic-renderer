#include "stdafx.h"
#include "material2.h"
#include "sincostab.h"
#include "renderer.h"

Magic::Material2::Material2(Renderer *a_renderer, const RGBf &a_rgbf) :
    Material(a_renderer),
    m_vPtd(a_renderer->threadNumber(),
        { decltype(PerThreadData::m_randGenRefl1)(),
          decltype(PerThreadData::m_randGenRefl2)(),
          decltype(PerThreadData::m_randRefl1)(0, SinCosTab::staticInstance().size() / 4),
          decltype(PerThreadData::m_randRefl2)(0, SinCosTab::staticInstance().size()) }),
    m_rgbf(a_rgbf)
{
    std::random_device l_dev;
    for (auto &u : m_vPtd) { u.m_randGenRefl1.seed(l_dev()); u.m_randGenRefl2.seed(l_dev()); }
}

Magic::Material2::~Material2()
{}

void Magic::Material2::genRay(RenderVar &a)
{
    assert(a.m_ti < m_vPtd.size());
    PerThreadData &l_ptd = m_vPtd[a.m_ti];
    const size_t l_a = l_ptd.m_randRefl1(l_ptd.m_randGenRefl1),
                 l_b = l_ptd.m_randRefl2(l_ptd.m_randGenRefl2);
    const SinCosTab &l_sct(SinCosTab::staticInstance());
    a.m_genRay = Vector3(l_sct.cos(l_a) * l_sct.sin(l_b),
                         l_sct.cos(l_a) * l_sct.cos(l_b), l_sct.sin(l_a));
}

Magic::RGBf Magic::Material2::fract(RenderVar &a)
{
    return m_rgbf;
}
