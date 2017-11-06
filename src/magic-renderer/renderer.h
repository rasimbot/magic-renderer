#ifndef __MAGIC_RENDERER_RENDERER_H
#define __MAGIC_RENDERER_RENDERER_H

#include "rgb.h"
#include "matrix4.h"

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

        void setCameraSizes(float a_width, float a_height, float a_length);
        Matrix4 look(const Vector3 &a_from, const Vector3 &a_to, const Vector3 &a_up);

        void doIt();

        static Matrix4 transf(const Vector3 &a_from, const Vector3 &a_to, const Vector3 &a_up);

    private:
        size_t m_bufWidth = 0, m_bufHeight = 0;
        RGB *m_buf = nullptr;

        float m_width = 0, m_height = 0, m_length = 0;
        Matrix4 m_look;
    };
}

#endif // __MAGIC_RENDERER_RENDERER_H
