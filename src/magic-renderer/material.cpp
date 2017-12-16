#include "stdafx.h"
#include "material.h"

Magic::Material::Material(Renderer *a_renderer)
{}

Magic::Material::~Material()
{}

bool Magic::Material::light(RenderVar &a)
{
    return false;
}

Magic::RGBf Magic::Material::lightRgbf(RenderVar &a)
{
    return RGBf();
}

void Magic::Material::genRay(RenderVar &a)
{}

Magic::RGBf Magic::Material::fract(RenderVar &a)
{
    return RGBf();
}
