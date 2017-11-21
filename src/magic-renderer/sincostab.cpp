#include "stdafx.h"
#include "sincostab.h"
#include "defs.h"
#include <fstream>

Magic::SinCosTab::SinCosTab(size_t a_tabSize) :
    m_sin(a_tabSize), m_cos(a_tabSize)
{
    for (size_t i = 0; i < a_tabSize; i++)
    {
        const double l_a = 2 * i * s_piD / a_tabSize;
        m_sin[i] = float(std::sin(l_a));
        m_cos[i] = float(std::cos(l_a));
    }
}
