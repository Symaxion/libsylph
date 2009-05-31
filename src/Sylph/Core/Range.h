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

class range {
public:
    inline range(int first, int last) {
        if(first>last) std::swap(first,last);
        _first = first;
        _last = last;
    }
    inline virtual ~range() {}
    inline int first() { return _first; }
    inline int last() { return _last; }
private:
    int _first;
    int _last;
};

SYLPH_END_NAMESPACE

#endif	/* RANGE_H_ */

