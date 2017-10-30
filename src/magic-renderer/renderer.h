#ifndef __MAGIC_RENDERER_RENDERER_H
#define __MAGIC_RENDERER_RENDERER_H

#include "rgb.h"

namespace Magic
{
    class Renderer
    {
    public:
        Renderer();
        ~Renderer();

        void setBufferSize(size_t a_bufWidth, size_t a_bufHeight);
        RGB *buf() const;

        Renderer(const Renderer &) = delete;
        Renderer &operator =(const Renderer &) = delete;

    private:
        size_t m_bufWidth = 0, m_bufHeight = 0;
        RGB *m_buf = nullptr;
    };
}

#endif // __MAGIC_RENDERER_RENDERER_H
