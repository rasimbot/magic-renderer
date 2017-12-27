#include "stdafx.h"
#include "object.h"
#include "func.h"

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

Magic::Matrix4 Magic::Object::proportionalToMaterial(const V2Triple &a_inMaterial)
{
    const Vector3 l_mV1(a_inMaterial[1] - a_inMaterial[0], 0);
    const Vector3 l_mFrom(a_inMaterial[0], 0);
    const Vector3 l_mTo(a_inMaterial[0], 1);
    const Vector3 l_mUp(cross(Vector3(0, 0, 1), l_mV1));
    const Matrix4 l_m2t(transf(l_mFrom, l_mTo, l_mUp));
    const Vector3 l_t2(l_m2t * Vector3(a_inMaterial[1], 0)), l_t3(l_m2t * Vector3(a_inMaterial[2], 0));
    const Vector3 l_up2(cross(Vector3(0, 0, 1), Vector3(l_mV1.x, -l_mV1.y)));
    const Matrix4 l_t2pm(transf(Vector3(), Vector3(0, 0, 1), l_up2));
    return translate(Vector3(a_inMaterial[0], 0)) * l_t2pm * scale(Vector3(l_t2.x, l_t3.y));
}
