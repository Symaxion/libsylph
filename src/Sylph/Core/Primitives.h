/* 
 * File:   Primitives.h
 * Author: frank
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

#endif	/* PRIMITIVES_H_ */

