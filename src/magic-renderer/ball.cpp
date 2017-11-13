#include "stdafx.h"
#include "ball.h"
#include "renderer.h"

Magic::Ball::Ball(const Vector3 &a_p, float a_r, bool a_light, const RGBf &a_rgbf) :
    m_p(a_p), m_r(a_r), m_light(a_light), m_rgbf(a_rgbf)
{}

Magic::Ball::~Ball()
{}

bool Magic::Ball::hit(const Matrix4 &a_ray, Matrix4 &a_normal) const
{
    const Vector3 l_inRaySpace(a_ray * m_p);
    const float l_d = m_r * m_r -
        l_inRaySpace.x * l_inRaySpace.x - l_inRaySpace.y * l_inRaySpace.y;
    if (l_d < 0) return false;
    const float l_sqrt = std::sqrt(l_d);
    const float l_z1 = l_inRaySpace.z + l_sqrt, l_z2 = l_inRaySpace.z - l_sqrt;
    if (l_z1 < 0 || l_z2 < 0) return false;
    const Vector3 l_from(0, 0, std::min(l_z1, l_z2));
    const Vector3 l_zDir(l_from - l_inRaySpace);
    const Vector3 l_to(l_from + l_zDir);
    const Vector3 l_up(perpendicular(l_zDir));
    a_normal = Renderer::transf(l_from, l_to, l_up);
    return true;
}

bool Magic::Ball::light() const
{
    return m_light;
}

Magic::RGBf Magic::Ball::rgbf() const
{
    return m_rgbf;
}
