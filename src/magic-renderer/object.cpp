#include "stdafx.h"
#include "object.h"

Magic::Object::Object(Renderer *a_renderer)
{}

Magic::Object::~Object()
{}

bool Magic::Object::hit(RenderVar &a)
{
    return false;
}

bool Magic::Object::light(RenderVar &a)
{
    return false;
}

Magic::RGBf Magic::Object::lightRgbf(RenderVar &a)
{
    return RGBf();
}

void Magic::Object::genRay(RenderVar &a)
{}

Magic::RGBf Magic::Object::fract(RenderVar &a)
{
    return RGBf();
}
