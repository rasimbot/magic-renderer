#include "stdafx.h"
#include "ball2.h"
#include "renderer.h"
#include "func.h"
#include "sincostab.h"
#include "defs.h"

Magic::Ball2::Ball2(Renderer *a_renderer, const Vector3 &a_p, float a_r,
                    const Vector3 &a_toNorth, float a_phase,
                    Material *a_material, const V2Triple &a_inMaterial) :
    Object(a_renderer),
    m_p(a_p), m_r(a_r),
    m_to(m_p + Vector3(0, 0, 1)), m_up(0, 1, 0),
    m_material(a_material),
    m_p2m(proportionalToMaterial(a_inMaterial))
{
    const float l_phaseAngle = float(2 * s_piD) * a_phase;
    const Vector3 l_phaseZa(-std::sin(l_phaseAngle), 0, std::cos(l_phaseAngle));
    m_to = m_p + l_phaseZa;
    const Vector3 l_ya(a_toNorth - m_p);
    const Vector3 l_rotAxis(cross(l_ya, Vector3(0, 1, 0)));
    const float l_xzLength = length(Vector3(l_ya.x, 0, l_ya.z));
    const Matrix4 l_l2w(rotateArbitr(l_rotAxis, Vector3(l_ya.y, -l_xzLength)));
    if (!isFinite(l_l2w)) return;
    m_to = m_p + l_l2w * l_phaseZa;
    m_up = l_l2w * Vector3(0, 1, 0);
}

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

    const Vector3 l_toInRaySpace(a.m_space * m_to);
    const Vector3 l_upInRaySpace(a.m_space * m_up);
    const Matrix4 l_rs2l(transf(l_inRaySpace, l_toInRaySpace, l_upInRaySpace));
    const Vector3 l_local(l_rs2l * l_from);
    const float l_alpha = std::atan2(l_local.z, l_local.x);
    const float l_beta = std::asin(l_local.y / m_r);
    const float l_alpha2pi = l_alpha >= 0 ? l_alpha : l_alpha + float(2 * s_piD);
    const float l_betaPi = l_beta + float(0.5 * s_piD);
    const Vector3 l_proportional(l_alpha2pi / float(2 * s_piD), l_betaPi / s_piF);
    a.m_surface = Vector3(m_p2m * l_proportional);

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
