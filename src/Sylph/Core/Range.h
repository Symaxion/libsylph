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

