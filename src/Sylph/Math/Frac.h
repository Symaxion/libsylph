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
 */

#ifndef SYLPH_MATH_FRAC_H_
#define SYLPH_MATH_FRAC_H_

#include "internal_base.h"
#include "Functions.h"

SYLPH_BEGIN_MATHNS
    class frac {
    public:
        inline frac(sint _n = 0, suint _d = 1) : n(_n), d(_d) {
            // abc();            
        }

        // TODO
        explicit frac(float f) {
        }

        // TODO
        explicit frac(double d) {
        }

        inline frac(const frac& o) : n(o.n), d(o.d) {}

        inline sint& num() {
            return n;
        }

        inline const sint& num() const {
            return n;
        }

        inline suint& den() {
            return d;
        }

        inline const suint& den() const {
            return d;
        }

        inline frac& operator=(const frac& o) {
            n = o.n;
            d = o.d;
            return *this;
        }


        inline frac& operator=(int i) {
            n = i;
            d = 1;
            return *this;
        }

        inline frac& operator=(float f) {
            return *this = frac(f);
        }

        inline frac& operator=(double d) {
            return *this = frac(d);
        }
        
        inline frac operator+() const {
            return *this;
        }

        inline frac operator-() const {
            frac f(*this);
            f.n = -n;
            return *this;
        }

        inline frac& operator+=(int i) {
            n += d*i;
            //abc();
            return *this;
        }

        inline frac& operator+=(const frac& f) {
            n = n*f.d + f.n * d;
            d *= f.d;
            //abc();
            return *this;
        }

        inline frac& operator-=(int i) {
            return *this += -i;
        }

        inline frac& operator-=(const frac& f) {
            return *this += -f;
        }

        inline frac& operator*=(int i) {
            n *= i;
            //abc();
            return *this;
        }

        inline frac& operator*=(const frac& f) {
            n *= f.n;
            d *= f.d;
            //abc();
            return *this;
        }

        inline frac& operator/=(int i) {
            d *= i;
            //abc();
            return *this;
        }

        inline frac& operator/=(const frac& f) {
            n *= f.d;
            d *= f.n;
            //abc();
            return *this;
        }

        inline bool operator==(const frac& f) const {
            return n == f.n && d == f.d;
        }

        inline bool operator==(int i) {
            return n == i && d == 1;
        }

        inline bool operator<(const frac& f) const {
            return n * f.d < d * f.n;
        }

        inline bool operator<(int i) const {
            return n < d * i;
        }

        inline operator int() const {
            return n/d;
        }

        inline operator float() const {
            return float(n)/float(d);
        }

        inline operator double() const {
            return double(n)/double(d);
        }

    private:
        /* TODO
        
        inline void abc() {
            suint a = gcd(n,d);
            n /= a;
            d /= a;
        } */

        sint n;
        suint d;
    };

    inline sint& num(frac& f) {
        return f.num();
    }
    
    inline const sint& num(const frac& f) {
        return f.num();
    }

    inline suint& den(frac& f) {
        return f.den();
    }

    inline const suint& den(const frac& f) {
        return f.den();
    }

    inline frac operator+(const frac& l, const frac& r) {
        return frac(l) += r;
    }

    inline frac operator+(const frac& l, int r) {
        return frac(l) += r;
    }

    inline frac operator+(int l, const frac& r) {
        return frac(l) += r;
    }

    inline frac operator-(const frac& l, const frac& r) {
        return frac(l) -= r;
    }

    inline frac operator-(const frac& l, int r) {
        return frac(l) -= r;
    }

    inline frac operator-(int l, const frac& r) {
        return frac(l) -= r;
    }

    inline frac operator*(const frac& l, const frac& r) {
        return frac(l) *= r;
    }

    inline frac operator*(const frac& l, int r) {
        return frac(l) *= r;
    }

    inline frac operator*(int l, const frac& r) {
        return frac(r) *= l;
    }

    inline frac operator/(const frac& l, const frac& r) {
        return frac(l) /= r;
    }

    inline frac operator/(const frac& l,int r) {
        return frac(l) /= r;
    }

    inline frac operator/(int l, const frac& r) {
        return frac(l) /= r;
    }

    S_CMP_SEQ(const frac&)
    S_CMP_SEQ_2(int,const frac&)

    inline frac abs(const frac& f) {
        return frac(abs(f.num()),f.den());
    }

    inline double sqrt(const frac& f) {
        return sqrt((double)f);
    }

    inline double cbrt(const frac& f) {
        return cbrt((double)f);
    }

    inline frac inv(suint i) {
        return frac(1,i);
    }

    inline frac inv(sint i) {
        return frac(i > 0 ? 1 : -1,abs(i));
    }

    inline frac inv(const frac& f) {
        return frac(den(f),num(f));
    }

    frac pow(sint x, sint y) {
       if(y >= 0) return pow(x,(suint)y);
       for(sint i = 0; i < -y; ++i) {
           x *= x;
       }
       return inv(x);
    }

    frac pow(frac x, suint y) {
       if(y == 0) return 1;
       if(x == 0) return 0;
       for(sint i = 0; i < y; ++i) {
           x *= x;
       }
       return x;
    }

    frac pow(frac x, sint y) {
       if(y >= 0) return pow(x,(suint)y);
       for(sint i = 0; i < -y; ++i) {
           x *= x;
       }
       return inv(x);
    }    

    inline bool isnan(const frac& f) {
        return num(f) == 0 && den(f) == 0;
    }

    inline bool isinf(const frac& f) {
        return num(f) != 0 && den(f) == 0;
    }

    inline bool isfinite(const frac& f) {
        return den(f) != 0;
    }
SYLPH_END_MATHNS

// Keep this at the bottom
#include "FracHelper.h"

#endif /* SYLPH_MATH_FRAC_H_ */
