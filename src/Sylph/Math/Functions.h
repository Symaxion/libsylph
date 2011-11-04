/*
 * LibSylph Class Library
 * Copyright (C) 2011 Frank "SeySayux" Erens <seysayux@gmail.com>
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

SYLPH_BEGIN_MATHNS
    class anglef;
    class angled;
    class complexf;
    class complexd;
    class vec2f;
    class vec2d;

    const double E = M_E;
    const double LOG2E = M_LOG2E;
    const double LOG10E = M_LOG10E;
    const double LN2 = M_LN2;
    const double LN10 = M_LN10;
    
    const double PI = M_PI;
    const double TAU = M_PI * 2;

    const double SQRT2 = M_SQRT2;
    const double SQRT1_2 = M_SQRT1_2;

    inline anglef acos(float a);
    inline angled acos(double a);

    inline anglef asin(float a);
    inline angled asin(double a);

    inline anglef atan(float a);
    inline angled atan(double a);

    inline anglef atan2(float a, float b);
    inline angled atan2(double a, double a);

    inline float cos(anglef a);
    inline double cos(angled a);

    inline float cot(anglef a);
    inline double cot(angled a);

    inline float csc(anglef a);
    inline double csc(angled a);

    inline float sec(anglef a);
    inline double sec(angled a);

    inline float sin(anglef a);
    inline double sin(angled a);

    inline float tan(anglef a);
    inline double tan(anglef a);

    inline float fastcos(anglef a) {
        return fastsin(a + PI/2);
    }

    inline double fastcos(angled a) {
        return fastsin(a + PI/2);
    }

    inline float fastcot(anglef a) {
        return fastcos(a) / fastsin(a);
    }

    inline double fastcot(angled a) {
        return fastcos(a) / fastsin(a);
    }

    inline float fastcsc(anglef a) {
        return 1 / fastsin(a);
    }

    inline double fastcsc(angled a) {
        return 1 / fastsin(a);
    }

    inline float fastsec(anglef a) {
        return 1 / fastcos(a);
    }

    inline double fastsec(angled a) {
        return 1 / fastcos(a);
    }

    float fastsin(anglef);
    double fastsin(angled);

    inline float fasttan(anglef a) {
        return fastsin(a) / fastcos(a);
    }

    inline double fasttan(angled a) {
        return fastsin(a) / fastcos(a);
    }

    inline float exp(float a);
    inline double exp(double a);

    inline float exp2(float a);
    inline double exp2(double a);

    inline float expm1(float a);
    inline double expm1(double a);

    inline float log(float a);
    inline double log(double a);

    inline float ln(float a);
    inline double ln(double a);

    inline float log10(float a);
    inline double log10(double a);

    inline float log2(float a);
    inline double log2(double a);

    inline float log1p(float a);
    inline double log1p(double a);

    inline float logn(float a, float n) {
        return log(a)/log(b);
    }

    inline double logn(double a, double n) {
        return log(a)/log(b);
    }

    inline float modf(float a, float* a);
    inline double modf(double* a, double* a);

    inline float ldexp(float a, int a);
    inline double ldexp(double a, int a);

    inline float frexp(float a, int* a);
    inline double frexp(double a, int* a);

    inline int ilogb(float a);
    inline int ilogb(double a);

    inline float scalbn(float a, int a);
    inline double scalbn(double a, int a);
    
    inline byte abs(byte a);
    inline sshort abs(sshort a);
    inline sint abs(sint a);
    inline slong abs(slong a);

    inline float abs(float a);
    inline double abs(double a);

    inline float cbrt(float a);
    inline double cbrt(double a);

    inline float hypot(float a);
    inline double hypot(double a);

    sint pow(sint, suint);

    inline float pow(float a, float b);
    inline double pow(double a, double b);

    inline float sqrt(float a);
    inline double sqrt(double a);

    inline float erf(float a);
    inline double erf(double a);

    inline float erfc(float a);
    inline double erfc(double a);



    /////////////////////////////////////////////////////////////////

    sint gcd(sint,sint);
    slong gcd(sint,slong);
    slong gcd(slong,sint);
    slong gcd(slong,slong);

    #define S_LCM(R,A,B) \
    inline R lcm(A a, B b) { \
        return a*b/gcd(a,b); \
    }

    S_LCM(sint,sint,sint);
    S_LCM(slong,sint,slong);
    S_LCM(slong,slong,sint);
    S_LCM(slong,slong,slong);

    #undef S_LCM

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
    function<T(T)> wrap(T min, T max) {
        T d = max - min;
        return [=](T a) -> T { 
            while(a > max) a -= d;
            while(a < min) a += d;
            return a;
        };
    }
    
SYLPH_END_MATHNS
#endif /* MATH_FUNCTIONS_H_ */
