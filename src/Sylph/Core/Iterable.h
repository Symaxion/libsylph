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

/*< rev Object-1
 *  rev Iterable-1
 *  rev Exception-1
 *  rev String-1
 *  rev Hashable-1
 >*/


SYLPH_BEGIN_NAMESPACE

SYLPH_PUBLIC
/**
 * Implementing this interface allows your class to be iterated by an
 * @c Iterator. This interface is also required for the correct functioning of
 * the @c sforeach() keyword.
 * Each Iterator should define an @c %Iterator and an @c %MutableIterator type,
 * corresponding to the actual types returned by @c iterator() and @c
 * mutableIterator().
 */
template<class T>
class Iterable : public virtual Object {
public:
    typedef T Type;
    typedef const Iterator<T> Iterator;
    typedef Iterator<T> MutableIterator;
public:
    /**
     * Get an instance of the Iterator for this class. The iterator returned
     * is not mutable, i.e. it cannot modify the contents of the collection.<p>
     * Unless mutability is really required, it is recommended to prefer this
     * method, as it does not allow accidential modifications.
     * @return An @c Iterator specific for the class being iterated over.
     */
    virtual Iterator iterator() const = 0;
    /**
     * Get an instance of the MutableIterator for this class. The iterator
     * returned is mutable, i.e. it can modifiy the contents of the collection.
     * @return An @c MutableIterator for the class being iterated over.
     */
    virtual MutableIterator mutableIterator() = 0;
};
SYLPH_END_NAMESPACE

#endif	/* _ITERABLE_H */

