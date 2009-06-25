/* 
 * File:   Range.h
 * Author: frank
 *
 * Created on 24 april 2009, 19:19
 */

#ifndef RANGE_H_
#define	RANGE_H_


#include "Object.h"
#include <algorithm>

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

template<class T>
class basic_range {
public:
    inline basic_range(T first, T last) {
        if(first>last) std::swap(first,last);
        _first = first;
        _last = last;
    }
    inline virtual ~basic_range() {}
    inline T first() { return _first; }
    inline T last() { return _last; }
private:
    T _first;
    T _last;
};
typedef basic_range<int> range;
typedef basic_range<float> frange;
typedef basic_range<double> drange;

SYLPH_END_NAMESPACE

#endif	/* RANGE_H_ */

