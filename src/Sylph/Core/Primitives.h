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
 * Created on 7 april 2009, 20:19
 */

#ifndef PRIMITIVES_H_
#define	PRIMITIVES_H_

#include "Object.h"
#include <cstdint>
#define __STDC_FORMAT_MACROS
#include <cinttypes>

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

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

namespace std {
    using ::sidx_t;
    using ::idx_t;
    using ::fsize_t;
    using ::fssize_t;
    using ::ptr_t;
}

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
    inline byte* a2bseq<T*>(const T* const t) {
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

#endif	/* PRIMITIVES_H_ */

