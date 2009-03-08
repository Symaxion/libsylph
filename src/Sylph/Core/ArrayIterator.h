/* 
 * File:   ArrayIterator.h
 * Author: frank
 *
 * Created on 8 februari 2009, 16:12
 */

#ifndef ARRAYITERATOR_H_
#define	ARRAYITERATOR_H_

#include "Iterator.h"
#include "Exception.h"

SYLPH_START_NAMESPACE(Core)

class Array;

SYLPH_PUBLIC

template<class T>
class ArrayIterator : public virtual Iterator<T> {
public:
    ArrayIterator(Array<T> & array) : ar(array) {}
    virtual ~ArrayIterator() {}
    bool hasNext() const;
    const T & next() const;
    bool hasPrevious() const;
    const T & previous() const;
    std::size_t nextIndex() const;
    std::size_t previousIndex() const;
protected:
    Array<T> ar;
    T * last;
    std::size_t idx = 0;
};

template<class T>
class ArrayMutableIterator : public virtual MutableIterator<T>,
        public virtual ArrayIterator<T> {
public:
    ArrayMutableIterator(Array<T> & array) : ArrayIterator(ar) {}
    virtual ~ArrayMutableIterator() {}
    void set(T & t) throw(Exception);
    void insert(T & t) throw(Exception);
    void remove() throw(Exception);
};

SYLPH_END_NAMESPACE(Core)

#endif	/* ARRAYITERATOR_H_ */

