#include "stdafx.h"
#include "triangle.h"
#include "renderer.h"
#include "func.h"

Magic::Triangle::Triangle(const Vector3 &a_p1, const Vector3 &a_p2,
                          const Vector3 &a_p3, bool a_light, const RGBf &a_rgbf) :
    m_p1(a_p1), m_p2(a_p2), m_p3(a_p3), m_light(a_light), m_rgbf(a_rgbf)
{}

Magic::Triangle::~Triangle()
{}

bool Magic::Triangle::hit(const Matrix4 &a_ray, Matrix4 &a_normal) const
{
    const Vector3 l_rs1(a_ray * m_p1), l_rs2(a_ray * m_p2), l_rs3(a_ray * m_p3);
    if (!isPointInTriangle(Vector2(), l_rs1, l_rs2, l_rs3)) return false;
    const Vector3 l_n(cross(l_rs2 - l_rs1, l_rs3 - l_rs2));
    const float l_z = (l_n.x * l_rs2.x + l_n.y * l_rs2.y + l_n.z * l_rs2.z) / l_n.z;
    if (l_z < 0) return false;
    const Vector3 l_from(0, 0, l_z);
    const Vector3 l_to(l_from - l_n);
    const Vector3 l_up(perpendicular(-l_n));
    a_normal = Renderer::transf(l_from, l_to, l_up);
    return true;
}

bool Magic::Triangle::light() const
{
    return m_light;
}

Magic::RGBf Magic::Triangle::rgbf() const
{
    return m_rgbf;
}
