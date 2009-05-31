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

/*< rev Object-1
 *  rev Iterable-1
 *  rev Iterator-1
 *  rev Exception-1
 *  rev String-1
 *  rev Hashable-1
 >*/

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC
template<class T>
class Iterable;

/**
 * Iterator provides a transparant interface for iterating over collections.
 * Each @c Iterable should have a specific implementation of this class. It is
 * not required to implement all methods of this class.
 * <p>
 * A <code>const</code> @c Iterator should allow <code>const</code> access to
 * items in the collection, but must not allow modification of those items.
 * A non-<code>const</code> @c Iterator should allow both access and
 * modification of the items. In order to comply to this behavior, it may
 * be necessary to declare one or more fields as <code>mutable</code>.
 * <p>
 * This class is used implicitly by @c sforeach(), and therefore an
 * implementation of this class is required for each @c Iterable that needs
 * to be able to being iterated over by @c sforeach() .
 */
template<class T>
class Iterator : public virtual Object {
public:
    /**
     * The type of the items inside the collection over which this Iterator
     * iterates.
     */
    typedef T Type;
public:

    /**
     * Creates a new Iterator from an Iterable. An Iterator can either be
     * constructed explicitly with this constructor, in which case the correct
     * type of Iterator for the particular collection needs to be known, or
     * through Iterable::iterator() or Iterable::mutableIterator() .
     * <p>The default implementation does nothing.
     * @param it The iterable to iterate over.
     */
    inline Iterator(const Iterable<T> & it) {}

    #ifndef SYLPH_DOXYGEN
    inline virtual ~Iterator() {}
    #endif
    /**
     * Checks if this iterator has any more entries in forward direction.
     * @return <i>true</i> if there are more entries, <i>false</i> otherwise.
     * @note You are not required to override this method if this Iterator
     * cannot iterate forward.
     */
    virtual bool hasNext() const;
    /**
     * Returns the next entry in the forward direction and moves the iterator
     * one place forward.
     * @throw Exception if there are no more entries.
     * @return The next entry
     * @note You are not required to override this method if this Iterator
     * cannot iterator forward.
     */
    virtual const T & next() const;
    /**
     * Checks if this iterator has any more entries in backward direction.
     * @return <i>true</i> if there are more entries, <i>false</i> otherwise.
     * @note You are not required to override this method if this Iterator
     * cannot iterate backward.
     */
    virtual bool hasPrevious() const;
    /**
     * Returns the next entry in the backward direction and moves the iterator
     * one place backward.
     * @throw Exception if there are no more entries.
     * @return The previous entry
     * @note You are not required to override this method if this Iterator
     * cannot iterate backward.
     */
    virtual const T & previous() const;

    /**
     * Moves the Iterator to the place "before" the first item, that is,
     * it gives the pointer in the iterator such a value that hasPrevious
     * returns false.
     * @note You are not required to override this method if this Iterator
     * cannot iterate backward.
     */
    virtual void front() const;

    /**
     * Moves the Iterator to the place "after" the last item, that is,
     * it gives the pointer in the iterator such a value that hasNext
     * returns false.
     * <p> This method is useful for backward iterating, i.e.
     * <pre>Iterator it = coll.getIterator(); // normal 'forward' iterator
     * it.back(); // ready for backward iteration </pre>
     * @note You are not required to override this method if this Iterator
     * cannot iterate forward
     */
    virtual void back() const;

    /**
     * Returns the next index of the Iterable in the forward direction.
     * @throw Exception if there are no more entries.
     * @return The next index in the Iterable
     * @note You are not required to override this method if this Iterator
     * cannot iterate forward; or if the Iterable is unordered.
     */
    virtual std::idx_t nextIndex() const;

   /**
     * Returns the next index of the Iterable in the backward direction.
     * @throw Exception if there are no more entries.
     * @return The previous index in the Iterable
     * @note You are not required to override this method if this Iterator
     * cannot iterate backward; or if the Iterable is unordered.
     */
    virtual std::idx_t previousIndex() const;

    /**
     * Replaces the last item returned by next() or previous() with the given
     * item
     * @param t The item to replace the last returned item with.
     * @note You are not required to override this method if the collection
     * does not support replacing.
     */
    virtual void set(T & t);

    /**
     * Inserts the given item after the last returned item.
     * @param t The item to insert.
     * @note You are not required to override this method if the collection
     * does not support insertion.
     */
    virtual void insert(T & t);
    /**
     * Removes the last returned item from the collection.
     * @note You are not requried to override this method if the collection
     * does not support removal.
     */
    virtual void remove();

    /**
     * Synonymous for next()
     */
    const T& operator++() const { return next(); }

    /**
     * Synonymous for previous()
     */
    const T& operator--() const { return previous(); }

    /**
     * Synoynmous for next()
     */
    const T& operator++(int) const { return next(); }

    /**
     * Synonymous for previous()
     */
    const T& operator--(int) const { return previous(); }
};

SYLPH_END_NAMESPACE


// note : there is a reason why the name is so strange -- do not use directly!

struct s_foreach_container_base_7tQmTc4i {};

template<class T>
class s_foreach_container_fjAk8tb1 : public s_foreach_container_base_7tQmTc4i {
    public:
    inline s_foreach_container_fjAk8tb1(const T& t): c(t), brk(0), i(c){};
    const T c;
    mutable int brk;
    typename T::Iterator i;
    inline bool condition() const { return (!brk++ && i.hasNext()); }
};

template<class T>
inline s_foreach_container_base_7tQmTc4i s_foreach_container_new(const T & t) {
    return s_foreach_container_fjAk8tb1<T>(t);
}

template<class T>
inline s_foreach_container_fjAk8tb1<T> * sf_cast(
  const s_foreach_container_base_7tQmTc4i& bas, const T&) {
     return static_cast<s_foreach_container_fjAk8tb1<T> >(bas);
}

#define sforeach(variable,container) \
for (s_foreach_container_base_7tQmTc4i & _##container##_ = \
         s_foreach_container_new(container); \
         sf_cast(_##container##_,container)->condition(); )               \
        for (variable = sf_cast(_##container##_, container)->i++; \
         sf_cast(_##container##_, container)->brk; \
             --sf_cast(_ #container#_, container)->brk)

#endif	/* _ITERATOR_H */

