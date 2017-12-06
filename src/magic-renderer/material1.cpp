#include "stdafx.h"
#include "material1.h"

Magic::Material1::Material1(const RGBf &a_rgbf) :
    m_rgbf(a_rgbf)
{}

Magic::Material1::~Material1()
{}

bool Magic::Material1::light()
{
    return true;
}

Magic::RGBf Magic::Material1::lightRgbf()
{
    return m_rgbf;
}
