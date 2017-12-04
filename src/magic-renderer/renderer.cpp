#include "stdafx.h"
#include "renderer.h"
#include "func.h"

Magic::Renderer::Renderer() :
    m_sct(4 * 2048),
    m_randGenCam(m_randDev()), m_randGenRefl1(m_randDev()), m_randGenRefl2(m_randDev()),
    m_randCam(-0.5f, 0.5f), m_randRefl1(0, m_sct.size() / 4), m_randRefl2(0, m_sct.size())
{}

Magic::Renderer::~Renderer()
{
    for (auto &q : m_objects) delete q;
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

void Magic::Renderer::setRaysNumStrategy(const std::vector<size_t> &a)
{
    m_samples.resize(a.size());
    for (size_t i = 0; i < m_samples.size(); i++) m_samples[i].resize(a[i]);
}

void Magic::Renderer::doIt()
{
    assert(m_buf != nullptr);
    m_nowhere = m_success = m_dropped = 0;
    for (size_t i = 0; i < m_bufHeight; i++)
        for (size_t j = 0; j < m_bufWidth; j++)
            m_buf[j + i * m_bufWidth] = processPixel(Vector2{ float(j), float(i) });
}

Magic::Matrix4 Magic::Renderer::transf(const Vector3 &a_from, const Vector3 &a_to, const Vector3 &a_up)
{
    //https://msdn.microsoft.com/ru-ru/library/windows/desktop/bb205342(v=vs.85).aspx
    const Vector3 l_za(normalized(a_to - a_from));
    const Vector3 l_xa(normalized(cross(a_up, l_za)));
    const Vector3 l_ya(cross(l_za, l_xa));
    return Matrix4{ l_xa.x, l_xa.y, l_xa.z, -dot(l_xa, a_from),
                    l_ya.x, l_ya.y, l_ya.z, -dot(l_ya, a_from),
                    l_za.x, l_za.y, l_za.z, -dot(l_za, a_from),
                    0, 0, 0, 1 };
}

Magic::ARGB Magic::Renderer::spectrumToRGB(const RGBf &a)
{
    return 250 * a;
}

void Magic::Renderer::calcBufToCam()
{
    m_bufToCam = Matrix4{ m_camWidth / m_bufWidth, 0, 0, m_camWidth / 2 * (1.0f / m_bufWidth - 1),
                          0, -m_camHeight / m_bufHeight, 0, -m_camHeight / 2 * (1.0f / m_bufHeight - 1),
                          0, 0, 1, 0,
                          0, 0, 0, 1 };
}

Magic::RGBf Magic::Renderer::ray(const Matrix4 &a_space, const RGBf &a_reflect)
{
    ReflArg l_reflArg{ a_space, a_reflect };
    for (auto &q : m_objects)
    {
        assert(q != nullptr);
        Matrix4 l_normal;
        float l_depth = 0;
        if (!q->hit(a_space, l_normal, l_depth) ||
            l_reflArg.m_object != nullptr && l_reflArg.m_depth < l_depth) continue;
        l_reflArg.m_object = q; l_reflArg.m_normal = l_normal; l_reflArg.m_depth = l_depth;
    }
    if (l_reflArg.m_object == nullptr) { m_nowhere++; return RGBf(); }
    if (l_reflArg.m_object->light()) { m_success++; return a_reflect * l_reflArg.m_object->rgbf(); }
    m_recursion++;
    if (m_recursion >= m_samples.size()) { m_dropped++; m_recursion--; return RGBf(); }
    const RGBf l_refl = refl(l_reflArg);
    m_recursion--;
    return l_refl;
}

Magic::RGBf Magic::Renderer::refl(const ReflArg &a)
{
    assert(a.m_object != nullptr);
    assert(m_recursion < m_samples.size());
    Samples &l_reflSamples = m_samples[m_recursion];
    const Matrix4 l_space(a.m_normal * a.m_space);
    const RGBf l_reflect(a.m_reflect * a.m_object->rgbf());
    for (size_t q = 0; q < l_reflSamples.size(); q++)
    {
        const Vector3 l_from;
        const size_t l_a = randRefl1(), l_b = randRefl2();
        const Vector3 l_to(m_sct.cos(l_a) * m_sct.sin(l_b),
                           m_sct.cos(l_a) * m_sct.cos(l_b), m_sct.sin(l_a));
        const Vector3 l_up(perpendicular(l_to));
        const Matrix4 l_refl(transf(l_from, l_to, l_up));
        l_reflSamples[q] = ray(l_refl * l_space, l_reflect);
    }
    const auto l_sum(std::accumulate(l_reflSamples.begin(), l_reflSamples.end(), RGBf()));
    return l_sum / float(l_reflSamples.size());
}

Magic::RGBf Magic::Renderer::camRay(const Vector3 &a)
{
    const Vector3 l_from;
    const Vector3 l_to(a.x, a.y, m_camLength);
    const Vector3 l_up(perpendicular(l_to));
    const Matrix4 l_camRay(transf(l_from, l_to, l_up));
    m_recursion = 0;
    return ray(l_camRay * m_look, RGBf{ 1, 1, 1 });
}

Magic::ARGB Magic::Renderer::processPixel(const Vector3 &a)
{
    assert(m_samples.size() > 0);
    Samples &l_pixSamples = m_samples[0];
    for (size_t q = 0; q < l_pixSamples.size(); q++)
    {
        const Vector4 l_shifted(a.x + randCam(), a.y + randCam());
        l_pixSamples[q] = camRay(m_bufToCam * l_shifted);
    }
    const auto l_sum = std::accumulate(l_pixSamples.begin(), l_pixSamples.end(), RGBf());
    return spectrumToRGB(l_sum / float(l_pixSamples.size()));
}
