#ifndef __MAGIC_RENDERER_RENDERER_H
#define __MAGIC_RENDERER_RENDERER_H

#include "argb.h"
#include <vector>
#include <list>
#include "object.h"
#include <vector>
#include <random>
#include "material.h"
#include <atomic>

namespace Magic
{
    class Renderer
    {
    public:
        typedef std::vector<RGBf> Samples;

    private:
        struct PerThreadData
        {
            size_t m_recursion;
            std::vector<Samples> m_samples;

            std::mt19937 m_randGenCam;
            std::uniform_real_distribution<float> m_randCam;

            float randCam() { return m_randCam(m_randGenCam); }
        };

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

        constexpr size_t threadNumber() const { return 4; }

        void add(Object *a);
        void add(Material *a);

        void setRaysNumStrategy(const std::vector<size_t> &a);

        void doAsync(size_t a_threadIndex);
        void doIt();

        size_t hit() const { return m_hit; }
        size_t misses() const { return m_misses; }
        size_t dropped() const { return m_dropped; }

        static ARGB spectrumToRGB(const RGBf &a);

    private:
        void calcBufToCam();
        bool ray(RenderVar &a);
        bool refl(RenderVar &a);
        bool camRay(size_t a_threadIndex, const Vector3 &a_dir, RGBf &a_spectrum);
        bool processPixel(size_t a_threadIndex, const Vector3 &a_dir, ARGB &a_color);

        size_t m_bufWidth = 0, m_bufHeight = 0;
        ARGB *m_buf = nullptr;

        float m_camWidth = 0, m_camHeight = 0, m_camLength = 0;
        Matrix4 m_bufToCam, m_look;

        std::list<Object *> m_objects;
        std::list<Material *> m_materials;

        std::atomic<size_t> m_hit, m_misses, m_dropped;
        std::vector<PerThreadData> m_vPtd;
    };
}

#endif // __MAGIC_RENDERER_RENDERER_H
