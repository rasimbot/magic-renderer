#include "stdafx.h"
#include "ball2.h"
#include "renderer.h"
#include "func.h"
#include "sincostab.h"

Magic::Ball2::Ball2(Renderer *a_renderer, const Vector3 &a_p, float a_r, Material *a_material) :
    Object(a_renderer),
    m_p(a_p), m_r(a_r), m_material(a_material)
{}

Magic::Ball2::~Ball2()
{}

bool Magic::Ball2::hit(RenderVar &a)
{
    const Vector3 l_inRaySpace(a.m_space * m_p);
    const float l_d = m_r * m_r -
        l_inRaySpace.x * l_inRaySpace.x - l_inRaySpace.y * l_inRaySpace.y;
    if (l_d < 0) return false;
    const float l_sqrt = std::sqrt(l_d);
    const float l_z1 = l_inRaySpace.z + l_sqrt, l_z2 = l_inRaySpace.z - l_sqrt;
    if (l_z1 < 0 || l_z2 < 0) return false;
    const float l_minZ = std::min(l_z1, l_z2);
    const Vector3 l_from(0, 0, l_minZ);
    const Vector3 l_zDir(l_from - l_inRaySpace);
    const Vector3 l_to(l_from + l_zDir);
    const Vector3 l_up(perpendicular(l_zDir));
    a.m_normal = transf(l_from, l_to, l_up);
    a.m_depth = l_minZ;
    return true;
}

bool Magic::Ball2::light(RenderVar &a)
{
    assert(m_material != nullptr);
    return m_material->light(a);
}

Magic::RGBf Magic::Ball2::lightRgbf(RenderVar &a)
{
    assert(m_material != nullptr);
    return m_material->lightRgbf(a);
}

void Magic::Ball2::genRay(RenderVar &a)
{
    assert(m_material != nullptr);
    m_material->genRay(a);
}

Magic::RGBf Magic::Ball2::fract(RenderVar &a)
{
    assert(m_material != nullptr);
    return m_material->fract(a);
}

void Magic::Ball2::set(const Vector3 &a_p)
{
    m_p = a_p;
}
