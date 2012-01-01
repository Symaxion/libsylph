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
 *  Created on: 17 sep. 2011
 */

#ifndef SYLPH_CORE_IN_H_
#define SYLPH_CORE_IN_H_

#include "Object.h"
#include "Array.h"
#include "Foreach.h"

#include <initializer_list>

SYLPH_BEGIN_NAMESPACE

#define S_INA(...) == InaHelper({__VA_ARGS__})
#define S_INR(a,b) == InrHelper(a,b)

#if !defined(SYLPH_NO_KEYWORDS) && !defined(SYLPH_NO_IN)
    #ifndef SYLPH_NO_INA
        #define ina S_INA
    #endif
    #ifndef SYLPH_NO_INR
        #define inr S_INR
    #endif
#endif

template<class T>
class InaHelperS {
public:
    InaHelperS(const std::initializer_list<T>& _li) : li(_li) {}

    const std::initializer_list<T>& li;
};

template<class T>
bool operator==(const T& lhs, const InaHelperS<T>& rhs) {
    sforeach(const T& t, rhs.li) {
        if(lhs == t) return true;
    }
    return false;
}

template<class T>
InaHelperS<T> InaHelper(const std::initializer_list<T>& li) {
    return InaHelperS<T>(li);
}

template<class T>
class InrHelperS {
public:
    InrHelperS(const T& _a, const T& _b) : a(_a), b(_b) {}

    const T& a;
    const T& b;
};

template<class T>
bool operator==(const T& lhs, const InrHelperS<T>& rhs) {
    return lhs >= rhs.a && lhs <= rhs.b;
}

template<class T>
InrHelperS<T> InrHelper(const T& a, const T& b) {
    return InrHelperS<T>(a,b);
}


SYLPH_END_NAMESPACE

#endif /* SYLPH_CORE_IN_H_ */
