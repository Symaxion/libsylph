/* 
 * File:   Equals.h
 * Author: frank
 *
 * Created on 6 maart 2009, 17:15
 */

#ifndef EQUALS_H_
#define	EQUALS_H_

#include "Object.h"

#include <cstring>

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC
template<class T>
inline bool Equals(T& t1, T& t2) {
    return t1 == t2;
}

template<>
inline bool Equals<char*>(char *& c1, char *& c2) {
    return std::strcmp(c1, c2) == 0;
}

template<class T>
inline bool PointeeEquals(T * t1, T * t2) {
    return *t1 == *t2;
};
SYLPH_END_NAMESPACE

}
SYLPH_END_NAMESPACE

#endif	/* EQUALS_H_ */

