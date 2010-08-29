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
 * Created on 24 april 2009, 19:19
 */

#ifndef RANGE_H_
#define	RANGE_H_


#include "Object.h"
#include <algorithm>

SYLPH_BEGIN_NAMESPACE

/** */
template<class T>
class basic_range {
public:
    /** */
    inline basic_range(T _first, T _last) : first(_first), last(_last) {
    }
    /** */
    inline virtual ~basic_range() {}

    inline bool sequential() const {
        return first <= last;
    }

    inline bool inverse() const {
        return !sequential();
    }

    inline bool singleton() {
        return first == last;
    }

    inline void swap() {
        std::swap(first,last);
    }
    T first;
    T last;
};

/** */
typedef basic_range<unsigned int> range;
/** */
typedef basic_range<float> frange;
/** */
typedef basic_range<double> drange;

SYLPH_END_NAMESPACE

#endif	/* RANGE_H_ */

