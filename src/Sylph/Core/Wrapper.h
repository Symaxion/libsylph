/* 
 * File:   Wrapper.h
 * Author: frank
 *
 * Created on 19 december 2008, 14:33
 */

#ifndef _WRAPPER_H
#define	_WRAPPER_H

#include "Object.h"
#include <utility>

SYLPH_START_NAMESPACE(Core)
SYLPH_PUBLIC
template<class T>
class Wrapper : public Object {
public:
    Wrapper(T t) {}
    Wrapper(T t) : contents(&t) {}
    virtual ~Wrapper() { delete contents; }
    bool operator==(const T& t) const {
        return *contents == t;
    }
    bool operator==(const Wrapper& w) const {
        return *contents == *(w.contents);
    }
    operator T() const {
        return *contents;
    }
private:
    T * contents;
};
SYLPH_END_NAMESPACE(Core)

#endif	/* _WRAPPER_H */

