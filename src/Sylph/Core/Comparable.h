/* 
 * File:   Comparable.h
 * Author: frank
 *
 * Created on 24 december 2008, 10:40
 */

#ifndef COMPARABLE_H_
#define	COMPARABLE_H_

#include "Object.h"

/**
 * @file Comparable.h
 * Include this file if you want your objects to be comparable with operator<
 * ,….
 * It defines operator!=,operator>,operator<=, and operator >= in terms of
 * operator== and operator<. Therefore, you'll only have to overload these in
 * order to make your objects comparable.
 */

SYLPH_START_NAMESPACE(Core)
SYLPH_PUBLIC
template<class T, class V>
inline bool operator!=(const T& lhs, const V& rhs) {
    return !(lhs == rhs);
}

template<class T, class V>
inline bool operator>(const T& lhs, const V& rhs) {
    return !(lhs < rhs) && !(*lhs == rhs);
}

template<class T, class V>
inline bool operator<=(const T& lhs, const V& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

template<class T, class V>
inline bool operator>=(const T& lhs, const V& rhs) {
    return !(lhs < rhs);
}
SYLPH_END_NAMESPACE(Core)

#endif	/* _COMPARABLE_H_ */

