/* 
 * File:   Iterator.h
 * Author: frank
 *
 * Created on 6 december 2008, 17:16
 */

#ifndef _ITERATOR_H
#define	_ITERATOR_H

#include "Object.h"
#include "Exception.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC
template<class T>
class Iterable;

/**
 * Iterator provides a transparant interface for iterating over collections.
 * Each @c Iterable should have a specific implementation of this class. In case
 * a certain method cannot be implemented (e.g. previous() when a collection
 * does not support reverse iteration) it should throw an @c 
 * UnsupportedOperationException. <p>
 * This class is used implicitly by @c sforeach(), and therefore a correct
 * implementation of it is necessary if you want to use @c sforeach().
 */
template<class T>
class Iterator : public Object {
public:

    /**
     * Creates a new Iterator from an Iterable. This implementation does
     * nothing.
     * @param it The iterable to iterate over.
     */
    Iterator(const Iterable<T> & it) {}

    /**
     * Default destructor.
     */
    virtual ~Iterator() {}
    /**
     * Checks if this iterator has any more entries in forward direction.
     * @return <i>true</i> if there are more entries, <i>false</i> otherwise.
     * @throw UnsupportedOperationException if this Iterator cannot iterate
     * forward.
     */
    virtual bool hasNext() = 0;
    /**
     * Returns the next entry in the forward direction and moves the iterator
     * one place forward.
     * @throw UnsupportedOperationException if this Iterator cannot iterate
     * forward.
     * @throw Exception if there are no more entries.
     * @return The next entry
     */
    virtual const T & next() = 0;
    /**
     * Checks if this iterator has any more entries in backward direction.
     * @return <i>true</i> if there are more entries, <i>false</i> otherwise.
     * @throw UnsupportedOperationException if this Iterator cannot iterate
     * backward.
     */
    virtual bool hasPrevious() = 0;
    /**
     * Returns the next entry in the backward direction and moves the iterator
     * one place backward.
     * @throw UnsupportedOperationException if this Iterator cannot iterate
     * backward.
     * @throw Exception if there are no more entries.
     * @return The previous entry
     */
    virtual const T & previous() = 0;
    /**
     * Returns the next index of the Iterable in the forward direction.
     * @throw UnsupportedOperationException if this Iterator cannot iterate
     * forward.
     * @throw UnsupportedOperationException if the Iterable is unordered.
     * @throw Exception if there are no more entries.
     * @return The next index in the Iterable
     */
    virtual std::size_t nextIndex() = 0;
   /**
     * Returns the next index of the Iterable in the backward direction.
     * @throw UnsupportedOperationException if this Iterator cannot iterate
     * backward.
     * @throw UnsupportedOperationException if the Iterable is unordered.
     * @throw Exception if there are no more entries.
     * @return The previous index in the Iterable
     */
    virtual std::size_t previousIndex() = 0;

    /**
     * Synonym for @c next()
     */
    const T& operator++() { return next(); }
    /**
     * Synonym for @c previous()
     */
    const T& operator--() { return previous(); }
};

/**
 * MutableIterator provides a transparant interface for iterating over
 * collections. Each @c Iterable should have a specific implementation of this
 * class. In case a certain method cannot be implemented (e.g. insert() when
 * a collection does not support insertion) it should throw an @c
 * UnsupportedOperationException. <p>
 * MutableIterator differs from @c Iterator by giving extra options for
 * mutating the collection it iterates over.
 */
template<class T>
class MutableIterator : public virtual Iterator<T> {
public:

    /**
     * Creates a new MutableIterator from an Iterable. This implementation does
     * nothing.
     * @param it The iterable to iterate over.
     */
    MutableIterator(const Iterable<T> & it) {}
    /**
     * Default destructor.
     */
    virtual ~MutableIterator() {}
    /**
     * Replaces the last item returned by next() or previous() with the given
     * item
     * @param t The item to replace the last returned item with.
     * @throw UnsupportedOperationException if this collection does not support
     * replacing (?)
     */
    virtual void set(T & t) throw(Exception) = 0;

    /**
     * Inserts the given item after the last returned item.
     * @param t The item to insert
     * @throw UnsupportedOperationException if this collection does not support
     * insertion.
     */
    virtual void insert(T & t) throw(Exception) = 0;
    /**
     * Removes the last returned item from the collection
     * @throw UnsupportedOperationException if this collection does not suppport
     * removal of items.
     */
    virtual void remove() throw(Exception) = 0;
};
SYLPH_END_NAMESPACE


// note : there is a reason why the name is so strange -- do not use directly!
template<class T>
class s_foreach_container_fjAk8tb1 {
    public:
    inline s_foreach_container_fjAk8tb1(const T& t): c(t), brk(0), i(c){};
    const T c;
    mutable int brk;
    Sylph::Iterator<T> i;
    inline bool condition() const { return (!brk++ && i.hasNext()); }

};
#define sforeach(variable,container)\
for (s_foreach_container_fjAk8tb1 &_container_ = \
         s_foreach_container_fjAk8tb1(container); \
         _container_.condition(); )               \
        for (variable = _container_.i++; _container_.brk; --_container_.brk)

#endif	/* _ITERATOR_H */

