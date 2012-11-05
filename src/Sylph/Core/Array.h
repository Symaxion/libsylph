/*
 * LibSylph Class Library
 * Copyright (C) 2012 Frank "SeySayux" Erens <seysayux@gmail.com>
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
#include "Collection.h"

#include <algorithm>
#include <iostream>

#ifndef SYLPH_NO_CXX0X
#include <initializer_list>
#endif

SYLPH_BEGIN_NAMESPACE
template<class T> class Array;

/**
 * Array provides a safe array. 
 *
 * It works the same like a C-style array (not like @c std::vector which can
 * expand), but instead of overflowing, it throws an Exception whenever you try
 * to access data outside its bounds. Therefore it also keeps track of its own
 * length. 
 *
 * The Array class provided here is reference-counted, which means it's
 * perfectly safe and even recommended to pass it by value instead of by
 * reference or by pointer. This way, the Array acts more like a builtin type
 * and does not obstruct the workflow. 
 *
 * Please note that most constructors copy the contents into the array, which
 * means that unless the type used is easy to copy, using the specialized
 * array-to-pointer ( @c Array<T*> ) is preferred.
 *
 * @tplreqs T CopyConstructible, DefaultConstructible, Assignable
 */
template<class T>
class Array : public virtual Object {
public:

    /**
     * @todo Write documentation!
     */
    template<class C, class V>
    class S_ITERATOR : public RandomAccessIterator<V, S_ITERATOR<C,V> > {
        template<class C1, class V1>
        friend class S_ITERATOR;
    public:
        typedef RandomAccessIterator<V, S_ITERATOR<C,V> > super;

        S_ITERATOR(bool begin = false, C* obj = null) : super(begin),
                mObj(obj) {
            mCurrentIndex = begin ? 0 : (mObj->size() - 1);
        }

        template<class C1, class V1>
        bool equals(const S_ITERATOR<C1,V1>& other) const {
            return mCurrentIndex == other.mCurrentIndex &&
                    mObj == other.mObj;
        }

        template<class C1, class V1>
        S_ITERATOR(const S_ITERATOR<C1,V1>& other) : 
                mCurrentIndex(other.mCurrentIndex), mObj(other.mObj) {
        }

        typename super::value_type& current() {
            return (*mObj)[mCurrentIndex];
        }

        typename super::const_reference current() const {
            return (*mObj)[mCurrentIndex];
        }

        bool hasNext() const {
            return mCurrentIndex < (mObj->size() - 1);
        }

        void next() {
            mCurrentIndex++;
        }

        bool hasPrevious() const {
            return mCurrentIndex > 0;
        }

        void previous() {
            mCurrentIndex--;
        }

        idx_t currentIndex() const {
            return mCurrentIndex;
        }

        size_t length() const {
            return mObj->size();
        }
    private:
        idx_t mCurrentIndex;
        C* mObj;
    };

    S_ITERABLE(Array<T>,T)
    S_REVERSE_ITERABLE(Array<T>,T)
public:
    /**
     * Creates an Array<T> from a pointer to T and a length. 
     *
     * The new array will have the length specified in @c length. The original
     * array will not be modified, the contents are copied. No bounds-checking
     * is done, therefore, use this function at your own responsibility!
     *
     * @param length The length of the original C array
     * @param orig The original C array, supplied as a pointer.
     */
    inline static Array<T> fromPointer(std::size_t length, T* orig) {
        Array<T> ar(length);
        for (idx_t x = 0; x < length; ++x)
            ar[x] = orig[x];
        return ar;
    }
public:

    /**
     * Creates an Array with the specified length. 
     *
     * A new instance of the reference counted data is created, its reference
     * count set to 1 and the internal C array is allocated to have the
     * specified length.
     *
     * @param len The length of the new Array.
     */
    explicit Array(std::size_t len = 0) : mOffset(0), mSize(len), 
            mData(new Data(len)) {}

#ifndef SYLPH_NO_CXX0X
    /**
     * Creates an Array from an intializer list. 
     *
     * This constructor allows the easier, more familiar syntax of Array
     * creation, but requires C++11. Using this constructor, arrays can be
     * initialized as following:
     *
     * @code
     * Array<int> myarr = {5,4,7,9};
     * @endcode
     *
     * A new instance of the reference counted data is created, the reference
     * count is set to 1, the length is set to the length of the initializer
     * list, and all data is copied into a newly allocated C array.
     *
     * @param il The initializer_list used to create the array.
     */
    Array(const std::initializer_list<T> & il) : mOffset(0), 
            mSize(il.size()), mData(new Data(mSize)) {
        for (idx_t i = 0; i < il.size(); ++i) {
            mData->mArray[i] = il.begin()[i];
        }
    }
#endif

    /**
     * Creates an Array from an existing C-style array. 
     *
     * Note that you can only pass a true array, i.e. you cannot an array that
     * decayed into a pointer.  If need to create an Array from a decayed C
     * array, you'll have to initialize using 
     * @c Array::fromPointer(size_t, T*) .
     *
     * A new instance of the reference counted data is created, the reference
     * count is set to 1, the length is set to the length of the Array, all
     * data is copied into a newly allocated C array with the same length as
     * the original array. The original array remains unmodified.
     *
     * @param array A traditional, C-style array to create this Array from.
     */
    template<size_t N>
    Array(const T(&array)[N]) : mOffset(0), mSize(N), 
            mData(new Data(N)) {
        for (idx_t i = 0; i < mSize; ++i) {
            mData->mArray[i] = array[i];
        }
    }

    /**
     * Creates an Array from another instance of the Array class. 
     *
     * The data is not copied, instead, the pointer to the reference counted
     * data will be set to the reference counted data of the other Array, and
     * the reference count will increase by 1. Other fields of the reference
     * counted data remain unmodified.
     *
     * @param other An other Array from which to use the reference counted data.
     */
    Array(const Array<T> & other) : mOffset(other.mOffset), 
        mSize(other.mSize), mData(other.mData) {
        mData->refcount++;
    }

    /**
     * Creates an array from a range of items. 
     *
     * Every item within the range will
     * be added to the array. This is most useful for integral types, as other
     * types usually don't support the required semantics.
     *
     * A new instance of the reference counted data is created, the reference
     * count is set to 1, the length is set to <code>ran.last() - ran.first()
     * </code>, a new C-style array with this length will be allocated.
     *
     * @param ran a range class that specifies the lower and upper boundaries.
     * @tplreqs T operator++, LessThanComparable
     */

    Array(const basic_range<T> & ran) : mOffset(0),
            mSize(ran.last() - ran.first()), mData(new Data(mSize)) {
        idx_t idx = 0;
        for (T x = ran.first(); x < ran.last(); ++x) {
            *this[idx] = x;
            idx++;
        }
    }

    /**
     * Destructor. 
     *
     * Reduces the reference count by 1. If the reference count reaches 0, the
     * internal backing data will be destroyed.
     */
    virtual ~Array() {
        mData->refcount--;
        if (!mData->refcount) {
            delete mData;
        }
    }

    T& get(idx_t i) {
        return mData->mArray[mOffset + i];
    }

    const T& get(idx_t i) const {
        return mData->mArray[mOffset + i];
    }

    void put(idx_t i, const T& t) {
        mData->mArray[mOffset + i] = t;
    }

    /**
     * Creates a copy of this array.
     *
     * The Array returned from this method is an exact copy of this Array, such
     * that <code>ar == ar.copy()</code> . The returned Array is different from
     * the one returned by operator=, as the reference counted data gets copied
     * as well, in other words, both Arrays will have a different, equal
     * instance of the reference counted data.
     *
     * @return A new Array containing the same data as this Array.
     */
    Array<T> copy() const {
        Array<T> toReturn(size());
        for (idx_t i = 0; i < size(); ++i) {
            toReturn[i] = (*this)[i];
        }
        return toReturn;
    }

    /**
     * Returns a C-style array representing the contents of this Array. 
     *
     * The array returned is not a copy of this array, in fact, changes to the
     * returned array are reflected in this Array.
     *
     * @return TODO
     */
    T* carray() {
        return mData->mArray;
    }

    /**
     * Returns a C-style array representing the contents of this Array. 
     *
     * The array returned is not a copy of this array, in fact, changes to the
     * returned array are reflected in this Array. This version returns a const
     * C-style array and is used when this Array is const.
     *
     * @return TODO
     */
    const T* carray() const {
        return mData->mArray;
    }

    /**
     * Checks whether this array contains the given element.
     *
     * @param t An object
     * @return true if this array containts the element, false otherwise
     */
    bool contains(const T& t) const {
        for(idx_t i = 0; i < size(); ++i) {
            if(get(i) == t) return true;
        }
        return false;
    }

    /**
     * TODO
     */
    sidx_t indexOf(const T& t, sidx_t offset = 0) const {
        (void)t;
        (void)offset;
        return -1;
    }

    /**
     * TODO
     */
    sidx_t lastIndexOf(const T& t, sidx_t offset = -1) const {
        (void)t;
        (void)offset;
        return -1;
    }

    /**
     *
     */
    size_t size() const {
        return mSize;
    }

    /**
     *
     */
    bool empty() const {
        return size() == 0;
    }

    /**
     * Sets every entry in the array to the object returned by that classes'
     * default constructor.
     */
    void clear() {
        for(idx_t i = 0; i < mSize; ++i) {
            put(i, T());
        }
    }

    /**
     * Sets the data pointer of this Array to the one of the other Array. 
     *
     * The refcount for the current data pointer gets decreased by 1, the
     * refcount for the data pointer of the other array gets increased by 1. In
     * case this Array's original data pointer's refcount reaches zero, the
     * original data will be deleted.
     * 
     * @param other The other array from which to use the data pointer
     */
    Array<T> & operator=(const Array<T>& other) {
        if (this->mData == other.mData) return *this;

        this->mData->refcount--;

        if (!this->mData->refcount) delete this->mData;

        this->mData = other.mData;
        this->mSize = other.mSize;
        this->mOffset = other.mOffset;

        mData->refcount++;

        return *this;
    }

    /**
     * Used for accessing the Array's contents. 
     *
     * Its behavior is identical to that of C-style arrays, but throws an
     * exception instead of overflowing or causing segfaults.
     *
     * @param idx the index in the array from which to return an element
     * @throw ArrayException if <code>idx > size()</code>
     */
    T& operator[](sidx_t idx) throw(Exception) {
        if((idx < makeSigned(mSize)) && (idx >= -makeSigned(mSize))) {
            return idx >= 0 ? get(idx) : get(mSize + idx);
        } else {
            char buf[2048];
            sprintf(buf, "Array overflow - index: %lld , length: %llu",
                    (long long)(idx), (unsigned long long)(mSize));
            sthrow(IndexException, buf);
        }
    }

    /**
     * This is the @c const version of T& operator[] . 
     *
     * Its behavior is identical to that of c-style const arrays, but throws an
     * exception instead of overflowing or causing segfaults.
     *
     * @param idx the index in the array from which to return an element
     * @throw ArrayException if <code>idx > size()</code>
     */
    const T& operator[](sidx_t idx) const throw (Exception) {
        if((idx < makeSigned(mSize)) && (idx >= -makeSigned(mSize))) {
            return idx >= 0 ? get(idx) : get(mSize + idx);
        } else {
            char buf[2048];
            sprintf(buf, "Array overflow - index: %lld , length: %llu",
                    (long long)(idx), (unsigned long long)(mSize));
            sthrow(IndexException, buf);
        }
    }

    /**
     * Slices the array and returns the subarray. 
     *
     * E.g. :
     * @code
     * Array<String> subarr = myarr[range(5,8)];
     * @endcode
     *
     * @c subarr now contains the values of @c myarr[5] to @c myarr[8] . 
     *
     * The returned slice refers directly to the original data, so any 
     * modifications done to the slice will be reflected in the original.
     *
     * @param ran The range describing the slice.
     * @throw ArrayException if ran.last() > length
     */
    Array<T> operator[](range ran) throw (IndexException) {
        // Check for negative indices and adjust
        ran.last = ran.last < 0 ? mSize + ran.last : ran.last;
        ran.first = ran.first < 0 ? mSize + ran.first : ran.first;
        if(ran.inverse()) sthrow(IndexException, "Inverted range");

        if (makeUnsigned(ran.last) >= mSize) {
            char buf[2048];
            sprintf(buf, "Array overflow - range: %u - %u , length: %llu",
                    ran.first, ran.last, (unsigned long long)(mSize));
            sthrow(IndexException, buf);
        }

        Array<T> toReturn = Array<T>(*this);
        toReturn.mOffset += ran.first;
        toReturn.mSize = ran.last - ran.first + 1;

        return toReturn;
    }

    /**
     * Const-version of operator[](range) .
     * @param ran The range describing the slice
     * @throw ArrayException if ran.last() > length
     */
    const Array<T> operator[](range ran) const throw (IndexException) {
        // Check for negative indices and adjust
        ran.last = ran.last < 0 ? mSize + ran.last : ran.last;
        ran.first = ran.first < 0 ? mSize + ran.first : ran.first;
        if(ran.inverse()) sthrow(IndexException, "Inverted range");

        if (makeUnsigned(ran.last) >= mSize) {
            char buf[2048];
            sprintf(buf, "Array overflow - range: %u - %u , length: %llu",
                    ran.first, ran.last, (unsigned long long)(mSize));
            sthrow(IndexException, buf);
        }

        Array<T> toReturn = Array<T>(*this);
        toReturn.mOffset += ran.first;
        toReturn.mSize = ran.last - ran.first + 1;

        return toReturn;
    }

private:
    idx_t mOffset;
    size_t mSize;

    struct Data {
        explicit Data(size_t length) : mArray(new T[length]()), refcount(1) {
        }

        ~Data() {
            delete[] mArray;
        }

        T* mArray;
        suint refcount;

    } * mData;
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
    if(SYLPH_UNLIKELY(lhs.size() == rhs.size())) {
        for(idx_t i = 0; i < lhs.size(); ++i) {
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
 * Compares the two Arrays. To Arrays compare less than when their size()s are
 * identical and each of the items compare less than to the item on the same
 * position in the other array.
 * @return <i>true</i> when the first array compares less than the first,
 * <i>false</i> otherwise.
 * @tplreqs T LessThanComparable
 */
template<class T>
inline bool operator<(const Array<T>& lhs, const Array<T>& rhs) {
    return std::lexicographical_compare(lhs.carray(),
            lhs.carray() + lhs.size()-1, rhs.carray(),
            rhs.carray() + rhs.size()-1);
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
Array<T> operator+(Array<T> lhs, Array<T> rhs) {
    Array<T> toReturn(lhs.size() + rhs.size());

    arraycopy(lhs, 0, toReturn, 0, lhs.size());
    arraycopy(rhs, 0, toReturn, lhs.size(), rhs.size());

    return toReturn;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const Array<T>& rhs) {
    out << "{ ";
    for(idx_t i = 0; i < rhs.size() - 1; ++i) {
        out << rhs[i] << ", ";
    }
    out << rhs[rhs.size()-1] << " }";
    return out;
}

SYLPH_END_NAMESPACE

S_BEGIN_TRAITS

S_SET_TRAIT(IsCollection, Array);
S_SET_TRAIT(IsSequentialCollection, Array);
S_SET_TRAIT(IsRandomAccessCollection, Array);
S_SET_TRAIT(IsEfficientFrontRetrievable, Array);
S_SET_TRAIT(IsEfficientMiddleRetrievable, Array);
S_SET_TRAIT(IsEfficientBackRetrievable, Array);

template<class T>
S_SET_TRAIT_TPL(IsSylphClass, Array<T>);
template<class T>
S_SET_TRAIT_TPL(IsEfficientlyCopyable, Array<T>);

S_END_TRAITS

#endif	/* SYLPH_CORE_ARRAY_H_ */

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
