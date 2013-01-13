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
 * Created on 7 april 2009, 20:19
 */

#ifndef SYLPH_CORE_PRIMITIVES_H_
#define	SYLPH_CORE_PRIMITIVES_H_

#include "Object.h"
#include <stdint.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

SYLPH_BEGIN_NAMESPACE

SYLPH_END_NAMESPACE

typedef unsigned char byte;

typedef size_t idx_t;
typedef ptrdiff_t sidx_t;

typedef uint64_t fsize_t;
typedef uint64_t fssize_t;

#ifndef SYLPH_LIKELY
    #if __GNUC__ - 0 >= 3
        #define SYLPH_LIKELY(x) __builtin_expect(!!(x),1)
        #define SYLPH_UNLIKELY(x) __builtin_expect(!!(x),0)
    #else
        #define SYLPH_LIKELY(x) (x)
        #define SYLPH_UNLIKELY(x) (x)
    #endif
#endif


#define SYLPH_SPECIALIZE(Class,Type) extern template class Class<Type>

#define SYLPH_SPECIALIZE_PRIMS(Class) \
    SYLPH_SPECIALIZE(Class,byte); \
    SYLPH_SPECIALIZE(Class,int32_t); \
    SYLPH_SPECIALIZE(Class,uint32_t); \
    SYLPH_SPECIALIZE(Class,int64_t); \
    SYLPH_SPECIALIZE(Class,uint64_t); \
    SYLPH_SPECIALIZE(Class,bool); \
    SYLPH_SPECIALIZE(Class,float); \
    SYLPH_SPECIALIZE(Class,double); \
    SYLPH_SPECIALIZE(Class,::Sylph::String)

// Conversions ///////////////////////////////////////////////////////////////

SYLPH_BEGIN_NAMESPACE
namespace Convert {
    inline uint32_t float2int(float f) {
        return *reinterpret_cast<uint32_t*>(&f);
    }
    inline float int2float(uint32_t i) {
        return *reinterpret_cast<float*>(&i);
    }
    inline uint64_t double2long(double d) {
        return *reinterpret_cast<uint64_t*>(&d);
    }
    inline double long2double(uint64_t l) {
        return *reinterpret_cast<double*>(&l);
    }
    template<class T>
    inline byte* a2bseq(const T& t) {
        return reinterpret_cast<byte*>(&t);
    }

    template<class T>
    inline byte* a2bseq(const T* const t) {
        return reinterpret_cast<byte*>(t);
    }
    template<class T>
    inline T& bseq2a(const byte* b) {
        return *reinterpret_cast<T*>(b);
    }

    template<class T>
    inline uintptr_t ptr2int(const T* const t) {
        return reinterpret_cast<uintptr_t>(t);
    }
}
SYLPH_END_NAMESPACE

#endif	/* SYLPH_CORE_PRIMITIVES_H_ */

// vim: ts=4:sts=4:sw=4:sta:et:tw=80:nobk
