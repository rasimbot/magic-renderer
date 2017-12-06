#include "stdafx.h"
#include "triangle.h"
#include "renderer.h"
#include "func.h"
#include "sincostab.h"

Magic::Triangle::Triangle(const Vector3 &a_p1, const Vector3 &a_p2,
                          const Vector3 &a_p3, bool a_light, const RGBf &a_rgbf) :
    m_p1(a_p1), m_p2(a_p2), m_p3(a_p3), m_light(a_light), m_rgbf(a_rgbf)
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
    return m_light;
}

Magic::RGBf Magic::Triangle::lightRgbf()
{
    return m_rgbf;
}

void Magic::Triangle::genRay(RenderVar &a)
{
    const size_t l_a = a.m_renderer->randRefl1(), l_b = a.m_renderer->randRefl2();
    const SinCosTab &l_sct(SinCosTab::staticInstance());
    a.m_genRay = Vector3(l_sct.cos(l_a) * l_sct.sin(l_b),
                         l_sct.cos(l_a) * l_sct.cos(l_b), l_sct.sin(l_a));
}

Magic::RGBf Magic::Triangle::fract(RenderVar &a)
{
    return m_rgbf;
}
