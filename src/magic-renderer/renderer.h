#ifndef __MAGIC_RENDERER_RENDERER_H
#define __MAGIC_RENDERER_RENDERER_H

#include "argb.h"
#include "vector3.h"
#include "matrix4.h"
#include <vector>
#include <list>
#include "object.h"
#include <random>

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

        void add(Object *a);

        void setCameraRaysNum(size_t a);

        void doIt();

        static Matrix4 transf(const Vector3 &a_from, const Vector3 &a_to, const Vector3 &a_up);

        float randF() { return m_randF(m_randGen); }
        static ARGB spectrumToRGB(const RGBf &a);

    private:
        void calcBufToCam();
        RGBf ray(const Matrix4 &a_space, const RGBf &a_reflect);
        RGBf camRay(const Vector3 &a);
        ARGB processPixel(const Vector3 &a);

        size_t m_bufWidth = 0, m_bufHeight = 0;
        ARGB *m_buf = nullptr;

        float m_camWidth = 0, m_camHeight = 0, m_camLength = 0;
        Matrix4 m_bufToCam, m_look;

        std::list<Object *> m_objects;

        std::vector<RGBf> m_camSamples;

        std::random_device m_randDev;
        std::mt19937 m_randGen;
        std::uniform_real_distribution<float> m_randF;
    };
}

#endif // __MAGIC_RENDERER_RENDERER_H
