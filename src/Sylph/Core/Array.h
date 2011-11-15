/*
 * LibSylph Class Library
 * Copyright (C) 2011 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not
 *   claim that you wrote the original software. If you use this software
 *   in a product, an acknowledgment in the product documentation would be
 *   appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not be
 *   misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any source
 *   distribution.
 *
 * Created on 8 februari 2009, 14:18
 */

#ifndef SYLPH_CORE_ARRAY_H_
#define	SYLPH_CORE_ARRAY_H_

#include "Iterable.h"
#include "Iterator.h"
#include "Comparable.h"
#include "Exception.h"
#include "Range.h"
#include "Primitives.h"

#include <algorithm>
#include <iostream>

#ifndef SYLPH_NO_CXX0X
#include <initializer_list>
#endif

SYLPH_BEGIN_NAMESPACE
class Any;
template<class T> class Array;


/**
 * Array provides a safe array. It works the same like a c-style array (not like
 * std::vector which can expand), but instead of overflowing, it throws an
 * @c Exception whenever you try to access data outside its bounds. Therefore it
 * also keeps track of its own length. <p>
 * The Array class provided here is reference-counted, which means it's
 * perfectly safe and even recommended to pass it by value instead of by
 * reference or by pointer. This way, the Array acts more like a builtin type
 * and does not obstruct the workflow. <p>
 * Please note that most constructors copy the contents into the array, which
 * means that unless the type used is easy to copy, using the specialized
 * array-to-pointer ( Array<T*> ) is preferred.
 * @tplreqs T CopyConstructible, DefaultConstructible, Assignable
 */
template<class T>
class Array : public virtual Object {
public:

    class LengthProxy {
        friend class Array<T>;
    public:
        operator const size_t&() const {
            return lp;
        }
        const size_t& operator()() const {
            return lp;
        }
    private:
        LengthProxy(const size_t& _lp) : lp(_lp) {}
        size_t lp;
    };

    /**
     * @todo Write documentation!
     */
    template<class C, class V>
    class S_ITERATOR : public RandomAccessIterator<V, S_ITERATOR<C,V> > {
    public:
        typedef RandomAccessIterator<V, S_ITERATOR<C,V> > super;

        S_ITERATOR(bool begin = false, C* obj = null) : super(begin),
                _obj(obj) {
            _currentIndex = begin ? 0 : (_obj->length - 1);
        }

        template<class C1, class V1>
        bool equals(const S_ITERATOR<C1,V1>& other) const {
            return _currentIndex == other._currentIndex &&
                    _obj == other._obj;
        }

        template<class C1, class V1>
        S_ITERATOR(const S_ITERATOR<C1,V1>& other) {
            _currentIndex = other._currentIndex;
            _obj = other._obj;
        }

        typename super::value_type& current() {
            return (*_obj)[_currentIndex];
        }

        typename super::const_reference current() const {
            return (*_obj)[_currentIndex];
        }

        bool hasNext() const {
            return _currentIndex < (_obj->length - 1);
        }

        void next() {
            _currentIndex++;
        }

        bool hasPrevious() const {
            return _currentIndex > 0;
        }

        void previous() {
            _currentIndex--;
        }

        idx_t currentIndex() const {
            return _currentIndex;
        }

        size_t length() const {
            return _obj->length;
        }
    //private:
        idx_t _currentIndex;
        C* _obj;
    };

    S_ITERABLE(Array<T>,T)
    S_REVERSE_ITERABLE(Array<T>,T)
public:
    /**
     * A function that is used for filtering by the filter() method. This
     * function takes both an instance of the class this Array contains, and
     * a reference to a reference to any kind of other data that may need to
     * be passed to the FilterFunction.
     */
    typedef bool(*FilterFunction)(const T&, Any&);
    /**
     * The length of the array. This variable is 1-based, while the array itself
     * is 0-based, i.e. if length == N the highest entry in this array is N-1.
     * E.g if array.length == 5, then the highest entry is array[4]
     */
#ifdef SYLPH_DOXYGEN
    const size_t length;
#else
    LengthProxy length;
#endif

    /**
     * Creates an Array<T> from a pointer to T and a length. The new array will
     * have the length specified in <code>length</code>. The original array will
     * not be modified, the contents are copied. No bounds-checking
     * is done, therefore, use this function at your own responsibility!
     * @param length The length of the original C array
     * @param orig The original C array, supplied as a pointer.
     */
    inline static Array<T> fromPointer(std::size_t length, T * orig) {
        Array<T> ar(length);
        for (idx_t x = 0; x < length; x++)ar[x] = orig[x];
        return ar;
    }
public:

    /**
     * Creates an Array with the specified length. A new instance of the
     * reference counted data is created, its reference count set to 1 and the
     * internal C array is allocated to have the specified length.
     * @param len The length of the new Array.
     */
    explicit Array(std::size_t len = 0) : length(len), data(new Data(len)) {}

#ifndef SYLPH_NO_CXX0X
    /**
     * Creates an Array from an initializer list. This constructor allows the
     * easier, more familiar syntax of Array creation, but requires C++0x. Using
     * this constructor, arrays can be initialized as following:
     * <pre>Array<int> myarr = {5,4,7,9};</pre>
     * A new instance of the reference counted data is created, the reference
     * count is set to 1, the length is set to the length of the initializer
     * list, and all data is copied into a newly allocated C array.
     * @param il The initializer_list used to create the array.
     */
    Array(const std::initializer_list<T> & il) : length(il.size()),
            data(new Data(length)) {
        for (idx_t i = 0; i < il.size(); i++) {
            data->_carray[i] = il.begin()[i];
        }
    }
#endif

    /**
     * Creates an Array from an existing C-style array. Note that you can only
     * pass a true array, i.e. you cannot pass a pointer that acts as an array.
     * If you only have a pointer, you'll have to initialize using
     * Array::fromPointer(size_t, length) . <p>
     * A new instance of the reference counted data is created, the reference
     * count is set to 1, the length is set to the length of the Array, all
     * data is copied into a newly allocated C array with the same length as
     * the original array. The original array remains unmodified.
     * @param array A traditional, C-style array to create this Array from.
     */
    template<size_t N>
    Array(const T(&array)[N]) : length(N), data(new Data(N)) {
        for (idx_t i = 0; i < length; i++) {
            data->_carray[i] = array[i];
        }
    }

    /**
     * Creates an Array from another instance of the Array class. The data is
     * not copied, instead, the pointer to the reference counted data will be
     * set to the reference counted data of the other Array, and the reference
     * count will increase by 1. Other fields of the reference counted data
     * remain unmodified.
     * @param other An other Array from which to use the reference counted data.
     */
    Array(const Array<T> & other) : length(other.length), data(other.data) {
        data->refcount++;
    }

    /**
     * Creates an array from a range of items. Every item within the range will
     * be added to the array. This is most useful for integral types, as other
     * types usually don't support the required semantics.<p>
     * A new instance of the reference counted data is created, the reference
     * count is set to 1, the length is set to <code>ran.last() - ran.first()
     * </code>, a new C-style array with this length will be allocated.
     * @param ran a range class that specifies the lower and upper boundaries.
     * @tplreqs T operator++, LessThanComparable
     */

    Array(const basic_range<T> & ran) : length(ran.last() - ran.first()),
            data(new Data(length)) {
        idx_t idx = 0;
        for (T x = ran.first(); x < ran.last(); x++) {
            *this[idx] = x;
            idx++;
        }
    }

    /**
     * Creates an Array from a single item. This is useful for implicit
     * conversions, as it allows a single instance of a class to be passed as
     * an Array of that class with length 1. <p>
     * A new instance of the reference counted data is created, the reference
     * count set to 1, the length is set to 1, and a new C-style array with
     * length 1 is allocated. The object is copied into this array, the original
     * object remains unmodified.
     * @param t An object to create a length-1 array from.
     */
    explicit Array(const T& t) : length(1), data(new Data(1)) {
        data->_carray[0] = t;
    }

    /**
     * Destructor. Reduces the reference count by 1. If the reference count
     * reaches 0, the internal backing data will be destroyed.
     */
    virtual ~Array() {
        data->refcount--;
        if (!data->refcount) {
            delete data;
            data = null;
        }
    }

    const T& get(idx_t i) const {
        return data->_carray[i];
    }

    void put(idx_t i, const T& t) {
        data->_carray[i] = t;
    }

    /**
     * Creates a copy of this array. The Array returned from this method is
     * an exact copy of this Array, such that ar == ar.copy() . The returned
     * Array is different from the one returned by operator=, as the reference
     * counted data gets copied as well, in other words, both Arrays will have
     * a different, equal instance of the reference counted data.
     * @return A new Array containing the same data as this Array.
     */
    Array<T> copy() const {
        Array<T> toReturn((std::size_t)length);
        for (idx_t i = 0; i < length; i++) {
            toReturn[i] = (*this)[i];
        }
        return toReturn;
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
     * This will filter the Array according to a FilterFunction. This function
     * returns a new, 'filtered' Array, which only contains the entries for
     * which the FilterFunction returns true.
     * @param func A pointer to the function which is used for filtering
     * @param clientData %Any data to be passed to the FilterFunction
     * @return A new array containing only the filtered data
     */
    Array<T> filter(FilterFunction func, Any& clientData) {
        // I'm terribly sorry but we'll need to iterate twice over the Array...
        size_t newlength;
        for (idx_t i = 0; i < length; i++) {
            if (func(*this[i], clientData)) newlength++;
        }
        Array<T> toReturn(newlength);
        idx_t curpos = 0;
        for (idx_t i = 0; i < length; i++) {
            if (func(*this[i], clientData)) {
                toReturn[curpos] = *this[i];
                curpos++;
            }
        }
        return toReturn;
    }

    /**
     * Sets every entry in the array to the object returned by that classes'
     * default constructor.
     */
    void clear() {
        delete this->data->_carray;
        this->data->_carray = new T[this->data->_length];
    }

    /**
     * Sets the data pointer of this Array to the other Array's. The refcount
     * for the current data pointer gets decreased by 1, the refcount for the
     * data pointer of the other array gets increased by 1. In case the this
     * Array's original data pointer's refcount reaches zero, the original data
     * will be deleted.
     * @param other The other array from which to use the data pointer
     */
    Array<T> & operator=(const Array<T> & other) {
        if (this->data == other.data) return *this;
        this->data->refcount--;
        if (!this->data->refcount) delete this->data;
        this->data = other.data;
        this->length = other.data->_length;
        data->refcount++;
        return *this;
    }

    /**
     * Used for accessing the Array's contents. Its behavior is identical to
     * that of c-style arrays, but throws an exception instead of overflowing
     * or causing segfaults. <p>
     * The Array will assume ownership over any pointers entered in this way.
     * @param idx the index in the array from which to return an element
     * @throw ArrayException if <code>idx > length</code>
     */
    T & operator[](sidx_t idx) throw (Exception) {
        if ((idx < (sidx_t)length) && (idx >= -(sidx_t)length)) {
            return idx >= 0 ? data->_carray[idx] : data->_carray[length + idx];
        } else {
            char buf[2048];
            sprintf(buf, "Array overflow - index: %d , length: %u",
                    signed(idx), unsigned(length));
            sthrow(IndexException, buf);
        }
    }

    /**
     * This is the <code>const</code> version of T& operator[] . Its behavior
     * is identical to that of c-style const arrays, but throws an exception
     * instead of overflowing or causing segfaults.
     * @param idx the index in the array from which to return an element
     * @throw ArrayException if <code>idx > length</code>
     */
    const T & operator[](sidx_t idx) const throw (Exception) {
        if ((idx < (sidx_t)length) && (idx >= -(sidx_t)length)) {
            return idx >= 0 ? data->_carray[idx] : data->_carray[length + idx];
        } else {
            char buf[2048];
            sprintf(buf, "Array overflow - index: %d , length: %u",
                    signed(idx), unsigned(length));
            sthrow(IndexException, buf);
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
    Array<T> operator[](range&& ran) throw (IndexException) {
        // Check for negative indices and adjust
        ran.last = ran.last < 0 ? length + ran.last : ran.last;
        ran.first = ran.first < 0 ? length + ran.first : ran.first;
        if(ran.inverse()) sthrow(IndexException, "Inverted range");

        if ((unsigned)ran.last >= length) {
            char buf[2048];
            sprintf(buf, "Array overflow - range: %u - %u , length: %u",
                    ran.first, ran.last, unsigned(length));
            sthrow(IndexException, buf);
        }

        Array<T> toReturn = Array<T>::fromPointer((ran.last - ran.first)+1,
                data->_carray + ran.first);
        return toReturn;
    }

    /**
     * Const-version of operator[](const range &) .
     * @param ran The range describing the slice
     * @throw ArrayException if ran.last() > length
     */
    const Array<T> operator[](range&& ran) const throw (IndexException) {
        // Check for negative indices and adjust
        ran.last = ran.last < 0 ? length + ran.last : ran.last;
        ran.first = ran.first < 0 ? length + ran.first : ran.first;
        if(ran.inverse()) sthrow(IndexException, "Inverted range");

        if ((unsigned)ran.last >= length) {
            char buf[2048];
            sprintf(buf, "Array overflow - range: %u - %u , length: %u",
                    ran.first, ran.last, unsigned(length));
            sthrow(IndexException, buf);
        }

        Array<T> toReturn = Array<T>::fromPointer((ran.last - ran.first)+1,
                data->_carray + ran.first);
        return toReturn;
    }

#ifndef SYLPH_DOXYGEN
protected:

    struct Data {

        explicit Data(size_t length) : _length(length), 
                 _carray(new T[length]()), refcount(1) {

        }

        virtual ~Data() {
            delete _carray;
        }
        const size_t _length;
        T * _carray;
        suint refcount;
    } * data;
#endif
};

template<class T>
Array<T> makeArray(const std::initializer_list<T>& t) {
    return t;
}

#define A_(...) makeArray({__VA_ARGS__})

/**
 * Compares the two Arrays on equality. To Arrays compare equal when their
 * lengths are identical and each of the items compare equal to the item on the
 * same position in the other array.
 * @return <i>true</i> when the two arrays compare equal, <i>false</i>
 * otherwise.
 * @tplreqs T EqualityComparable
 */
template<class T>
inline bool operator==(const Array<T>& lhs, const Array<T>& rhs) {
    if(lhs.length == rhs.length) {
        for(idx_t i = 0; i < lhs.length; i++) {
            if(lhs[i] != rhs[i]) return false;
        }
        return true;
    }
    return false;
}

/**
 * Pops the first element off the Array, then returns it. As the array is
 * changed, the popped element is no longer part of the array and will no
 * longer be managed by any @c PointerManagers over the Array.
 * @param a An array, from which the element will be popped.
 * @return The first element of the array.
 * @complexity O(1)
 */
template<class T>
inline T shift(Array<T>& a) {
    T t = a[0];
    a = a[range(1,-1)];
    return t;
}

/**
 * Compares the two Arrays. To Arrays compare less than when their lengths are
 * identical and each of the items compare less than to the item on the same
 * position in the other array.
 * @return <i>true</i> when the first array compares less than the first,
 * <i>false</i> otherwise.
 * @tplreqs T LessThanComparable
 */
template<class T>
inline bool operator<(const Array<T>& lhs, const Array<T>& rhs) {
    return std::lexicographical_compare(&lhs[0], &lhs[lhs.length-1],
            &rhs[0], &rhs[rhs.length-1]);
}

template<class T>
inline bool operator!=(const Array<T>& lhs, const Array<T>& rhs) {
    return !(lhs == rhs);
}

template<class T>
inline bool operator>=(const Array<T>& lhs, const Array<T>& rhs) {
    return !(lhs < rhs);
}

template<class T>
inline bool operator<=(const Array<T>& lhs, const Array<T>& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

template<class T>
inline bool operator>(const Array<T>& lhs, const Array<T>& rhs) {
    return !(lhs < rhs) && !(lhs == rhs);
}

template<class T>
std::ostream& operator<<(std::ostream& out, const Array<T>& rhs) {
    out << "{ ";
    for(idx_t i = 0; i < rhs.length - 1; ++i) {
        out << rhs[i] << ", ";
    }
    out << rhs[rhs.length-1] << " }";
    return out;
}

SYLPH_END_NAMESPACE

#endif	/* SYLPH_CORE_ARRAY_H_ */


