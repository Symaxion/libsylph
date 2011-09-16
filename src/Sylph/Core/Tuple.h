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
 *  Created on: 15 sep. 2011
 */

#ifndef SYLPH_CORE_TUPLE_H_
#define SYLPH_CORE_TUPLE_H_

#include "Object.h"
#include <tuple>

SYLPH_BEGIN_NAMESPACE

template<class... T>
class Tuple {
    // TODO implement Tuple

    Tuple(const T&... t) {}
};

template<class T, class U>
struct Pair {
    typedef T FirstType;
    typedef U SecondType;

    T first;
    U second;

    Pair() : first(), second() {}
    Pair(const T& t, const U& u) : first(t), second(u) {}
    Pair(const Tuple<T,U>& t) {
        // TODO Pair(const Tuple<T,U>&)
    }

    operator Tuple<T,U>() const {
        return Tuple<T,U>(first,second);
    }
};

template<class T, class U, class V>
struct Triplet {
    typedef T FirstType;
    typedef U SecondType;
    typedef V ThirdType;

    T first;
    U second;
    V third;

    Triplet() : first(), second(), third() {}
    Triplet(const T& t, const U& u, const V& v) : first(t), second(u),
            third(v) {}
    Triplet(const Tuple<T,U,V>& t) {
        // TODO Triplet(const Tuple<T,U,V>&)
    }

    operator Tuple<T,U,V>() const {
        return Tuple<T,U,V>(first,second,third);
    }
};

SYLPH_END_NAMESPACE

#endif /* SYLPH_CORE_TUPLE_H_ */
