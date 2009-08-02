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
 * Created on 24 december 2008, 10:40
 */

#ifndef COMPARABLE_H_
#define	COMPARABLE_H_

#include "Object.h"

/**
 * @file Comparable.h
 * Include this file if you want your objects to be comparable with operator<
 * ,….
 * It defines operator!=,operator>,operator<=, and operator >= in terms of
 * operator== and operator<. Therefore, you'll only have to overload these in
 * order to make your objects comparable.
 */

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC
template<class T, class V>
inline bool operator!=(const T& lhs, const V& rhs) {
    return !(lhs == rhs);
}

template<class T, class V>
inline bool operator>(const T& lhs, const V& rhs) {
    return !(lhs < rhs) && !(*lhs == rhs);
}

template<class T, class V>
inline bool operator<=(const T& lhs, const V& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

template<class T, class V>
inline bool operator>=(const T& lhs, const V& rhs) {
    return !(lhs < rhs);
}
SYLPH_END_NAMESPACE

#endif	/* _COMPARABLE_H_ */

