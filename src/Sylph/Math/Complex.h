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

#ifndef SYLPH_MATH_COMPLEX_H_
#define SYLPH_MATH_COMPLEX_H_

#include "internal_base.h"
#include "Functions.h"

#include <complex>

SYLPH_BEGIN_MATHNS

    template<class Number>
    class Complex : public Object {
    public:
        inline Complex(Number _r = 0, Number _i = 0) : r(_r), i(_i) {}

        template<class N>
        inline Complex(const std::complex<N>& c) : r(c.real()),
                i(c.imag()) {}
        
        template<class N>
        inline Complex(const Complex<N>& c) : r(c.real()), i(c.imag()) {}

        inline Number& real() { 
            return r;
        }

        inline const Number& real() const {
            return r;
        }

        inline Number& imag() {
            return i;
        }
        
        inline const Number& imag() const {
            return i;
        }

        inline static Complex<Number> polar(Number rho, Number theta) {
            return Complex<Number>(rho * cos(theta), rho * sin(theta));
        }

        template<class N>
        inline Complex& operator=(const Complex<N>& c) {
            r = c.r;
            i = c.i;
            return *this;
        }

        template<class N>
        inline Complex<Number>& operator=(N n) {
            r = n;
            i = 0;
            return *this;
        }

        template<class N>
        inline Complex<Number>& operator=(const std::complex<N>& c) {
            r = c.r;
            i = c.i;
            return *this;
        }

        template<class N>
        inline Complex<Number>& operator+=(N n) {
            r += n;
            return *this;
        }

        template<class N>
        inline Complex<Number>& operator+=(const Complex<N>& c) {
            r += c.r;
            i += c.i;
            return *this;
        }

        template<class N>
        inline Complex<Number>& operator-=(N n) {
            r -= n;
            return *this;
        }

        template<class N>
        inline Complex<Number>& operator-=(const Complex<N>& c) {
            r -= c.r;
            i -= c.i;
            return *this;
        }

        template<class N>
        inline Complex<Number>& operator*=(N n) {
            r *= n;
            i *= n;
            return *this;
        }

        template<class N>
        inline Complex<Number>& operator*=(const Complex<N>& c) {
            Number _r = r;
            Number _i = i;
            r = _r * c.r - _i * c.i;
            i = _r * c.i + _i * c.r;
            return *this;
        }

        template<class N>
        inline Complex<Number>& operator/=(N n) {
            r /= n;
            i *= n;
            return *this;
        }

    private:
        Number r, i;
    };

    typedef Complex<float> Complexf;
    typedef Complex<double> Complexd;
    typedef Complexf complexf;
    typedef Complexd complexd;

    template<class Number>
    inline Number& real(Complex<Number>& c) {
        return c.real();
    }

    template<class Number>
    inline const Number& real(const Complex<Number>& c) {
        return c.real();
    }

    template<class Number>
    inline Number& imag(Complex<Number>& c) {
        return c.imag();
    }

    template<class Number>
    inline const Number& imag(const Complex<Number>& c) {
        return c.imag();
    }

    template<class Number>
    inline Number norm(const Complex<Number>& c) {
        return hypot(c.real(),c.imag());    
    }

    template<class Number>
    inline Number abs(const Complex<Number>& c) {
        return sqrt(norm(c));
    }

    template<class Number>
    inline Number arg(const Complex<Number>& c) {
        return atan2(c.imag(), c.real());
    }

SYLPH_END_MATHNS

#endif /* SYLPH_MATH_COMPLEX_H_ */
