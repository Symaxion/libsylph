/* 
 * File:   Iterable.h
 * Author: frank
 *
 * Created on 6 december 2008, 17:15
 */

#ifndef _ITERABLE_H
#define	_ITERABLE_H

#include "Object.h"
#include "Iterator.h"

SYLPH_START_NAMESPACE(Core)

SYLPH_PUBLIC
/**
 */
template<class T>
class Iterable : public Object {
public:
    Iterable() {}
    virtual ~Iterable() {}
    virtual Iterator<T> iterator() const = 0;
    virtual MutableIterator<T> mutableIterator() = 0;
};
SYLPH_END_NAMESPACE(Core)

#endif	/* _ITERABLE_H */

