#include "stdafx.h"
#include "object.h"

Magic::Object::~Object()
{}

bool Magic::Object::hit(ReflArg &a)
{
    return false;
}

bool Magic::Object::light()
{
    return false;
}

Magic::RGBf Magic::Object::rgbf()
{
    return RGBf();
}
