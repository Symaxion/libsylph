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

enum Primitive {
    T_Integer,
    T_Long,
    T_Float,
    T_Double,
    T_Bool,
    T_Array,
    T_String,
    T_Dictionary,
    FAIL
};

template<class T>
inline Primitive primtype(const T &) {
    return FAIL;
}

template<>
inline Primitive primtype<int>(const int &) {
    return T_Integer;
}
template<>
inline Primitive primtype<sint>(const sint &) {
    return T_Integer;
}

template<>
inline Primitive primtype<suint>(const suint &) {
    return T_Integer;
}

template<>
inline Primitive primtype<long>(const long &) {
    return sizeof(int) == sizeof(long) ? T_Integer : T_Long;
}

template<>
inline Primitive primtype<long long>(const long long &) {
    return T_Long;
}

template<>
inline Primitive primtype<slong>(const slong &) {
    return T_Long;
}

template<>
inline Primitive primtype<sulong>(const slong &) {
    return T_Long;
}

template<>
inline Primitive primtype<float>(const float &) {
    return T_Float;
}

template<>
inline Primitive primtype<bool>(const bool &) {
    return T_Bool;
}

template<class T>
inline Primitive primtype<Array<T> >(const Array<T> &) {
    return T_Array;
};

template<>
inline Primitive primtype<String>(const String &) {
    return T_String;
}

template<>
inline Primitive primtype<Dictionary>(const Dictionary &) {
    return T_Dictionary;
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

#endif	/* PRIMITIVES_H_ */

