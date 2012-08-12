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

#ifndef SYLPH_MATH_ANGLE_H_
#define SYLPH_MATH_ANGLE_H_

#include "internal_base.h"

#include "Functions.h"

SYLPH_BEGIN_MATHNS

#define RAD * 1
#define DEG * (PI / 180)
#define BID * (PI / 128)

    template<class Number>
    class Angle {
    public:
        Angle(Number n = 0) : value((n = wrapH(n)) == -PI ? PI : n) {}
        Angle(const Angle<Number>& a) : value(a.value) {}

        Angle<Number>& operator=(Number n) {
            wrap(n);
            return *this;
        }

        Angle<Number>& operator=(const Angle<Number>& a) {
            value = a.value;
            return *this;
        }
        
        operator Number() {
            return value;
        }

        operator const Number() const {
            return value;
        }
    private:
        static function<Number(Number)> wrapH;
        void wrap(Number n) {
            value = (n = wrapH(n)) == -PI ? PI : n;
        }
        Number value;
    };

    template<class Number>
    function<Number(Number)> Angle<Number>::wrapH = Sylph::Math::wrap(-PI,PI);

    typedef Angle<float> anglef;
    typedef Angle<double> angled;

    template<class Number>
    class Angle3 {
    private:
        typedef Angle<Number> Angle_;
    public:
        Angle_ x,y,z;
    public:
        Angle3(Angle_ _x = 0, Angle_ _y = 0, Angle_ _z = 0) :
                x(_x), y(_y), z(_z) {}
    };
SYLPH_END_MATHNS

// Keep this at the bottom
#include "TrigFunctions.h"

#endif /* SYLPH_MATH_ANGLE_H_ */

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
