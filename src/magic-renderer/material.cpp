#include "stdafx.h"
#include "material.h"

Magic::Material::Material()
{}

Magic::Material::~Material()
{}

bool Magic::Material::light()
{
    return false;
}

Magic::RGBf Magic::Material::lightRgbf()
{
    return RGBf();
}

void Magic::Material::genRay(RenderVar &a)
{}

Magic::RGBf Magic::Material::fract(RenderVar &a)
{
    return RGBf();
}
