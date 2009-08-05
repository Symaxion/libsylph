/*
 * LibSylph Class Library
 * Copyright (C) 2009 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LibSylph Pulbic License as published
 * by the LibSylph Developers; either version 1.0 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LibSylph
 * Public License for more details.
 *
 * You should have received a copy of the LibSylph Public License
 * along with this Library, if not, contact the LibSylph Developers.
 *
 * Created on 9 december 2008, 15:34
 */

#ifndef UTIL_H_
#define	UTIL_H_

#include "Object.h" // macros
#include "Exception.h"
#include "Array.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

template<class T>
inline void carraycopy(const T src[], std::size_t srcPos, T dest[],
        std::size_t destPos, std::size_t length) throw (Exception) {
    for (int i = 0; i < length; i++) {
        dest[destPos + i] = src[srcPos + i];
    }
}

template<class T>
inline void arraycopy(const Array<T> & src, std::size_t srcPos, Array<T> & dest,
        std::size_t destPos, std::size_t length) throw (Exception) {

    std::size_t srcSize = src.length;
    std::size_t destSize = dest.length;
    if (srcPos + length > srcSize) sthrow(ArrayException, "Source array too short");
    if (destPos + length > destSize) sthrow(ArrayException, "Dest array too short");

    for (int i = 0; i < length; i++) {
        dest[destPos + i] = src[srcPos + i];
    }
}

template <typename T, std::size_t N>
std::size_t carraysize(T(&)[N]) {
    return N;
}

SYLPH_END_NAMESPACE

#endif	/* UTIL_H_ */

