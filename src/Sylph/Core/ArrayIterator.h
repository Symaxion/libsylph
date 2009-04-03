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

SYLPH_BEGIN_NAMESPACE

template<class T> class Array;

SYLPH_PUBLIC

/**
 * This class provides an @c Iterator for @c Array.
 * This iterator is not fail-fast, multithreading
 * is therefore not yet supported!
 * An easier way to create an instance of this
 * iterator that is collection-independant, is to
 * use @c Array::iterator().
 * This iterator does not support modifing the
 * collection while it iterates over it.
 */
template<class T>
class ArrayIterator : public virtual Iterator<T> {
public:
    /**
     * Default constructor.
     * @param array Array to iterate over.
     */
    ArrayIterator(Array<T> & array) : ar(&array), idx(0) {}
    /**
     * Default destructor
     */
    virtual ~ArrayIterator() {}
    /**
     * Check if this iterator has any more entries
     * @return true if this iterator has more entries, false
     * otherwise
     * @see Array::length
     */
    bool hasNext();
    /**
     * Returns the next entry in the array and moves this
     * iterator one place forward. 
     * @throw ArrayException if trying to return an entry
     * outside the bounds of the Array.
     * @return the next entry in the array.
     * @see ArrayIterator::hasNext
     * @see Array::operator[]
     */
    const T & next();
    bool hasPrevious();
    const T & previous();
    std::size_t nextIndex();
    std::size_t previousIndex();
protected:
    #ifndef SYLPH_DOXYGEN
    Array<T> * ar;
    T * last;
    unsigned int idx;
    #endif
};

template<class T>
class ArrayMutableIterator : public virtual MutableIterator<T>,
        public ArrayIterator<T> {
public:
    ArrayMutableIterator(Array<T> & array) : ArrayIterator<T>(array) {}
    virtual ~ArrayMutableIterator() {}
    void set(T & t) throw(Exception);
    void insert(T & t) throw(Exception);
    void remove() throw(Exception);
};

SYLPH_END_NAMESPACE

#endif	/* ARRAYITERATOR_H_ */

