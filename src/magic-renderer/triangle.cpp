#include "stdafx.h"
#include "triangle.h"

Magic::Triangle::Triangle(const Vector3 &a_p1, const Vector3 &a_p2,
                          const Vector3 &a_p3, bool a_light, const RGBf &a_rgbf) :
    m_p1(a_p1), m_p2(a_p2), m_p3(a_p3), m_light(a_light), m_rgbf(a_rgbf)
{}

Magic::Triangle::~Triangle()
{}

bool Magic::Triangle::hit(const Matrix4 &a_ray, Matrix4 &a_normal) const
{
    return false;
}

bool Magic::Triangle::light() const
{
    return m_light;
}

Magic::RGBf Magic::Triangle::rgbf() const
{
    return m_rgbf;
}
