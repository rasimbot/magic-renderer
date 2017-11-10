#include "stdafx.h"
#include "object.h"

Magic::Object::~Object()
{}

bool Magic::Object::hit(const Matrix4 &a_ray, Matrix4 &a_normal) const
{
    return false;
}

bool Magic::Object::light() const
{
    return false;
}

Magic::RGBf Magic::Object::rgbf() const
{
    return RGBf();
}
