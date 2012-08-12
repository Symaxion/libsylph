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

#ifndef SYLPH_MATH_QUATERNION_H_
#define SYLPH_MATH_QUATERNION_H_

#include "internal_base.h"
#include "Vector.h"
#include "Angle.h"

SYLPH_BEGIN_MATHNS

template<class Number>
class Quaternion : public Object {
public:
    Quaternion(Number r = 0, Number i = 0, Number j = 0, Number k = 0) :
            r(r), i(i), j(j), k(k) {}

    Quaternion(Angle<Number> a, const Vector<Number>& v) :
            r(cos(a/2)), i(v.x*sin(a/2)), j(v.y*sin(a/2)), k(v.z*sin(a/2)) {};

    Number& real() {
        return r;
    }

    const Number& real() const {
        return r;
    }

    Vector<Number&> imag() {
        return {i,j,k};
    }

    const Vector<const Number&> imag() const {
        return {i,j,k};
    }
private:
    Number r,i,j,k;
};

template<class Number>
Number& real(Quaternion<Number>& q) {
    return q.real();
}

template<class Number>
const Number& real(const Quaternion<Number>& q) {
    return q.real();
}

template<class Number>
Vector<Number&> imag(Quaternion<Number>& q) {
    return q.imag();
}

template<class Number>
const Vector<const Number&> imag(const Quaternion<Number>& q) {
    return q.imag();
}

SYLPH_END_MATHNS

#endif /* SYLPH_MATH_QUATERNION */

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
