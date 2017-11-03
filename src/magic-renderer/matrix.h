#ifndef __MAGIC_RENDERER_MATRIX_H
#define __MAGIC_RENDERER_MATRIX_H

#include "vector4.h"

namespace Magic
{
    struct Matrix
    {
        float m11 = 1, m12 = 0, m13 = 0, m14 = 0,
              m21 = 0, m22 = 1, m23 = 0, m24 = 0,
              m31 = 0, m32 = 0, m33 = 1, m34 = 0,
              m41 = 0, m42 = 0, m43 = 0, m44 = 1;
    };

    inline Matrix operator *(const Matrix &o, const Matrix &a)
    {
        return Matrix{ o.m11 * a.m11 + o.m12 * a.m21 + o.m13 * a.m31 + o.m14 * a.m41,
                       o.m11 * a.m12 + o.m12 * a.m22 + o.m13 * a.m32 + o.m14 * a.m42,
                       o.m11 * a.m13 + o.m12 * a.m23 + o.m13 * a.m33 + o.m14 * a.m43,
                       o.m11 * a.m14 + o.m12 * a.m24 + o.m13 * a.m34 + o.m14 * a.m44,
                       o.m21 * a.m11 + o.m22 * a.m21 + o.m23 * a.m31 + o.m24 * a.m41,
                       o.m21 * a.m12 + o.m22 * a.m22 + o.m23 * a.m32 + o.m24 * a.m42,
                       o.m21 * a.m13 + o.m22 * a.m23 + o.m23 * a.m33 + o.m24 * a.m43,
                       o.m21 * a.m14 + o.m22 * a.m24 + o.m23 * a.m34 + o.m24 * a.m44,
                       o.m31 * a.m11 + o.m32 * a.m21 + o.m33 * a.m31 + o.m34 * a.m41,
                       o.m31 * a.m12 + o.m32 * a.m22 + o.m33 * a.m32 + o.m34 * a.m42,
                       o.m31 * a.m13 + o.m32 * a.m23 + o.m33 * a.m33 + o.m34 * a.m43,
                       o.m31 * a.m14 + o.m32 * a.m24 + o.m33 * a.m34 + o.m34 * a.m44,
                       o.m41 * a.m11 + o.m42 * a.m21 + o.m43 * a.m31 + o.m44 * a.m41,
                       o.m41 * a.m12 + o.m42 * a.m22 + o.m43 * a.m32 + o.m44 * a.m42,
                       o.m41 * a.m13 + o.m42 * a.m23 + o.m43 * a.m33 + o.m44 * a.m43,
                       o.m41 * a.m14 + o.m42 * a.m24 + o.m43 * a.m34 + o.m44 * a.m44 };
    }

    inline Vector4 operator *(const Vector4 &o, const Matrix &a)
    {
        return Vector4{ o.x * a.m11 + o.y * a.m12 + o.z * a.m13 + o.w * a.m14,
                        o.x * a.m21 + o.y * a.m22 + o.z * a.m23 + o.w * a.m24,
                        o.x * a.m31 + o.y * a.m32 + o.z * a.m33 + o.w * a.m34,
                        o.x * a.m41 + o.y * a.m42 + o.z * a.m43 + o.w * a.m44 };
    }
}

#endif // __MAGIC_RENDERER_MATRIX_H
