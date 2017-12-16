#include "stdafx.h"
#include "renderer.h"
#include "func.h"
#include "sincostab.h"
#include <future>

Magic::Renderer::Renderer() :
    m_vPtd(threadNumber(),
    { 0, decltype(PerThreadData::m_samples)(),
      decltype(PerThreadData::m_randGenCam)(),
      decltype(PerThreadData::m_randCam)(-0.5f, 0.5f) })
{
    std::random_device l_dev;
    for (auto &u : m_vPtd) u.m_randGenCam.seed(l_dev());
}

Magic::Renderer::~Renderer()
{
    for (auto &q : m_objects) delete q;
    for (auto &q : m_materials) delete q;
}

void Magic::Renderer::setBufferSize(size_t a_bufWidth, size_t a_bufHeight)
{
    delete[] m_buf; m_buf = nullptr;
    m_bufWidth = 0; m_bufHeight = 0;
    m_buf = new ARGB[a_bufWidth * a_bufHeight];
    m_bufWidth = a_bufWidth; m_bufHeight = a_bufHeight;
    calcBufToCam();
}

size_t Magic::Renderer::bufWidth() const
{
    return m_bufWidth;
}

size_t Magic::Renderer::bufHeight() const
{
    return m_bufHeight;
}

Magic::ARGB *Magic::Renderer::buf() const
{
    return m_buf;
}

void Magic::Renderer::setCameraSizes(float a_width, float a_height, float a_length)
{
    m_camWidth = a_width; m_camHeight = a_height; m_camLength = a_length;
    calcBufToCam();
}

Magic::Matrix4 Magic::Renderer::look(const Vector3 &a_from, const Vector3 &a_to, const Vector3 &a_up)
{
    return m_look = transf(a_from, a_to, a_up);
}

void Magic::Renderer::add(Object *a)
{
    assert(a != nullptr);
    m_objects.push_back(a);
}

void Magic::Renderer::add(Material *a)
{
    assert(a != nullptr);
    m_materials.push_back(a);
}

void Magic::Renderer::setRaysNumStrategy(const std::vector<size_t> &a)
{
    assert(threadNumber() <= m_vPtd.size());
    for (size_t q = 0; q < threadNumber(); q++)
    {
        PerThreadData &l_ptd = m_vPtd[q];
        l_ptd.m_samples.resize(a.size());
        for (size_t i = 0; i < l_ptd.m_samples.size(); i++) l_ptd.m_samples[i].resize(a[i]);
    }
}

void Magic::Renderer::doAsync(size_t a_threadIndex)
{
    assert(m_buf != nullptr);
    for (size_t q = a_threadIndex; q < m_bufWidth * m_bufHeight; q += threadNumber())
    {
        const size_t i = q / m_bufWidth, j = q % m_bufWidth;
        processPixel(a_threadIndex, Vector2{ float(j), float(i) }, m_buf[j + i * m_bufWidth]);
    }
}

void Magic::Renderer::doIt()
{
    assert(m_buf != nullptr);
    m_hit = m_misses = m_dropped = 0;
    std::vector<std::future<void>> l_res(threadNumber());
    for (size_t e = 0; e < threadNumber(); e++)
        l_res[e] = std::move(std::async(std::launch::async, &Renderer::doAsync, this, e));
}

Magic::ARGB Magic::Renderer::spectrumToRGB(const RGBf &a)
{
    return 255 * a;
}

void Magic::Renderer::calcBufToCam()
{
    m_bufToCam = Matrix4{ m_camWidth / m_bufWidth, 0, 0, m_camWidth / 2 * (1.0f / m_bufWidth - 1),
                          0, -m_camHeight / m_bufHeight, 0, -m_camHeight / 2 * (1.0f / m_bufHeight - 1),
                          0, 0, 1, 0,
                          0, 0, 0, 1 };
}

bool Magic::Renderer::ray(RenderVar &a)
{
    assert(a.m_ti < m_vPtd.size());
    for (auto &q : m_objects)
    {
        assert(q != nullptr);
        RenderVar l_var{ a.m_ti, a.m_space };
        if (!q->hit(l_var) || a.m_object != nullptr && a.m_depth < l_var.m_depth) continue;
        a.m_object = q; a.m_normal = l_var.m_normal;
        a.m_depth = l_var.m_depth; a.m_surface = l_var.m_surface;
    }

    if (a.m_object == nullptr) { m_misses++; return true; }
    if (a.m_object->light(a)) { a.m_spectrum = a.m_object->lightRgbf(a); m_hit++; return true; }

    PerThreadData &l_ptd = m_vPtd[a.m_ti];
    if (l_ptd.m_recursion + 1 >= l_ptd.m_samples.size()) { m_dropped++; return false; }

    const Vector3 l_back(a.m_normal * Vector3(0, 0, 2 * a.m_depth));
    const Vector3 l_face(l_back.x, l_back.y, -l_back.z);
    const float l_xypl = std::sqrt(l_face.x * l_face.x + l_face.y * l_face.y);
    const Vector3 l_vYZ(0, l_face.z, -l_xypl);
    const Matrix4 l_mYZ(rotateYZ(l_vYZ));
    const Vector3 l_vXY(l_face.y, -l_face.x, 0);
    const Matrix4 l_mXY(rotateXY(l_vXY));
    a.m_bounce = l_mXY * l_mYZ;

    l_ptd.m_recursion++;
    const bool r = refl(a);
    l_ptd.m_recursion--;
    return r;
}

bool Magic::Renderer::refl(RenderVar &a)
{
    assert(a.m_object != nullptr);
    assert(a.m_ti < m_vPtd.size());
    PerThreadData &l_ptd = m_vPtd[a.m_ti];
    assert(l_ptd.m_recursion < l_ptd.m_samples.size());
    Samples &l_reflSamples = l_ptd.m_samples[l_ptd.m_recursion];

    const Matrix4 l_normalInSpace(a.m_normal * a.m_space);

    size_t g = 0;
    for (size_t q = 0; q < l_reflSamples.size(); q++)
    {
        a.m_object->genRay(a);
        if (a.m_genRay.z < 0) continue;
        const RGBf l_fract(a.m_object->fract(a));

        const Vector3 l_to(a.m_genRay);
        const Vector3 l_up(perpendicular(l_to));
        const Matrix4 l_refl(transf(Vector3(), l_to, l_up));

        RenderVar l_renderVar{ a.m_ti, l_refl * l_normalInSpace };
        if (ray(l_renderVar)) l_reflSamples[g++] = l_fract * l_renderVar.m_spectrum;
    }

    if (g < 1) return false;

    const auto l_sum(std::accumulate(l_reflSamples.begin(), l_reflSamples.begin() + g, RGBf()));
    a.m_spectrum = l_sum / float(g);
    return true;
}

bool Magic::Renderer::camRay(size_t a_threadIndex, const Vector3 &a_dir, RGBf &a_spectrum)
{
    assert(a_threadIndex < m_vPtd.size());
    const Vector3 l_from;
    const Vector3 l_to(a_dir.x, a_dir.y, m_camLength);
    const Vector3 l_up(perpendicular(l_to));
    const Matrix4 l_camRay(transf(l_from, l_to, l_up));
    PerThreadData &l_ptd = m_vPtd[a_threadIndex];
    l_ptd.m_recursion = 0;
    RenderVar l_renderVar{ a_threadIndex, l_camRay * m_look };
    if (!ray(l_renderVar)) return false;
    a_spectrum = l_renderVar.m_spectrum;
    return true;
}

bool Magic::Renderer::processPixel(size_t a_threadIndex, const Vector3 &a_dir, ARGB &a_color)
{
    assert(a_threadIndex < m_vPtd.size());
    PerThreadData &l_ptd = m_vPtd[a_threadIndex];
    assert(l_ptd.m_samples.size() > 0);
    Samples &l_pixSamples = l_ptd.m_samples[0];

    size_t g = 0;
    for (size_t q = 0; q < l_pixSamples.size(); q++)
    {
        const Vector4 l_shifted(a_dir.x + l_ptd.randCam(), a_dir.y + l_ptd.randCam());
        if (camRay(a_threadIndex, m_bufToCam * l_shifted, l_pixSamples[g])) g++;
    }

    if (g < 1) return false;

    const auto l_sum = std::accumulate(l_pixSamples.begin(), l_pixSamples.begin() + g, RGBf());
    a_color = spectrumToRGB(l_sum / float(g));
    return true;
}
