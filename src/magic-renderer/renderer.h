#ifndef __MAGIC_RENDERER_RENDERER_H
#define __MAGIC_RENDERER_RENDERER_H

#include "rgb.h"
#include "point.h"
#include "matrix.h"

namespace Magic
{
    class Renderer
    {
    public:
        Renderer();
        ~Renderer();

        Renderer(const Renderer &) = delete;
        Renderer &operator =(const Renderer &) = delete;

        void setBufferSize(size_t a_bufWidth, size_t a_bufHeight);
        RGB *buf() const;

        void setSize(float a_width, float a_height);
        void look(const Point &a_from, const Point &a_to, const Point &a_left);

    private:
        size_t m_bufWidth = 0, m_bufHeight = 0;
        RGB *m_buf = nullptr;

        float m_width = 0, m_height = 0;
        Matrix m_look;
    };
}

#endif // __MAGIC_RENDERER_RENDERER_H
