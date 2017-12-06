#include "stdafx.h"
#include "triangle.h"
#include "renderer.h"
#include "func.h"
#include "sincostab.h"

Magic::Triangle::Triangle(const Vector3 &a_p1, const Vector3 &a_p2,
                          const Vector3 &a_p3, Material *a_material) :
    m_p1(a_p1), m_p2(a_p2), m_p3(a_p3), m_material(a_material)
{}

Magic::Triangle::~Triangle()
{}

bool Magic::Triangle::hit(RenderVar &a)
{
    const Vector3 l_rs1(a.m_space * m_p1), l_rs2(a.m_space * m_p2), l_rs3(a.m_space * m_p3);
    if (!isPointInTriangle(Vector2(), l_rs1, l_rs2, l_rs3)) return false;
    const Vector3 l_n(cross(l_rs2 - l_rs1, l_rs3 - l_rs2));
    const float l_z = (l_n.x * l_rs2.x + l_n.y * l_rs2.y + l_n.z * l_rs2.z) / l_n.z;
    if (l_z < 0) return false;
    const Vector3 l_from(0, 0, l_z);
    const Vector3 l_to(l_from - l_n);
    const Vector3 l_up(perpendicular(-l_n));
    a.m_normal = transf(l_from, l_to, l_up);
    a.m_depth = l_z;
    return true;
}

bool Magic::Triangle::light()
{
    assert(m_material != nullptr);
    return m_material->light();
}

Magic::RGBf Magic::Triangle::lightRgbf()
{
    assert(m_material != nullptr);
    return m_material->lightRgbf();
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
