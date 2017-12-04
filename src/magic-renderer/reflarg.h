#ifndef __MAGIC_RENDERER_REFLARG_H
#define __MAGIC_RENDERER_REFLARG_H

#include "object.h"

namespace Magic
{
    struct ReflArg
    {
        Matrix4 m_space;
        RGBf m_reflect;
        Object *m_object = nullptr;
        Matrix4 m_normal;
        float m_depth = 0;
    };
}

#endif // __MAGIC_RENDERER_REFLARG_H
