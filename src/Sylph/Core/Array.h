/* 
 * File:   Array.h
 * Author: frank
 *
 * Created on 8 februari 2009, 14:18
 */

#ifndef ARRAY_H_
#define	ARRAY_H_

#include "Iterable.h"
#include "Comparable.h"
#include "Exception.h"
#include <initializer_list>

SYLPH_START_NAMESPACE(Core)

SYLPH_PUBLIC
/**
 * Array provides a safe array. It works the same like a c-style array (not like
 * std::vector which can expand), but instead of overflowing, it throws an
 * @c Exception whenever you try to access data outside its bounds. Therefore it
 * also keeps track of its own length.
 */
template <class T>
class Array : public virtual Iterable<T> {
    friend bool operator==(const Array<T>& lhs, const Array<T>& rhs);
    friend bool operator<(const Array<T>& lhs, const Array<T>& rhs);

public:
    /**
     * The type of the array, for using with arrays with an unkown type. E.g.:
     * <pre>myarray::Type t = myarray[3];</pre>
     */
    typedef T Type;
    /**
     * The length of the array. This variable is 1-based, while the array itself
     * is 0-based, i.e. if length == N the highest entry in this array is N-1.
     * E.g if array.length == 5, then the higest entry is array[4]
     */
    const int length;

private:
    T carray[];

public:
    /**
     * Creates a new array with the given length.
     * @param len the length of the new array
     */
    explicit Array(std::size_t len);
    /*
     * Creates an array from an initializer list.
     * @param il the initializer list
     */
    Array(std::initializer_list<T> il);
    /**
     * Creates an array from a C-style array. The contents of the array are
     * copied into this array. The original array will not be modified.
     * @param array the c-style array
     */
    Array(T & array[]);
    /**
     * Copy constructor. Copies all entries into this array.
     * @param ar the other array
     */
    Array(Array<T> & ar);
    /**
     * Destructor. Deletes the backing c-style array
     */
    virtual ~Array();

    /**
     * Returns an iterator over the elements. The returned iterator is not
     * mutable. The type is of the iterator is @c ArrayIterator
     */
    Iterator<T> iterator() const;
    /**
     * Returns an mutable iterator over the elements. Elements can be modified
     * by the iterator. The type of the iterator is @c ArrayMutableIterator.
     */
    MutableIterator<T> mutableIterator() const;

    /**
     * Returns a c-style array representing the contents of this Array. The
     * array returned is not a copy of this array, in fact, changes to the
     * returned array are reflected in this Array.
     */
    T * carray();
    /**
     * Returns a c-style array representing the contents of this Array. The
     * array returned is not a copy of this array, in fact, changes to the
     * returned array are reflected in this Array. This version returns a const
     * c-style array and is used when this Array is const.
     */
    const T * carray() const;

    /**
     * Default assignment operator
     * @param other The other array
     */
    template<class T> Array & operator=(const Array<T> & other);

    /**
     * Used for accessing the Array's contents. Its behaviour is identical to
     * that of c-style arrays, but throws an exception instead of overflowing
     * or causing segfaults.
     * @param idx the index in the array from which to return an element
     * @throw ArrayException if <code>idx > length</code>
     */
    T & operator[](std::size_t idx) throw (Exception);
    /**
     * This is the <code>const</code> version of T& operator[]
     * @param idx the index in the array from which to return an element
     * @throw ArrayException if <code>idx > length</code>
     */
    const T & operator[](std::size_t idx) const throw (Exception);

};
template<class T>
inline bool operator==(const Array<T>& lhs, const Array<T>& rhs);
template<class T>
inline bool operator<(const Array<T>& lhs, const Array<T>& rhs);

SYLPH_END_NAMESPACE(Core)

#endif	/* ARRAY_H_ */

