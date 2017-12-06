#ifndef __MAGIC_RENDERER_SINCOSTAB_H
#define __MAGIC_RENDERER_SINCOSTAB_H

#include <cassert>
#include <vector>

namespace Magic
{
    struct SinCosTab
    {
        SinCosTab(size_t a_tabSize);

        float sin(size_t a_index) const
        {
            assert(m_sin.size() == m_cos.size());
            return m_sin[a_index % m_sin.size()];
        }

        float cos(size_t a_index) const
        {
            assert(m_sin.size() == m_cos.size());
            return m_cos[a_index % m_sin.size()];
        }

        size_t size() const { assert(m_sin.size() == m_cos.size()); return m_sin.size(); }

        std::vector<float> m_sin, m_cos;

        static SinCosTab &staticInstance();
    };
}

#endif // __MAGIC_RENDERER_SINCOSTAB_H
