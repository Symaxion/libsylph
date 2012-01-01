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
 * Created on 31 juli 2009, 21:21
 */

#ifndef SYLPH_CORE_FOREACH_H_
#define	SYLPH_CORE_FOREACH_H_

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

#endif	/* SYLPH_CORE_FOREACH_H_ */

