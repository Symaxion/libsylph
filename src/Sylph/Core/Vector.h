/*
 * LibSylph Class Library
 * Copyright (C) 2012 Frank "SeySayux" Erens <seysayux@gmail.com>
 * Copyright (C) 2010 Scott "ernieballsep" Philbrook <ernieballsep@gmail.com>
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
 * Created on 6 december 2008, 12:07
 */

#ifndef SYLPH_CORE_VECTOR_H_
#define	SYLPH_CORE_VECTOR_H_

#include "Array.h"
#include "Util.h"
#include "Equals.h"
#include "Iterator.h"

#include "Collection.h"

#include "Debug.h"

#include <vector>
#include <initializer_list>

SYLPH_BEGIN_NAMESPACE

/**
 * @todo Write documentation!
 * @tplreqs T DefaultConstructible, CopyConstructible, Assignable
 */
template<class T>
class Vector : public Object {
public:

    template<class C, class V>
    class S_ITERATOR : public RandomAccessIterator<V, S_ITERATOR<C,V> > {
        template<class C1, class V1>
        friend class S_ITERATOR;
        friend class Vector<T>;
    public:
        typedef RandomAccessIterator<V, S_ITERATOR<C,V> > super;

        S_ITERATOR(bool begin = false, C* obj = null) : super(begin),
                mObj(obj) {
            mCurrentIndex = begin ? 0 : mObj->size() - 1;
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
            return mCurrentIndex < mObj->size() - 1;
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
            return mObj->size() - 1;
        }
    private:
        idx_t mCurrentIndex;
        C* mObj;
    };

    S_ITERABLE(Vector<T>,T)
    S_REVERSE_ITERABLE(Vector<T>,T)


    /**
     * Creates an empty vector. By default, the initial capacity is 16, the
     * size is 0.
     * @param initialCount The initial capacity of the vector, 16 if none is
     * provided.
     */
    explicit Vector(std::size_t initialCount = 16) :
            elements((std::size_t)initialCount), mSize(0) {
    }

    /**
     * Creates a copy of the vector. 
     *
     * All elements of the other vector will be copied into this vector.
     *
     * TODO implement this!
     *
     * @param other The other Vector.
     */
    Vector(const Vector<T>& other) {
        (void)other;
        SYLPH_STUB;
    }
    
    /**
     *
     * TODO implement
     */
    Vector(std::initializer_list<T> il) : elements(il.size() * 2), 
            mSize(0) {
        for(typename std::initializer_list<T>::const_iterator it = il.begin(); 
                it != il.end(); ++it) {
            add(*it);
        }
        
        
    }

    /**
     * Destroys this vector. If this Vector is holding pointers, this destructor
     * does not deallocate their memory.
     */
    virtual ~Vector() {
    }

    /**
     * Appends given element to the Vector. The element will be copied to the
     * end of the Vector. If the capacity is not sufficient, a new elements
     * array will be allocated with twice the size of the original array
     * and all existing data will be copied into the new array. The size
     * of this Vector will increase by 1.
     * @param t The element to append.
     * @complexity O(1)
     */
    void add(const T& t) {
        ensureCapacity(mSize + 1);
        ++mSize;
        set(mSize - 1, t);
    }

    /**
     * Appends all elements of given Vector to this Vector, in order they
     * have been inserted in the original Vector. This is the equivalent of
     * calling add() for each of the elements in the given Vector in the order
     * they have been inserted.
     * The size of this Vector will increase by the size of the given Vector.
     * @param c Another Vector whose elements to append to this one.
     * @complexity O(n)
     */
    void addAll(const Vector<T>& c) {
        ensureCapacity(mSize + c.mSize);
        for(Vector<T>::const_iterator it = c.begin();
                it != c.end(); ++it) {
            add(*it);
        }
    }

    /**
     * @complexity O(n)
     * TODO
     */
    void removeAll(const Vector<T>& c) {

    }

    /**
     * Returns the current capacity of this Vector. The capacity represents
     * the maximum size this Vector can have without needing to expand and
     * copy all elements to a new, bigger array. Therefore, the capacity must
     * always be greater than or equal to the size of this Vector.
     * @return The current capacity of this Vector.
     * @complexity O(0)
     */
    std::size_t capacity() const {
        return elements.size();
    }

    /**
     * Removes all elements from this vector. This will clear the underlying
     * array of the vector and reduces the sice effectively to 0.
     * @complexity O(n)
     */
    void clear() {
        mSize = 0;
        elements.clear();
    }

    /**
     * @param An object @c t
     * @returns if this Vector has an element equal to @c t
     * @complexity O(n)
     */
    bool contains(const T & t) const {
        return indexOf(t) != -1;
    }

    /**
     * @complexity O(1)
     */
    bool empty() const {
        return mSize == 0;
    }

    /**
     * @complexity O(1)
     */
    const T& get(std::size_t idx) const throw(IndexException) {
        try {
            checkBounds(idx);
            return elements[idx];
        } straced;
    }

    /**
     * @complexity O(1)
     */
    T& get(std::size_t idx) throw(IndexException) {
        try {
            checkBounds(idx);
            return elements[idx];
        } straced;
    }

    /**
     * @complexity O(n)
     */
    sidx_t indexOf(const T & t, idx_t idx = 0) const throw(IndexException) {
        try {
            checkBounds(idx);
        } straced;
        static Equals<T> equf;
        for (std::size_t i = idx; i < mSize; i++) {
            if (equf(get(i), t)) {
                return i;
            }
        }
        return -1;
    }

    /**
     * @complexity O(n)
     */
    sidx_t lastIndexOf(const T & t) const {
        return lastIndexOf(t, mSize - 1);
    }

    /**
     * @complexity O(n)
     */
    sidx_t lastIndexOf(const T & t, std::size_t idx) const 
            throw(IndexException) {
        static Equals<T> equf;
        try {
            checkBounds(idx);
        } straced;

        for (std::size_t i = idx; (signed)i >= 0; --i) {
            if (equf(get(i), t)) {
                return i;
            }
        }
        return -1;
    }

    /**
     * @complexity O(n)
     */
    void remove(const T & t) {
        removeAt(indexOf(t));
    }

    /**
     * @complexity O(n)
     */
    void removeAt(std::size_t idx) throw(IndexException) {
        try {
            checkBounds(idx);
        } straced;
        mSize--;
        if (idx < (elements.size() - 1))
            arraycopy(elements, idx + 1, elements, idx,
                elements.size() - 1 - idx);
    }

    /**
     * @complexity O(n)
     */
    void removeAt(const iterator& i) {
        removeAt(i.currentIndex());
    }

    /**
     * @complexity O(n)
     */
    void removeAt(const const_iterator& i) {
        removeAt(i.currentIndex());
    }

    /**
     * @complexity O(1)
     */
    void set(std::size_t idx, const T & t) throw(IndexException) {
        try {
            checkBounds(idx);
            elements[idx] = t;
        }
        straced;
    }

    /**
     * @complexity O(0)
     */
    std::size_t size() const {
        return mSize;
    }

    /**
     * @complexity O(n)
     */
    Array<T> toArray() const {
        Array<T> toReturn(size());
        for(idx_t i = 0; i < size(); ++i) {
            toReturn[i] = elements[i];
        }
        return toReturn;
    }

    /**
     * @complexity O(n)
     */
    bool operator==(const Vector<T> & c) const {
        if (mSize != c.size()) return false;
        else {
            for (std::size_t x = 0; x < c.size(); x++) {
                if (get(x) != c.get(x)) return false;
            }
            return true;
        }
    }

    /**
     * @complexity O(n)
     */
    inline bool operator<(const Vector<T>& rhs) const {
    return std::lexicographical_compare(this->elements.carray(),
            this->elements.carray() + this->size()-1, rhs.elements.carray(),
            rhs.elements.carray() + rhs.size()-1);
    }

    /**
     * @complexity O(1)
     */
    T & operator[](idx_t idx) throw(IndexException) {
        try {
            return get(idx);
        } straced;
    }

    /**
     * @complexity O(1)
     */
    const T & operator[](idx_t idx) const throw(IndexException) {
        try {
            return get(idx);
        } straced;
    }

    /**
     * @complexity O(n)
     */
    Vector& operator=(const Vector<T> & rhs) {
        elements = Array<T > (rhs.elements.size());
        mSize = rhs.size();
        arraycopy(rhs.elements, 0, elements, 0, rhs.elements.size());
        return *this;
    }


private:
    Array<T> elements;
    std::size_t mSize;

    void ensureCapacity(std::size_t capacity) {
        if (capacity > elements.size()) {
            std::size_t newsize;
            newsize = elements.size() << 1;
            Array<T> oldElements = elements;
            elements = Array<T > (newsize);
            arraycopy(oldElements, 0, elements, 0, oldElements.size());
        }
    }

    inline void checkBounds(std::size_t idx) const 
            throw(IndexException) {
        if (idx >= mSize) sthrow(IndexException, "Vector out of bounds");
    }

};

template<class T>
inline bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs == rhs);
}

template<class T>
inline bool operator>=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs < rhs);
}

template<class T>
inline bool operator<=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

template<class T>
inline bool operator>(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs < rhs) && !(lhs == rhs);
}

template<class T>
Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs) {
    Vector<T> toReturn((lhs.size() + rhs.size())*2);
    toReturn.addAll(lhs);
    toReturn.addAll(rhs);
    return toReturn;
}

SYLPH_END_NAMESPACE

S_BEGIN_TRAITS
S_SET_TRAIT(IsCollection, Vector);
S_SET_TRAIT(IsSequentialCollection, Vector);
S_SET_TRAIT(IsExpandableCollection, Vector);
S_SET_TRAIT(IsRandomAccessCollection, Vector);
S_SET_TRAIT(IsEfficientFrontRetrievable, Vector);
S_SET_TRAIT(IsEfficientMiddleRetrievable, Vector);
S_SET_TRAIT(IsEfficientBackRetrievable, Vector);
S_SET_TRAIT(IsEfficientBackInsertable, Vector);

template<class T>
S_SET_TRAIT_TPL(IsSylphClass, Vector<T>);
template<class T>
S_SET_TRAIT_TPL(IsArrayBacked, Vector<T>);
S_END_TRAITS

#endif	/* SYLPH_CORE_VECTOR_H_ */

// vim: ts=4:sts=4:sw=4:sta:et:tw=80:nobk
