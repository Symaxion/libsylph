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

#ifndef SYLPH_MATH_FUNCTIONS_H_
#define SYLPH_MATH_FUNCTIONS_H_

#include "internal_base.h"

#include "../Core/Function.h"
#include "../Core/Traits.h"

SYLPH_BEGIN_MATHNS
    template<class T> class Angle;
    typedef Angle<float> anglef;
    typedef Angle<double> angled;

    template<class T> class Complex;
    typedef Complex<float> complexf;
    typedef Complex<double> complexd;

    template<class T> class Vector2;
    typedef Vector2<float> vec2f;
    typedef Vector2<double> vec2d;

    const double E = M_E;
    const double LOG2E = M_LOG2E;
    const double LOG10E = M_LOG10E;
    const double LN2 = M_LN2;
    const double LN10 = M_LN10;
    
    const double PI = M_PI;
    const double TAU = M_PI * 2;

    const double SQRT2 = M_SQRT2;
    const double SQRT1_2 = M_SQRT1_2;

    inline float exp(float a);
    inline double exp(double a);

    inline float exp2(float a);
    inline double exp2(double a);

    inline float expm1(float a);
    inline double expm1(double a);

    inline float log(float a) {
        return ::logf(a);
    }
    inline double log(double a) {
        return ::log(a);
    }

    inline float ln(float a);
    inline double ln(double a);

    inline float log10(float a);
    inline double log10(double a);

    inline float log2(float a);
    inline double log2(double a);

    inline float log1p(float a);
    inline double log1p(double a);

    inline float logn(float a, float b) {
        return log(a)/log(b);
    }

    inline double logn(double a, double b) {
        return log(a)/log(b);
    }

    inline float modf(float a, float* b);
    inline double modf(double a, double* b);

    inline float ldexp(float a, int b);
    inline double ldexp(double a, int b);

    inline float frexp(float a, int* b);
    inline double frexp(double a, int* b);

    inline int ilogb(float a);
    inline int ilogb(double a);

    inline float scalbn(float a, int b);
    inline double scalbn(double a, int b);
    
    inline byte abs(byte a);
    inline sshort abs(sshort a);
    inline sint abs(sint a) {
        return ::abs(a);
    }
    inline slong abs(slong a);

    inline float abs(float a);
    inline double abs(double a);

    inline float cbrt(float a);
    inline double cbrt(double a) {
        return ::pow(a,1.0/3.0);
    }

    inline float hypot(float a);
    inline double hypot(double a);

    sint pow(sint, suint);

    inline float pow(float a, float b);
    inline double pow(double a, double b);

    inline float sqrt(float a);
    inline double sqrt(double a) {
        return ::sqrt(a);
    }

    inline float erf(float a);
    inline double erf(double a);

    inline float erfc(float a);
    inline double erfc(double a);


    /////////////////////////////////////////////////////////////////

    template<class T, class U>
    auto gcd(T t, U u) -> decltype(t + u) {
        static_assert(S_TRAIT(IsIntegral,T),"gcd requires integral parameters");
        static_assert(S_TRAIT(IsIntegral,U),"gcd requires integral parameters");

        // TODO implement algorithm of Euclides
    }

    template<class T, class U>
    auto lcm(T t, U u) -> decltype(t + u) {
        static_assert(S_TRAIT(IsIntegral,T),"lcm requires integral parameters");
        static_assert(S_TRAIT(IsIntegral,U),"lcm requires integral parameters");

        return t*u / gcd(t,u);
    }

    template<class T>
    function<T(T)> clip(T min, T max) {
        return [=](T a) -> T { a < min ? min : a > max ? max : a; };
    }

    template<class T>
    function<T(T)> proj(T a, T b, T c, T d) {
        T p,q;
        return (p=d-c) >= (q=b-a) ?
            [=](T e) -> T {
                return c + e * q/p;
            } : [=](T e) -> T {
                return (e - c) * p/q;
            };
    }
    
    template<class T>
    S_ENABLE_IF(function<T(T)>,
            S_TRAIT(Not,
                    S_TRAIT2(Or,
                            S_TRAIT(IsIntegral,T),
                            S_TRAIT(IsFloatingPoint,T))))
            wrap(T min, T max) {
        T d = max - min;
        return [=](T a) -> T { 
            while(a > max) a -= d;
            while(a < min) a += d;
            return a;
        };
    }
    
    template<class T>
    S_ENABLE_IF(function<T(T)>,
            S_TRAIT(IsFloatingPoint,T))
            wrap(T a, T b) {
        return [=](T c) -> T {
            return a + fmod(c-a,b-a);
        };
    }

    template<class T>
    S_ENABLE_IF(function<T(T)>,
            S_TRAIT(IsIntegral,T))
            wrap(T a, T b) {
        return [=](T c) -> T {
             return a + ((c-a)%(b-a));
        };
    }

SYLPH_END_MATHNS
#endif /* MATH_FUNCTIONS_H_ */

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
