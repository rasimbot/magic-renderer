#include "stdafx.h"
#include "triangle.h"
#include "renderer.h"
#include "func.h"
#include "sincostab.h"

Magic::Triangle::Triangle(Renderer *a_renderer, const V3Triple &a_inWorld,
                          Material *a_material, const V2Triple &a_inMaterial) :
    Object(a_renderer),
    m_w(a_inWorld), m_material(a_material),
    m_p2m(proportionalToMaterial(a_inMaterial))
{
    assert(m_material != nullptr);
}

Magic::Triangle::~Triangle()
{}

bool Magic::Triangle::hit(RenderVar &a)
{
    const Vector3 l_r1(a.m_space * m_w[0]), l_r2(a.m_space * m_w[1]), l_r3(a.m_space * m_w[2]);
    if (!isPointInTriangle(Vector2(), l_r1, l_r2, l_r3)) return false;
    const Vector3 l_v1(l_r2 - l_r1), l_v2(l_r3 - l_r1);
    const Vector3 l_n(cross(l_v1, l_v2));
    const float l_z = (l_n.x * l_r2.x + l_n.y * l_r2.y + l_n.z * l_r2.z) / l_n.z;
    if (l_z < 0) return false;
    const Vector3 l_from1(0, 0, l_z), l_to1(l_from1 - l_n), l_up1(perpendicular(-l_n));
    a.m_normal = transf(l_from1, l_to1, l_up1);
    a.m_depth = l_z;
    const Vector3 l_to2(l_r1 + l_n), l_up2(cross(l_n, l_v1));
    const Matrix4 l_r2t(transf(l_r1, l_to2, l_up2));
    const Vector3 l_t2(l_r2t * l_r2), l_t3(l_r2t * l_r3);
    const Vector3 l_tHit(l_r2t * l_from1), l_proportional(l_tHit.x / l_t2.x, l_tHit.y / l_t3.y);
    a.m_surface = Vector3(m_p2m * l_proportional);
    return true;
}

bool Magic::Triangle::light(RenderVar &a)
{
    assert(m_material != nullptr);
    return m_material->light(a);
}

Magic::RGBf Magic::Triangle::lightRgbf(RenderVar &a)
{
    assert(m_material != nullptr);
    return m_material->lightRgbf(a);
}

void Magic::Triangle::genRay(RenderVar &a)
{
    assert(m_material != nullptr);
    m_material->genRay(a);
}

Magic::RGBf Magic::Triangle::fract(RenderVar &a)
{
    assert(m_material != nullptr);
    return m_material->fract(a);
}
