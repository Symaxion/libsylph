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
 * Created on 9 december 2008, 15:34
 */

#ifndef SYLPH_CORE_UTIL_H_
#define	SYLPH_CORE_UTIL_H_

#include "Object.h" // macros
#include "Exception.h"
#include "Array.h"

#include <math.h>
#include <string.h>

SYLPH_BEGIN_NAMESPACE

// TODO: move this to Array
template<class T>
inline void carraycopy(const T src[], std::size_t srcPos, T dest[],
        std::size_t destPos, std::size_t length) throw (Exception) {
    memcpy(dest+destPos,src+srcPos, length*sizeof(T));
}

template<class T>
inline void arraycopy(const Array<T> & src, std::size_t srcPos, Array<T> & dest,
        std::size_t destPos, std::size_t length) throw (Exception) {

    std::size_t srcSize = src.length;
    std::size_t destSize = dest.length;
    if (srcPos + length > srcSize) sthrow(IndexException, "Source array too short");
    if (destPos + length > destSize) sthrow(IndexException, "Dest array too short");

    memcpy(dest.carray() + destPos, src.carray() + srcPos, length*sizeof(T));
}

template <typename T, std::size_t N>
inline std::size_t carraysize(T(&)[N]) {
    return N;
}

// TODO: Move this to math
template<class T, class U = T>
inline U abs(T t) {
    return t > 0 ? t : -t;
}

template<>
inline unsigned int abs<int, unsigned int>(int t) {
    return t > 0 ? t : -t;
}

template<>
inline unsigned long abs<long, unsigned long>(long t) {
    return t > 0 ? t : -t;
}

template<>
inline unsigned short abs<short, unsigned short>(short t) {
    return t > 0 ? t : -t;
}

template<class T>
inline signed char sign(T t) {
    return t > 0 ? 1 : t == 0? 0 : -1;
}

template<>
inline signed char sign<double>(double t) {
    return copysign(1.0,t);
}


template<>
inline signed char sign<float>(float t) {
    return copysignf(1.0f, t);
}


SYLPH_END_NAMESPACE

#endif	/* SYLPH_CORE_UTIL_H_ */


// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
