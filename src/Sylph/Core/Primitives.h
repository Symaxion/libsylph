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
typedef int16_t sshort;
typedef int32_t sint;
typedef int64_t slong;
typedef uint16_t sushort;
typedef uint32_t suint;
typedef uint64_t sulong;

#define S_FMT_S PRIi16
#define S_FMT_US PRIu16
#define S_FMT_I PRIi32
#define S_FMT_UI PRIu32
#define S_FMT_L PRIi64
#define S_FMT_UL PRIu64

#define SIC(x) INT32_C(x)
#define SUIC(x) UINT32_C(x)
#define SLC(x) INT64_C(x)
#define SULC(x) UINT64_C(x)


#ifdef __i386__
typedef suint idx_t;
typedef sint sidx_t;

typedef suint ptr_t;
#elif defined(__x86_64__)
typedef sulong idx_t;
typedef slong sidx_t;

typedef sulong ptr_t;
#endif

typedef sulong fsize_t;
typedef slong fssize_t;

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
    SYLPH_SPECIALIZE(Class,sint); \
    SYLPH_SPECIALIZE(Class,suint); \
    SYLPH_SPECIALIZE(Class,slong); \
    SYLPH_SPECIALIZE(Class,sulong); \
    SYLPH_SPECIALIZE(Class,bool); \
    SYLPH_SPECIALIZE(Class,float); \
    SYLPH_SPECIALIZE(Class,double); \
    SYLPH_SPECIALIZE(Class,::Sylph::String)

// Conversions ///////////////////////////////////////////////////////////////

SYLPH_BEGIN_NAMESPACE
namespace Convert {
    inline suint float2int(float f) {
        return *reinterpret_cast<suint*>(&f);
    }
    inline float int2float(suint i) {
        return *reinterpret_cast<float*>(&i);
    }
    inline sulong double2long(double d) {
        return *reinterpret_cast<sulong*>(&d);
    }
    inline double long2double(sulong l) {
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
    inline ptr_t ptr2int(const T* const t) {
        return reinterpret_cast<ptr_t>(t);
    }
}
SYLPH_END_NAMESPACE

#endif	/* SYLPH_CORE_PRIMITIVES_H_ */


// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
