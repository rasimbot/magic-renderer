#include "stdafx.h"
#include "shinymaterial.h"
#include "sincostab.h"
#include "renderer.h"

Magic::ShinyMaterial::ShinyMaterial(Renderer *a_renderer, const RGBf &a_rgbf) :
    Material(a_renderer),
    m_i{ 0,
         SinCosTab::staticInstance().size() / 36.0f,
         SinCosTab::staticInstance().size() / 18.0f,
         SinCosTab::staticInstance().size() / 7.2f,
         SinCosTab::staticInstance().size() / 2.0f },
    m_w{ 1, 0.4f, 0.25f, 0.125f, 0 },
    m_vPtd( a_renderer->threadNumber(),
        { decltype(PerThreadData::m_randGenRefl1)(),
          decltype(PerThreadData::m_randGenRefl2)(),
          decltype(PerThreadData::m_randRefl1)(m_i.begin(), m_i.end(), m_w.begin()),
          decltype(PerThreadData::m_randRefl2)(0, SinCosTab::staticInstance().size()) }),
    m_rgbf(a_rgbf)
{
    std::random_device l_dev;
    for (auto &u : m_vPtd) { u.m_randGenRefl1.seed(l_dev()); u.m_randGenRefl2.seed(l_dev()); }
}

Magic::ShinyMaterial::~ShinyMaterial()
{}

void Magic::ShinyMaterial::genRay(RenderVar &a)
{
    assert(a.m_ti < m_vPtd.size());
    PerThreadData &l_ptd = m_vPtd[a.m_ti];
    const size_t l_a = size_t(l_ptd.m_randRefl1(l_ptd.m_randGenRefl1)),
                 l_b = l_ptd.m_randRefl2(l_ptd.m_randGenRefl2);
    const SinCosTab &l_sct(SinCosTab::staticInstance());
    a.m_genRay = Vector3(l_sct.sin(l_a) * l_sct.cos(l_b),
                         l_sct.sin(l_a) * l_sct.sin(l_b), l_sct.cos(l_a));
}

Magic::RGBf Magic::ShinyMaterial::fract(RenderVar &a)
{
    return m_rgbf;
}
