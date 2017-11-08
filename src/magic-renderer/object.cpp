#include "stdafx.h"
#include "object.h"

Magic::Object::~Object()
{}

float Magic::Object::hit(const Matrix4 &a_ray) const
{
    return false;
}

Magic::ARGB Magic::Object::color() const
{
    return ARGB();
}
