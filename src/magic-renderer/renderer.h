#ifndef __MAGIC_RENDERER_RENDERER_H
#define __MAGIC_RENDERER_RENDERER_H

#include "argb.h"
#include "vector3.h"
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
        size_t bufWidth() const;
        size_t bufHeight() const;
        ARGB *buf() const;

        void setCameraSizes(float a_width, float a_height, float a_length);
        Matrix4 look(const Vector3 &a_from, const Vector3 &a_to, const Vector3 &a_up);

        void doIt();

        static Matrix4 transf(const Vector3 &a_from, const Vector3 &a_to, const Vector3 &a_up);

    private:
        void calcBufToCam();
        ARGB processPixel(const Vector4 &a);

        size_t m_bufWidth = 0, m_bufHeight = 0;
        ARGB *m_buf = nullptr;

        float m_camWidth = 0, m_camHeight = 0, m_camLength = 0;
        Matrix4 m_bufToCam, m_look;
    };
}

#endif // __MAGIC_RENDERER_RENDERER_H
