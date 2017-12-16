#include "stdafx.h"
#include "material1.h"

Magic::Material1::Material1(Renderer *a_renderer, const RGBf &a_rgbf) :
    Material(a_renderer), m_rgbf(a_rgbf)
{}

Magic::Material1::~Material1()
{}

bool Magic::Material1::light(RenderVar &a)
{
    return true;
}

Magic::RGBf Magic::Material1::lightRgbf(RenderVar &a)
{
    return m_rgbf;
}
