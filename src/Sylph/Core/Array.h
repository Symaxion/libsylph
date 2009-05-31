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
#include "Range.h"
#include "Util.h"
#include "Primitives.h"

#include <algorithm>
#include <initializer_list>

/*< rev Object-1
 *  rev Iterable-1
 *  rev Exception-1
 *  rev String-1
 *  rev Iterator-1
 *  rev Hashable-1
 *  rev Array-1
 >*/

SYLPH_BEGIN_NAMESPACE

SYLPH_PUBLIC
/**
 * Array provides a safe array. It works the same like a c-style array (not like
 * std::vector which can expand), but instead of overflowing, it throws an
 * @c Exception whenever you try to access data outside its bounds. Therefore it
 * also keeps track of its own length.
 */
template <class T>
class Array : public Iterable<T> {
    friend class Array<int>;
    #ifndef SYLPH_DOXYGEN
    friend class Array<String>;
    #endif
private:

    class ArrayIterator : public Iterator {
    public:
        ArrayIterator(Array<T> & array) : ar(&array), idx(0), last(0) {
        }

        #ifndef SYLPH_DOXYGEN
        virtual ~ArrayIterator() {}
        #endif

        bool hasNext() const {
            return idx < ar->length;
        }

        const T & next() const {
            return last = &ar[idx++];
        }

        bool hasPrevious() hasPrevious() const {
            return idx > 0;
        }

        const T & previous() const {
            return last = &ar[--idx];
        }

        std::idx_t nextIndex() nextIndex() const {
            return idx;
        }

        std::idx_t previousIndex() previousIndex() const {
            return idx - 1;
        }

        virtual void front() const {
            idx = 0;
        }

        virtual void back() back() const {
            idx = ar->length;
        }

        void set(T & t) {
            *last = t;
        }
        void insert(T & t);
        void remove();
    protected:
#ifndef SYLPH_DOXYGEN
        Array<T> * ar;
        mutable T * last;
        mutable std::idx_t idx;
#endif
    };

public:
    /**
     * The length of the array. This variable is 1-based, while the array itself
     * is 0-based, i.e. if length == N the highest entry in this array is N-1.
     * E.g if array.length == 5, then the higest entry is array[4]
     */
    const int & length;
public:
    /**
     * Creates an Array<T> from a pointer to T and a length. The new array will
     * have the length specified in <code>length</code>. The original array will
     * not be modified, the contents are copied. No bounds-checking
     * is done, therefore, use this function at your own responsability!
     * @param length The length of the original C array
     * @param orig The original C array, supplied as a pointer.
     */
    inline static Array<T> fromPointer(std::size_t length, T * orig) {
        Array<T> ar(length);
        for (int x = 0; x < length; x++)ar[x] = orig[x];
        return ar;
    }
public:

    /**
     * Creates a new array with the given length. A new instance of the
     * reference counted data is created, its refcount set to 1. The memory
     * gets zeroed, so it is perfectly safe to compare with 0 to see
     * if a particular entry in the array has been initialized.
     * @param len the length of the new Array.
     */
    explicit Array(std::size_t len) : _length(len), length(_length) {
        data = new Data(len);
        data->_carray = (T*) calloc(len, sizeof (T));
    }

    /**
     * Creates an array from an initializer list. The length is the same as the
     * length of the initializer list. A new instance of the reference counted
     * data is created, its refcount set to 1.
     * @param il the initializer list
     */
    Array(const std::initializer_list<T> & il) : _length(il.size()), length(_length) {
        data = new Data(_length);
        data->_carray = (T*) calloc(il.size(), sizeof (T));
        carraycopy(il.begin(), 0, data->_carray, 0, il.size());
    }

    /**
     * Creates an array from a C-style array. The contents of the array are
     * copied into this array. The original array will not be modified. The
     * length is the same as the length of the C array. A new instance of the
     * reference counted data is created, its refcount set to 1.
     * @param array the c-style array
     */
    Array(const T array[]) : _length(carraysize(array)), length(_length) {
        data = new Data(_length);
        data->_carray = (T*) calloc(_length, sizeof (T));
        carraycopy(array, 0, data->_carray, 0, _length);
    }

    /**
     * Copy constructor. As Array is reference-counted, it will just copy the
     * pointer to the internal reference and increase the counter by 1.
     * @param other A reference to the other Array.
     */
    Array(const Array<T> & other) : _length(other._length) {
        if (this == &other) return;
        this->data = other.data;
        this->_length = other.data->length;
        data->refcount++;
    }

    /**
     * Destructor. This will decrease the reference counter by one. If the
     * counter reaches zero, the backing data will be deleted.
     */
    virtual ~Array() {
        data->refcount--;
        if (!data->refcount) delete data;
    }

    /**
     * Returns an iterator over the elements. The returned iterator is not
     * mutable. 
     */
    Iterator iterator() const {
        return ArrayIterator<T > (*this);
    }

    /**
     * Returns an mutable iterator over the elements. Elements can be modified
     * by the iterator.
     * @note Since Array does not support neither insertion nor deletion,
     * insert() and remove() haven't been implemented.
     */
    MutableIterator mutableIterator() {
        return ArrayIterator<T > (*this);
    }

    /**
     * Returns a c-style array representing the contents of this Array. The
     * array returned is not a copy of this array, in fact, changes to the
     * returned array are reflected in this Array.
     */
    T * carray() {
        return data->_carray;
    }

    /**
     * Returns a c-style array representing the contents of this Array. The
     * array returned is not a copy of this array, in fact, changes to the
     * returned array are reflected in this Array. This version returns a const
     * c-style array and is used when this Array is const.
     */
    const T *carray() const {
        return data->_carray;
    }

    /**
     * Swaps the data pointer of this Array with the other Array. The refcount
     * for the current data pointer gets decreased, the refcount for the data
     * pointer of the other array gets increased. In case the this Array's
     * original data pointer's refcount reaches zero, the original data is
     * deleted.
     * @param other The other array from which to use the data pointer
     */
    Array<T> & operator=(const Array<T> & other) {
        if (this->data == other.data) return;
        this->data->refcount--;
        if (!this->data->refcount) delete this->data;
        this->data = other.data;
        this->_length = other.data->length;
        data->refcount++;
        return *this;
    }

    /**
     * Used for accessing the Array's contents. Its behaviour is identical to
     * that of c-style arrays, but throws an exception instead of overflowing
     * or causing segfaults.
     * @param idx the index in the array from which to return an element
     * @throw ArrayException if <code>idx > length</code>
     */
    T & operator[](std::sidx_t idx) throw (Exception) {
        if (abs(idx) < length) {
            return idx > 0 ? data->_carray[idx] : data->_carray(length + idx);
        } else {
            sthrow(ArrayException, "Array overflow");
        }
    }

    /**
     * This is the <code>const</code> version of T& operator[] . Its behaviour
     * is identical to that of c-style const arrays, but throws an exception
     * instead of overflowing or causing segfaults.
     * @param idx the index in the array from which to return an element
     * @throw ArrayException if <code>idx > length</code>
     */
    const T & operator[](std::sidx_t idx) const throw (Exception) {
        if (abs(idx) < length) {
            return idx > 0 ? data->_carray[idx] : data->_carray(length + idx);
        } else {
            sthrow(ArrayException, "Array overflow");
        }
    }

    /**
     * Slices the array and returns the subarray. E.g. :
     * <pre>Array<String> subarr = myarr[range(5,8)]</pre>
     * <code>subarr</code> now contains the values of @c myarr[5] to @c myarr[8]
     * . Please note that the subarray contains a copy of the original.
     * @param ran The range describing the slice.
     * @throw ArrayException if ran.last() > length
     */
    Array<T> operator[](const range & ran) throw (Exception) {
        if (ran.first() < 0 || ran.last() > length)
            sthrow(ArrayException, "Array overflow");

        Array<T> toReturn = Array<T>::fromPointer(ran.last() - ran.first(),
                data->_carray + ran.first());
        return toReturn;
    }

    /**
     * Const-version of operator[](const range &) .
     * @param ran The range describing the slice
     * @throw ArrayException if ran.last() > length
     */
    const Array<T> operator[](const range & ran) const throw (Exception) {
        if (ran.first() < 0 || ran.last() > length)
            sthrow(ArrayException, "Array overflow");

        Array<T> toReturn = Array<T>::fromPointer(ran.last() - ran.first(),
                data->_carray + ran.first());
        return toReturn;
    }

#ifndef SYLPH_DOXYGEN
private:

    struct Data {
        explicit Data(size_t length) : Data::_length(length), refcount(1) {

        }

        virtual ~Data() {
            free(_carray);
        }
        const int _length;
        T * _carray;
        suint refcount;
    } * data;
    private int _length;
#endif
};

#ifndef SYLPH_DOXYGEN // doxygen shouldn't know about this *evilgrin*

template<>
class Array<String> : public Array<String> {
public:

    static inline Array<String> fromPointer(std::size_t length, char ** orig) {
        Array<String> ar(length);
        for (int x = 0; x < length; x++)ar[x] = orig[x];
        return ar;
    }
};
#endif

/**
 * This is a specialisation for the Array class, for integral types. It's
 * specialisation allows for construction through ranges, otherwise, it's
 * functionality is equal to that of Array .
 */
template<>
class Array<int> : public Array<int> {
public:

    /**
     * Creates an integer array from a range. The following syntax
     * <pre> Array<int>(range(X, Y)); </pre>
     * is just shorthand for
     * <pre>Array<int>(Y-X) arr;
     * for(int i = X; i < Y; i++) arr[i]=X+i;</pre>
     * A new shared data pointer gets created. Length is equal to ran.last() -
     * ran.first()
     * @param ran The range describing the contents of the array.
     */
    Array(const range & ran) : _length(ran.last() - ran.first()), length(_length) {
        data = new Data(_length);
        data->_carray = (T*) calloc(_length, sizeof (T));
        for (int x = 0; x < _length; x++) {
            *this[x] = x + ran.first();
        }
    }
};

/**
 * Compares the two Arrays on equality. To Arrays compare equal when their
 * lengths are identical and each of the items compare equal to the item on the
 * same position in the other array.
 * @return <i>true</i> when the two arrays compare equal, <i>false</i>
 * otherwise.
 */
template<class T>
inline bool operator==(const Array<T>& lhs, const Array<T>& rhs) {
    return lhs.length == rhs.length ?
            std::equal(lhs.carray[0], lhs.carray[lhs.length - 1], rhs[0]) : false;
}

/**
 * Compares the two Arrays. To Arrays compare less than when their lengths are
 * identical and each of the items compare less than to the item on the same
 * position in the other array.
 * @return <i>true</i> when the first array compares less than the first,
 * <i>false</i> otherwise.
 */
template<class T>
inline bool operator<(const Array<T>& lhs, const Array<T>& rhs) {
    return lhs.length == rhs.length ?
            std::lexicographical_compare(lhs.carray[0], lhs.carray[lhs.length - 1],
            rhs[0], rhs[rhs.length - 1]) : false;
}

SYLPH_END_NAMESPACE

#endif	/* ARRAY_H_ */

