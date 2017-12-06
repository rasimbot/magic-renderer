#ifndef __MAGIC_RENDERER_RENDERER_H
#define __MAGIC_RENDERER_RENDERER_H

#include "argb.h"
#include <vector>
#include <list>
#include "object.h"
#include <random>
#include "material.h"

namespace Magic
{
    class Renderer
    {
    public:
        typedef std::vector<RGBf> Samples;

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
        void add(Material *a);

        void setRaysNumStrategy(const std::vector<size_t> &a);

        void doIt();

        size_t nowhere() const { return m_nowhere; }
        size_t success() const { return m_success; }
        size_t dropped() const { return m_dropped; }

        float randCam() { return m_randCam(m_randGenCam); }

        static ARGB spectrumToRGB(const RGBf &a);

    private:
        void calcBufToCam();
        RGBf ray(RenderVar &a);
        RGBf refl(RenderVar &a);
        RGBf camRay(const Vector3 &a);
        ARGB processPixel(const Vector3 &a);

        size_t m_bufWidth = 0, m_bufHeight = 0;
        ARGB *m_buf = nullptr;

        float m_camWidth = 0, m_camHeight = 0, m_camLength = 0;
        Matrix4 m_bufToCam, m_look;

        std::list<Object *> m_objects;
        std::list<Material *> m_materials;

        size_t m_recursion;
        std::vector<Samples> m_samples;
        size_t m_nowhere, m_success, m_dropped;

        std::random_device m_randDev;
        std::mt19937 m_randGenCam;
        std::uniform_real_distribution<float> m_randCam;
    };
}

#endif // __MAGIC_RENDERER_RENDERER_H
