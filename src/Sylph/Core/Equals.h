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
 * Created on 6 maart 2009, 17:15
 */

#ifndef EQUALS_H_
#define	EQUALS_H_

#include "Object.h"

#include <cstring>

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

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

#endif	/* EQUALS_H_ */

