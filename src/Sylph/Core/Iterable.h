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
 * Implementing this interface allows your class to be iterated by an
 * @c Iterator. This interface is also required for the correct functioning of
 * the @c sforeach() keyword.
 */
template<class T>
class Iterable : public Object {
public:
    /**
     * Get an instance of the Iterator for this class. The iterator returned
     * is not mutable, i.e. it cannot modify the contents of the collection.<p>
     * Unless mutability is really required, it is recommended to prefer this
     * method, as it does not allow accidential modifications.
     * @return An @c Iterator specific for the class being iterated over.
     */
    virtual Iterator<T> iterator() const = 0;
    /**
     * Get an instance of the MutableIterator for this class. The iterator
     * returned is mutable, i.e. it can modifiy the contents of the collection.
     * @return An @c MutableIterator for the class being iterated over.
     */
    virtual MutableIterator<T> mutableIterator() = 0;
};
SYLPH_END_NAMESPACE(Core)

#endif	/* _ITERABLE_H */

