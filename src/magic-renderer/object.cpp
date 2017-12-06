#include "stdafx.h"
#include "object.h"

Magic::Object::~Object()
{}

bool Magic::Object::hit(RenderVar &a)
{
    return false;
}

bool Magic::Object::light()
{
    return false;
}

Magic::RGBf Magic::Object::lightRgbf()
{
    return RGBf();
}

void Magic::Object::genRay(RenderVar &a)
{}

Magic::RGBf Magic::Object::fract(RenderVar &a)
{
    return RGBf();
}
