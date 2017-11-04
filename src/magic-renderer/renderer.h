#ifndef __MAGIC_RENDERER_RENDERER_H
#define __MAGIC_RENDERER_RENDERER_H

#include "rgb.h"
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

        Matrix look(const Vector3 &a_from, const Vector3 &a_to, const Vector3 &a_up);

    private:
        size_t m_bufWidth = 0, m_bufHeight = 0;
        RGB *m_buf = nullptr;

        Matrix m_look;
    };
}

#endif // __MAGIC_RENDERER_RENDERER_H
