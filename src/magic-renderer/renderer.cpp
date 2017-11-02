#include "stdafx.h"
#include "renderer.h"
#include "point.h"

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

void Magic::Renderer::setSize(float a_width, float a_height)
{
    m_width = a_width; m_height = a_height;
}

void Magic::Renderer::look(const Point &a_from, const Point &a_to, const Point &a_left)
{
}
