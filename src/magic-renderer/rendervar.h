#ifndef __MAGIC_RENDERER_REFLARG_H
#define __MAGIC_RENDERER_REFLARG_H

namespace Magic
{
    class Object;
    class Renderer;

    struct RenderVar
    {
        Renderer *m_renderer = nullptr;
        Matrix4 m_space;
        RGBf m_fractAcc;
        Object *m_object = nullptr;
        Matrix4 m_normal;
        float m_depth = 0;
        Matrix4 m_bounce;
        Vector3 m_genRay;
    };
}

#endif // __MAGIC_RENDERER_REFLARG_H
