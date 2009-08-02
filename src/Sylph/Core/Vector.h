/*
 * LibSylph Class Library
 * Copyright (C) 2009 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LibSylph Pulbic License as published
 * by the LibSylph Developers; either version 1.0 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LibSylph
 * Public License for more details.
 *
 * You should have received a copy of the LibSylph Public License
 * along with this Library, if not, contact the LibSylph Developers.
 *
 * Created on 6 december 2008, 12:07
 */

#ifndef VECTOR_H_
#define	VECTOR_H_

#include "Array.h"
#include "Collection.h"
#include "Util.h"
#include "Equals.h"
#include "Iterator.h"

#include <vector>
#include <initializer_list>

SYLPH_BEGIN_NAMESPACE

SYLPH_PUBLIC
template<class T>
class Array;
template<class T>
class Vector;

template<class T>
class Vector_base : public Collection<T> {
    friend class Vector<T>;
public:
    class iterator : public RandomAccessIterator<T, Vector<T> > {
    public:
        S_RANDOM_ACCESS_ITERATOR(iterator,T,Vector<T>)
        void construct(bool begin, Vector<T>* obj) const {
            _obj = obj;
            _currentIndex = begin ? 0 : _obj->size();
        }
        bool operator==(const iterator& other) const {
            return _currentIndex == other._currentIndex &&
                    _obj == other._obj && super::operator==(other);
        }
        void copyFrom(iterator& other) const {
            _currentIndex = other._currentIndex;
            _obj = other._obj;
        }
        reference current() const {
            return _obj[_currentIndex];
        }
        bool hasNext() const {
            return _obj->size() < _currentIndex;
        }
        void next() const {
            _currentIndex++;
        }
        bool hasPrevious() const {
            return _currentIndex >= 0;
        }
        void previous() const {
            currentIndex--;
        }
        idx_t currentIndex() const {
            return _currentIndex;
        }
        size_t length() const {
            return _obj->size();
        }
    private:
        mutable idx_t _currentIndex;
        Vector<T>* _obj;
    };
    S_ITERABLE(T)
protected:

    explicit Vector_base(std::size_t initialCount = 16, std::size_t increase = 0) {
        elements = new Array<T > (initialCount);
        capacityIncrease = increase;
        elementCount = 0;
    }

    /**
     * Construct a Vector from an original std::vector. The contents are copied
     * into this Vector. A new Array will be created with the same length
     * as the size of the original vector
     * @param orig The original std
     * @note This constructor is not yet implemented!
     */
    Vector_base(const Vector_base<T> & orig) {
        elements = new Array<T > (orig.elements->length);
        capacityIncrease = orig.capacityIncrease;
        elementCount = orig.elementCount;
        arraycopy(orig.*elements, 0, *elements, 0, orig.elements->length);
    }

    Vector_base(const Array<T> & orig) {
        elements = new Array<T > (orig.length * 2);
        arraycopy(orig, 0, *elements, 0, orig.length);
        elementCount = orig.length;
        capacityIncrease = 0;
    }

    Vector_base(const std::initializer_list<T> & orig) {
        elements = new Array<T > (orig.size()*2);
        capacityIncrease = 0;
        elementCount = 0;
        for (T * t = orig.begin(); t < orig.end(); t++) {
            this->push(&t);
        }
    }

    virtual ~Vector_base() {
        delete elements;
    }

public:
    // vector specific
    void push(const T & t) {
        add(t);
    }

    T pop() {
        T toReturn = *elements[elementCount - 1];
        elementCount--;
        return toReturn;
    }

    T & get(std::size_t idx) {
        if (idx >= elementCount) sthrow(ArrayException, "Vector out of bounds");
        else {
            return *elements[idx];
        }
    }

    const T & get(std::size_t idx) const {
        if (idx >= elementCount) sthrow(ArrayException, "Vector out of bounds");
        else {
            return *elements[idx];
        }
    }

    void set(std::size_t idx, const T & t) {
        if (idx >= elementCount) sthrow(ArrayException, "Vector out of bounds");
        else {
            *elements[idx] = t;
        }
    }

    void trim() {
        Array<T> * oldElements = elements;
        elements = new Array<T > (elementCount);
        arraycopy(*oldElements, 0, *elements, 0, elementCount);
        delete oldElements;
    }

    bool add(const T & t) {
        ensureCapacity(elementCount + 1);
        *elements[elementCount] = t;
        elementCount++;
        return true;
    }

    bool addAll(const Collection<T> & c) {

        sforeach(T & t, c) {
            this->add(t);
        }
        return true;
    }

    void clear() {
        Array<T> * oldElements = elements;
        elements = new Array<T > (oldElements->length);
        elementCount++;
        delete oldElements;
    }

    bool contains(T & t) const {
        return indexOf(t) != -1;
    }

    bool containsAll(const Collection<T> & c) const {
        std::size_t amount = 0;

        sforeach(T & t, c) {
            if (this->contains(t)) amount++;
        }
        return amount == c.size();
    }

    bool operator==(const Collection<T> & c) const {
        Vector_base * v = dynamic_cast<Vector_base> (c);
        if (v == NULL) return false;
        else if (this->size() != c.size()) return false;
        else {
            for (std::size_t x = 0; x < c.size(); x++) {
                if (*this[x] != c[x]) return false;
            }
            return true;
        }
    }

    sint hashCode() const;

    bool empty() const {
        return size() == 0;
    }
    virtual Collection<T> filter(typename Vector_base<T>::FilterFunction func,
      Any& clientData) {
        Vector<T> toReturn;
        for(idx_t i = 0; i < size(); i++) {
            if(func(*this[i],clientData)) toReturn.push(*this[i]);
        }
        return toReturn;
    }

    bool remove(const T & t) {
        bool b;
        (b = indexOf(t) != -1) && removeAt(indexOf(t));
        return b;
    }

    void removeAt(std::size_t idx) {
        if (idx > size()) sthrow(ArrayException, "Vector out of bounds");
        elementCount--;
        if (idx < elementCount)
            arraycopy(*elements, idx + 1, *elements, idx,
                elementCount - idx);
    }

    bool removeAll(const Collection<T> & c) {
        std::size_t i;
        std::size_t j;
        for (i = 0; i < elementCount; i++) {
            if (c.contains(*elements[i])) break;
        }
        if (i == elementCount) return false;

        for (j = i++; i < elementCount; i++) {
            if (!c.contains(*elements[i])) *elements[j++] = *elements[i];
        }
        elementCount -= i - j;
        return true;
    }

    bool retainAll(const Collection<T> & c) {
        std::size_t i;
        std::size_t j;
        for (i = 0; i < elementCount; i++) {
            if (!c.contains(*elements[i])) break;
        }
        if (i == elementCount) return false;

        for (j = i++; i < elementCount; i++) {
            if (c.contains(*elements[i])) *elements[j++] = *elements[i];
        }
        elementCount -= i - j;
        return true;
    }

    std::size_t size() const {
        return elementCount;
    }

    Array<T> toArray() const {
        return elements;
    }

    // vector specific non-destructive

    const T & front() {
        return *elements[0];
    }

    const T & back() {
        return *elements[elementCount - 1];
    }

    sidx_t indexOf(T & t, std::idx_t idx = 0) const {
        for (std::size_t i = idx; i < size(); i++) {
            if (Equals(*this[i], t)) {
                return i;
            }
        }
        return -1;
    }

    inline int lastIndexOf(const T & t) const {
        return lastIndexOf(t, elementCount);
    }

    sidx_t lastIndexOf(T & t, std::size_t idx) const {
        if (idx > size()) sthrow(ArrayException, "Vector out of bounds");
        for (std::size_t i = idx; i >= 0; i--) {
            if (Equals(*this[i], t)) {
                return i;
            }
        }
        return -1;
    }

    T & operator[](std::idx_t idx) {
        return get(idx);
    }

    const T & operator[](std::idx_t idx) const {
        return get(idx);
    }

    Vector_base<T> & operator=(const Vector_base<T> & rhs) const {
        delete elements;
        elements = new Array<T > (rhs.elements->length);
        capacityIncrease = rhs.capacityIncrease;
        elementCount = rhs.elementCount;
        arraycopy(rhs.*elements, 0, *elements, 0, rhs.elements->length);
        return *this;
    }
private:
    std::size_t elementCount;
    std::size_t capacityIncrease;
    Array<T> * elements;

    void ensureCapacity(std::size_t capacity) {
        if (capacity <= elements->length) return;
        std::size_t newsize;
        if (capacityIncrease == 0) newsize = elements->length * 2;
        else newsize = elements->length + capacityIncrease;
        Array<T> * oldElements = elements;
        elements = new Array<T > (newsize);
        arraycopy(*oldElements, 0, *elements, 0, oldElements->length);
        delete oldElements;
    }
};

template<class T>
class Vector : public Vector_base<T> {
public:
    explicit Vector(std::size_t initialCount = 16, std::size_t increase = 0) :
        Vector_base<T>(initialCount,increase) {}

    Vector(const Vector<T> & orig) : Vector_base<T>(orig) {}

    Vector(const Array<T> & orig) : Vector_base<T>(orig) {}

    Vector(const std::initializer_list<T> & orig) : Vector_base<T>(orig) {}
};
template<class T>
class Vector<T*> : public Vector_base<T*> {
public:
    explicit Vector(std::size_t initialCount = 16, std::size_t increase = 0) :
        Vector_base<T*>(initialCount,increase) {}

    Vector(const Vector<T> & orig) : Vector_base<T*>(orig) {}

    Vector(const Array<T> & orig) : Vector_base<T*>(orig) {}

    Vector(const std::initializer_list<T> & orig) : Vector_base<T*>(orig) {}
    Vector<T*> deepCopy() const {
        Vector<T*> toReturn;

        for(typename Vector<T*>::iterator it = this->begin(); 
                it != this->end(); ++it) {
            toReturn.push(new T(*it));
        }
        return toReturn;
    }
};

SYLPH_END_NAMESPACE
#endif	/* VECTOR_H_ */

