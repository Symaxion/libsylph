/*
 * LibSylph Class Library
 * Copyright (C) 2012 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not
 *   claim that you wrote the original software. If you use this software
 *   in a product, an acknowledgment in the product documentation would be
 *   appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not be
 *   misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any source
 *   distribution.
 *
 */

#ifndef SYLPH_MATH_VECTOR_H_
#define SYLPH_MATH_VECTOR_H_

#include "internal_base.h"
#include "Angle.h"
#include "TrigFunctions.h"

SYLPH_BEGIN_MATHNS
    template<class Number>
    class Vector2 {
    public:
        static Vector2<Number> zero;
        static Vector2<Number> unitX;
        static Vector2<Number> unitY;
        static Vector2<Number> unitXY;
    public:
        Vector2() : x(0), y(0) {}
        Vector2(Number _x, Number _y) : x(_x), y(_y) {}

        auto mag() const -> decltype(sqrt(Number(0))) {
            return std::sqrt(magSq());
        }

        Number magSq() const {
            return x*x + y*y;
        }

        Vector2<Number> normalize() const {
            Vector2<Number> toReturn;
            toReturn.x = x*x/magSq();
            toReturn.y = y*y/magSq();
            return toReturn;
        }

        bool multipleOf(const Vector2& v2) const {
            return x*v2.y == y * v2.x;
        }

        bool isUnitVector() const {
            return magSq() == 1.0f;
        }

        Vector2<Number> operator-() const {
            Vector2<Number> toReturn;
            toReturn.x = -x;
            toReturn.y = -y;
            return toReturn;
        }

    public:
        Number x, y;
    };

    template<class Number>
    auto mag(const Vector2<Number>& v) -> decltype(v.mag()) {
        return v.mag();
    }

    template<class Number>
    Number magSq(const Vector2<Number>& v) {
        return v.magSq();
    }

    template<class Number>
    auto dist(const Vector2<Number>& v1, const Vector2<Number>& v2) -> 
            decltype((v2-v1).mag()) {
        return (v2-v1).mag();
    }

    template<class Number>
    Number distSq(const Vector2<Number>& v1, const Vector2<Number>& v2) {
        return (v2-v1).magSq();
    }

    template<class Number>
    Vector2<Number>& operator+=(Vector2<Number>& v1, const Vector2<Number>& v2) {
        v1.x += v2.x;
        v1.y += v2.y;
        return v1;
    }

    template<class Number>
    Vector2<Number> operator+(const Vector2<Number>& v1,
            const Vector2<Number>& v2) {
        return Vector2<Number>(v1) += v2;
    }

    template<class Number>
    Vector2<Number>& operator-=(Vector2<Number>& v1, const Vector2<Number>& v2) {
        v1.x -= v2.x;
        v1.y -= v2.y;
        return v1;
    }

    template<class Number>
    Vector2<Number> operator-(const Vector2<Number>& v1,
            const Vector2<Number>& v2) {
        return Vector2<Number>(v1) -= v2;
    }

    template<class Number>
    Number operator*(const Vector2<Number>& v1, const Vector2<Number>& v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    template<class Number>
    Vector2<Number>& operator*=(Vector2<Number>& v, Number n) {
        v.x *= n; v.y *= n;
        return v;
    }

    template<class Number>
    Vector2<Number> operator*(const Vector2<Number>& v, Number n) {
        return Vector2<Number>(v) *= n;
    }

    template<class Number>
    Vector2<Number> operator*(Number n, const Vector2<Number>& v) {
        return Vector2<Number>(v) *= n;
    }

    template<class Number>
    Vector2<Number>& operator/=(Vector2<Number>& v, Number n) {
        v.x /= n; v.y /= n;
        return v;
    }

    template<class Number>
    Vector2<Number> operator/(const Vector2<Number>& v, Number n) {
        return Vector2<Number>(v) /= n;
    }
    template<class Number>
    Number operator^(const Vector2<Number>& v1, const Vector2<Number>& v2) {
        return std::acos((v1*v2)/(norm(v1)*norm(v2)));
    }

    template<class Number>
    class Vector3 {
    public:
        Vector3() : x(0), y(0) {}
        Vector3(Number _x, Number _y, Number _z) : x(_x), y(_y), z(_z) {}

        Number norm() {
            return std::sqrt(x*x + y*y + z*z);
        }
    public:
        Number x, y, z;
    };

    inline anglef atan2(const vec2f& a) {
        return atan2(a.y,a.x);
    }

    inline angled atan2(const vec2d& a) {
        return atan2(a.y,a.x);
    }

    typedef Vector2<float> Vector2f;
    typedef Vector2<double> Vector2d;
    typedef Vector3<float> Vector3f;
    typedef Vector3<double> Vector3d;

    typedef Vector2f vec2f;
    typedef Vector2d vec2d;
    typedef Vector3f vec3f;
    typedef Vector3d vec3d;


    typedef Vector2f Point2f;
    typedef Vector2d Point2d;
    typedef Vector2f Point3f;
    typedef Vector3d Point3d;

    typedef Point2f pt2f;
    typedef Point2d pt2d;
    typedef Point3f pt3f;
    typedef Point3d pt3d;

    typedef Vector2f Size2f;
    typedef Vector3f Size3f;
    typedef Vector2d Size2d;
    typedef Vector3d Size3d;

    typedef Size2f size2f;
    typedef Size3f size3f;
    typedef Size3d size3d;
    typedef Size2d size2d;
SYLPH_END_MATHNS

#endif /* SYLPH_MATH_VECTOR_H_ */

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
