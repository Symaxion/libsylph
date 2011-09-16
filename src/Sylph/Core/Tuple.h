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
#include <utility>

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
    Pair(const std::tuple<T,U>& t) {
        // TODO Pair(const std::tuple&)
    }

    Pair(const std::pair<T,U>& t) : first(t.first), second(t.second) {}

    operator Tuple<T,U>() const {
        return Tuple<T,U>(first,second);
    }

    operator std::tuple<T,U>() const {
        return std::tuple<T,U>(first,second);
    }

    operator std::pair<T,U>() const {
        return std::pair<T,U>(first,second);
    }
};

template<class T, class U>
inline Pair<T,U> makePair(const T& t, const U& u) {
    return Pair<T,U>(t,u);
}

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

    Triplet(const std::tuple<T,U,V>& t) {
        // TODO Triplet(const std::tuple&)
    }

    operator Tuple<T,U,V>() const {
        return Tuple<T,U,V>(first,second,third);
    }
    operator std::tuple<T,U,V>() const {
        return std::tuple<T,U,V>(first,second,third);
    }
};

template<class T, class U, class V>
inline Triplet<T,U,V> makeTriplet(const T& t, const U& u, const V& v) {
    return Triplet<T,U,V>(t,u,v);
}

template<class... T>
inline Tuple<T...> L_(const T&... t) {
    return Tuple<T...>(t...);
}

template<class... T>
inline Tuple<T&&...> R_(T&&... t) {
    return Tuple<T&&...>(t...);
}

struct IgnoreHelper {
    template<class T>
    const IgnoreHelper& operator=(T t) const {
        return *this;
    }
};

const struct IgnoreHelper ignore = IgnoreHelper();
#if !defined(SYLPH_NO_KEYWORDS) && !defined(SYLPH_NO_IGNORE)
const struct IgnoreHelper __ = IgnoreHelper();
#endif

SYLPH_END_NAMESPACE

#endif /* SYLPH_CORE_TUPLE_H_ */
