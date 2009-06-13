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

SYLPH_BEGIN_NAMESPACE
        SYLPH_PUBLIC

template<class T> class Array;
class String;
class Dictionary;

SYLPH_END_NAMESPACE

typedef unsigned char byte;
typedef int16_t sshort;
typedef int32_t sint;
typedef int64_t slong;
typedef uint16_t sushort;
typedef uint32_t suint;
typedef uint64_t sulong;

// TODO distinction 32/64 bits platforms
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

SYLPH_BEGIN_NAMESPACE

namespace Primitive {
enum Primitive {
    Integer,
    Long,
    Float,
    Double,
    Bool,
    Array,
    String,
    Dictionary,
    FAIL
};
}

template<class T>
inline Primitive::Primitive primtype(const T &) {
    return FAIL;
}

template<>
inline Primitive::Primitive primtype<int>(const int &) {
    return Primitive::Integer;
}
template<>
inline Primitive::Primitive primtype<sint>(const sint &) {
    return Primitive::Integer;
}

template<>
inline Primitive::Primitive primtype<suint>(const suint &) {
    return Primitive::Integer;
}

template<>
inline Primitive::Primitive primtype<long>(const long &) {
    return sizeof(int) == sizeof(long) ? Primitive::Integer : Primitive::Long;
}

template<>
inline Primitive::Primitive primtype<long long>(const long long &) {
    return Primitive::Long;
}

template<>
inline Primitive::Primitive primtype<slong>(const slong &) {
    return Primitive::Long;
}

template<>
inline Primitive::Primitive primtype<sulong>(const slong &) {
    return Primitive::Long;
}

template<>
inline Primitive::Primitive primtype<float>(const float &) {
    return Primitive::Float;
}

template<>
inline Primitive::Primitive primtype<bool>(const bool &) {
    return Primitive::Bool;
}

template<class T>
inline Primitive::Primitive primtype<Array<T> >(const Array<T> &) {
    return Primitive::Array;
};

template<>
inline Primitive::Primitive primtype<String>(const String &) {
    return Primitive::String;
}

template<>
inline Primitive::Primitive primtype<Dictionary>(const Dictionary &) {
    return Primitive::Dictionary;
};

class SChar : public virtual Object {
public:
    SChar() : SChar(0) {}
    SChar(const char c);
    SChar(const wchar_t wc);
    SChar(const suint i);
    SChar(const SChar& orig);
    virtual ~SChar();
    SChar operator=(const char c);
    SChar operator=(const wchar_t wc);
    SChar operator=(const suint i);
    SChar operator=(const SChar& orig);
private:
    suint repres;
};

typedef SChar schar;
SYLPH_END_NAMESPACE
using Sylph::schar;

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

