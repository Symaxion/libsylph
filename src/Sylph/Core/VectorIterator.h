/*
 * File:   VectorIterator.h
 * Author: frank
 *
 * Created on 6 maart 2009, 18:39
 */

#ifndef _VECTORITERATOR_H
#define	_VECTORITERATOR_H

#include "Iterator.h"
#include "Exception.h"

SYLPH_START_NAMESPACE(Core)

class Vector;

SYLPH_PUBLIC

template<class T>
class VectorIterator : public virtual Iterator<T> {
public:
    VectorIterator(const Vector<T> & vector) : vt(&vector) {}
    virtual ~VectorIterator() {}
    bool hasNext() const;
    const T & next() const;
    bool hasPrevious() const;
    const T & previous() const;
    std::size_t nextIndex() const;
    std::size_t previousIndex() const;
protected:
    Vector<T> * vt;
    T * last;
    std::size_t idx = 0;
};

template<class T>
class VectorMutableIterator : public virtual MutableIterator<T>,
        public virtual VectorIterator<T> {
public:
    VectorMutableIterator(const Vector<T> & vt) : VectorIterator(vt) {}
    virtual ~VectorMutableIterator() {}
    void set(T & t) throw(Exception);
    void insert(T & t) throw(Exception);
    void remove() throw(Exception);
};

SYLPH_END_NAMESPACE(Core)

#endif	/* _VECTORITERATOR_H */
