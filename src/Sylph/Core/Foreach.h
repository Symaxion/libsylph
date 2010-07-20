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
 * Created on 31 juli 2009, 21:21
 */

#ifndef FOREACH_H_
#define	FOREACH_H_

#include "Object.h"
#include <cstddef>

struct foreach_container_base {
};

template <class T>
struct foreach_container : public foreach_container_base {

    inline foreach_container(const T & t) : c(t), brk(0), i(c.begin()),
    e(c.end()) {
    };
    const T c;
    mutable int brk;
    mutable typename T::const_iterator i, e;

    inline bool condition() const {
        return (!brk++ && i != e);
    }
};

template <class T>
inline T* foreach_pointer(const T&) {
    return Sylph::null;
}

template <class T>
inline foreach_container<T> foreach_container_create(const T& t) {
    return foreach_container<T > (t);
}

template <typename T>
inline const foreach_container<T>* foreach_cast(
        const foreach_container_base* base, const T*) {
    return static_cast<const foreach_container<T> *> (base);
}


#define sforeach(variable, container) \
for (const ::foreach_container_base& _container_ = \
	::foreach_container_create(container); ::foreach_cast(&_container_, \
	true ? 0 : ::foreach_pointer(container))->condition(); \
	++::foreach_cast(&_container_, true ? 0 : \
	::foreach_pointer(container))->i) \
    for (variable = *::foreach_cast(&_container_, true ? 0 : \
            ::foreach_pointer(container))->i; ::foreach_cast(&_container_, \
            true ? 0 : ::foreach_pointer(container))->brk; \
            --::foreach_cast(&_container_, true ? 0 : \
            ::foreach_pointer(container))->brk)

#endif	/* FOREACH_H_ */

