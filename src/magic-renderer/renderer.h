#ifndef __MAGIC_RENDERER_RENDERER_H
#define __MAGIC_RENDERER_RENDERER_H

#include "argb.h"
#include "vector3.h"
#include "matrix4.h"
#include <vector>
#include <list>
#include "object.h"
#include <random>
#include "sincostab.h"

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
        void setReflRaysNum(size_t a);

        void doIt();

        static Matrix4 transf(const Vector3 &a_from, const Vector3 &a_to, const Vector3 &a_up);

        float randCam() { return m_randCam(m_randGenCam); }
        size_t randRefl1() { return m_randRefl1(m_randGenRefl1); }
        size_t randRefl2() { return m_randRefl2(m_randGenRefl2); }

        static ARGB spectrumToRGB(const RGBf &a);

    private:
        void calcBufToCam();
        RGBf ray(const Matrix4 &a_space, const RGBf &a_reflect);
        RGBf refl(const Matrix4 &a_space, const RGBf &a_reflect);
        RGBf camRay(const Vector3 &a);
        ARGB processPixel(const Vector3 &a);

        size_t m_bufWidth = 0, m_bufHeight = 0;
        ARGB *m_buf = nullptr;

        float m_camWidth = 0, m_camHeight = 0, m_camLength = 0;
        Matrix4 m_bufToCam, m_look;

        std::list<Object *> m_objects;

        std::vector<RGBf> m_camSamples, m_reflSamples;

        SinCosTab m_sct;

        std::random_device m_randDev;
        std::mt19937 m_randGenCam, m_randGenRefl1, m_randGenRefl2;
        std::uniform_real_distribution<float> m_randCam;
        std::uniform_int_distribution<size_t> m_randRefl1, m_randRefl2;

        size_t m_recursion;
    };
}

#endif // __MAGIC_RENDERER_RENDERER_H
