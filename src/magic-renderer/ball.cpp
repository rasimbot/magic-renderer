#include "stdafx.h"
#include "ball.h"

Magic::Ball::Ball(const Vector3 &a_p, float a_r, const ARGB &a_c) :
    m_p(a_p), m_r(a_r), m_c(a_c)
{}

Magic::Ball::~Ball()
{}

float Magic::Ball::hit(const Matrix4 &a_ray) const
{
    const Vector3 l_inRaySpace(a_ray * m_p);
    const float l_d = m_r * m_r -
        l_inRaySpace.x * l_inRaySpace.x - l_inRaySpace.y * l_inRaySpace.y;
    if (l_d < 0) return -1;
    const float l_sqrt = std::sqrt(l_d);
    const float l_z1 = l_inRaySpace.z + l_sqrt, l_z2 = l_inRaySpace.z - l_sqrt;
    if (l_z1 <= 0 && l_z2 <= 0) return -1;
    if (l_z1 < 0 && l_z2 > 0 || l_z1 > 0 && l_z2 < 0) return 0;
    return std::min(l_z1, l_z2);
}

Magic::ARGB Magic::Ball::color() const
{
    return m_c;
}
