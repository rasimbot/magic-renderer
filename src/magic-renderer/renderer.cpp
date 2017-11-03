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

void Magic::Renderer::look(const Vector3 &a_from, const Vector3 &a_to, const Vector3 &a_up)
{}
