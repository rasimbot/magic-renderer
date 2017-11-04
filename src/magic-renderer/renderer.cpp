#include "stdafx.h"
#include "renderer.h"

Magic::Renderer::Renderer()
{}

Magic::Renderer::~Renderer()
{}

void Magic::Renderer::setBufferSize(size_t a_bufWidth, size_t a_bufHeight)
{
    delete[] m_buf; m_buf = nullptr;
    m_bufWidth = 0; m_bufHeight = 0;
    m_buf = new RGB[a_bufWidth * a_bufHeight];
    m_bufWidth = a_bufWidth; m_bufHeight = a_bufHeight;
}

Magic::RGB *Magic::Renderer::buf() const
{
    return m_buf;
}

Magic::Matrix Magic::Renderer::look(const Vector3 &a_from, const Vector3 &a_to, const Vector3 &a_up)
{
    //https://msdn.microsoft.com/ru-ru/library/windows/desktop/bb205342(v=vs.85).aspx
    const Vector3 l_za(normalized(a_to - a_from));
    const Vector3 l_xa(normalized(cross(a_up, l_za)));
    const Vector3 l_ya(cross(l_za, l_xa));
    m_look = Matrix{ l_xa.x, l_xa.y, l_xa.z, -dot(l_xa, a_from),
                     l_ya.x, l_ya.y, l_ya.z, -dot(l_ya, a_from),
                     l_za.x, l_za.y, l_za.z, -dot(l_za, a_from),
                     0, 0, 0, 1 };
    return m_look;
}
