#include "stdafx.h"
#include "renderer.h"
#include "func.h"

Magic::Renderer::Renderer()
{}

Magic::Renderer::~Renderer()
{
    for (auto &q : m_objects) delete q;
}

void Magic::Renderer::setBufferSize(size_t a_bufWidth, size_t a_bufHeight)
{
    delete[] m_buf; m_buf = nullptr;
    m_bufWidth = 0; m_bufHeight = 0;
    m_buf = new ARGB[a_bufWidth * a_bufHeight];
    m_bufWidth = a_bufWidth; m_bufHeight = a_bufHeight;
    calcBufToCam();
}

size_t Magic::Renderer::bufWidth() const
{
    return m_bufWidth;
}

size_t Magic::Renderer::bufHeight() const
{
    return m_bufHeight;
}

Magic::ARGB *Magic::Renderer::buf() const
{
    return m_buf;
}

void Magic::Renderer::setCameraSizes(float a_width, float a_height, float a_length)
{
    m_camWidth = a_width; m_camHeight = a_height; m_camLength = a_length;
    calcBufToCam();
}

Magic::Matrix4 Magic::Renderer::look(const Vector3 &a_from, const Vector3 &a_to, const Vector3 &a_up)
{
    return m_look = transf(a_from, a_to, a_up);
}

void Magic::Renderer::add(Object *a)
{
    assert(a != nullptr);
    m_objects.push_back(a);
}

void Magic::Renderer::doIt()
{
    assert(m_buf != nullptr);
    for (size_t i = 0; i < m_bufHeight; i++)
        for (size_t j = 0; j < m_bufWidth; j++)
            m_buf[j + i * m_bufWidth] = processPixel(m_bufToCam * Vector4{ float(j), float(i) });
}

Magic::Matrix4 Magic::Renderer::transf(const Vector3 &a_from, const Vector3 &a_to, const Vector3 &a_up)
{
    //https://msdn.microsoft.com/ru-ru/library/windows/desktop/bb205342(v=vs.85).aspx
    const Vector3 l_za(normalized(a_to - a_from));
    const Vector3 l_xa(normalized(cross(a_up, l_za)));
    const Vector3 l_ya(cross(l_za, l_xa));
    return Matrix4{ l_xa.x, l_xa.y, l_xa.z, -dot(l_xa, a_from),
                    l_ya.x, l_ya.y, l_ya.z, -dot(l_ya, a_from),
                    l_za.x, l_za.y, l_za.z, -dot(l_za, a_from),
                    0, 0, 0, 1 };
}

void Magic::Renderer::calcBufToCam()
{
    m_bufToCam = Matrix4{ m_camWidth / m_bufWidth, 0, 0, m_camWidth / 2 * (1.0f / m_bufWidth - 1),
                          0, -m_camHeight / m_bufHeight, 0, -m_camHeight / 2 * (1.0f / m_bufHeight - 1),
                          0, 0, 1, 0,
                          0, 0, 0, 1 };
}

Magic::RGBf Magic::Renderer::ray(const Matrix4 &a_space, const RGBf &a_reflect)
{
    Object *l_o = nullptr;
    Matrix4 l_n1;
    for (auto &q : m_objects)
    {
        assert(q != nullptr);
        Matrix4 l_n2;
        if (!q->hit(a_space, l_n2) || l_o != nullptr && l_n1.m34 < l_n2.m34) continue;
        l_o = q;
        l_n1 = l_n2;
    }
    if (l_o == nullptr) return RGBf();
    if (l_o->light()) return a_reflect * l_o->rgbf();
    return ray(l_n1 * a_space, a_reflect * l_o->rgbf());
}

Magic::ARGB Magic::Renderer::processPixel(const Vector4 &a)
{
    const Vector3 l_from;
    const Vector3 l_to(a.x, a.y, m_camLength);
    const Vector3 l_up(perpendicular(l_to));
    const Matrix4 l_camRay(transf(l_from, l_to, l_up));
    auto l_rgbf(ray(l_camRay * m_look, RGBf{ 1, 1, 1 }));
    return ARGB{ unsigned char(std::nearbyint(255 * l_rgbf.b)),
                 unsigned char(std::nearbyint(255 * l_rgbf.g)),
                 unsigned char(std::nearbyint(255 * l_rgbf.r)) };
}
