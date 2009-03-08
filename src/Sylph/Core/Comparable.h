/* 
 * File:   Comparable.h
 * Author: frank
 *
 * Created on 24 december 2008, 10:40
 */

#ifndef _COMPARABLE_H
#define	_COMPARABLE_H

#include "Object.h"

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

#endif	/* _COMPARABLE_H */

