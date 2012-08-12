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
 * Created on 6 maart 2009, 17:15
 */

#ifndef SYLPH_CORE_EQUALS_H_
#define	SYLPH_CORE_EQUALS_H_

#include "Object.h"

#include <cstring>

SYLPH_BEGIN_NAMESPACE

/**
 * @todo Write documentation!
 */
template<class T>
struct Equals {
    inline bool operator()(const T& t1, const T & t2) const {
        return t1 == t2;
    }
};

template<>
struct Equals<const char*> {
    inline bool operator()(const char * c1, const char * c2) const {
        return std::strcmp(c1, c2) == 0;
    }
};

template<class T>
struct Equals<T*> {
    inline bool operator()(const T * t1, const T * t2) const {
        return *t1 == *t2;
    }
};
SYLPH_END_NAMESPACE

#endif	/* SYLPH_CORE_EQUALS_H_ */


// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
