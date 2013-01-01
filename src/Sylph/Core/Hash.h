/*
 * LibSylph Class Library
 * Copyright (C) 2013 Frank "SeySayux" Erens <seysayux@gmail.com>
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
 * Created on 4 maart 2009, 12:45
 */

#ifndef SYLPH_CORE_HASH_H_
#define	SYLPH_CORE_HASH_H_

#include "Object.h"
#include "Exception.h"
#include "Primitives.h"

SYLPH_BEGIN_NAMESPACE
inline sint hash_internal(const byte * b, std::size_t len) {
    suint hash = 0;
    suint x = 0;
    suint i = 0;

    for(i = 0; i < len; b++, i++) {
        hash = (hash << 4) + (*b);
        if((x = hash & 0xF0000000L) != 0) {
            hash ^= (x >> 24);
        }
        hash &= ~x;
    }
    return hash;
}

template<class T>
struct Hash {
    inline sint operator()(const T & t) const {
        return hash_internal(reinterpret_cast<const byte*>(&t), sizeof (T));
    }
};

template<class T>
struct Hash<T*> {
    inline sint operator()(const T * t) const {
        return t == 0 ? 0 :
                hash_internal(reinterpret_cast<const byte*>(t), sizeof (T));
    }
};

template<>
struct Hash<int> {
    inline sint operator()(const int & i) const {
        return i;
    }
};

SYLPH_END_NAMESPACE

#endif	/* SYLPH_CORE_HASH_H_ */

// vim: ts=4:sts=4:sw=4:sta:et:tw=80:nobk
