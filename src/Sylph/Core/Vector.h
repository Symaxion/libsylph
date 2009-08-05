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
class Vector : public Collection<T> {
public:
    class iterator : public RandomAccessIterator<T, iterator> {
    public:
        typedef RandomAccessIterator<T, iterator> super;

        iterator(bool begin = false, Vector<T>* obj = NULL)
        : super(begin), _obj(obj) {
            _currentIndex = begin ? 0 : _obj->size();
        }

        iterator(bool begin = false, const Vector<T>* obj = NULL)
        : super(begin), _obj(const_cast<Vector<T>*> (obj)) {
            _currentIndex = begin ? 0 : _obj->size();
        }

        bool equals(const iterator& other) const {
            return _currentIndex == other._currentIndex &&
                    _obj == other._obj;
        }

        iterator(const iterator& other) {
            _currentIndex = other._currentIndex;
            _obj = other._obj;
        }

        typename super::reference current() const {
            return (*_obj)[_currentIndex];
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
            _currentIndex--;
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
public:

    explicit Vector(std::size_t initialCount = 16, std::size_t increase = 0) :
        elements((std::size_t)initialCount), capacityIncrease(increase),
        elementCount(0) {
    }

    Vector(const Vector<T> & orig) :
            elements((std::size_t)orig.elements->length),
            capacityIncrease(orig.capacityIncrease),
            elementCount(orig.elementCount) {
        arraycopy(orig.elements, 0, elements, 0, orig.elements.length);
    }

    Vector(const Array<T> & orig) : elements((size_t)orig.length << 1),
            elementCount(orig.length), capacityIncrease(0){
        arraycopy(orig, 0, elements, 0, orig.length);
    }

    Vector(const std::initializer_list<T> & orig) : elements(orig.size() << 1),
            capacityIncrease(0), elementCount(0){
        for (T * t = orig.begin(); t < orig.end(); t++) {
            this->push(&t);
        }
    }

    virtual ~Vector() {}

    // vector specific
    void push(const T & t) {
        add(t);
    }

    T pop() {
        T toReturn = elements[elementCount - 1];
        elementCount--;
        return toReturn;
    }

    T & get(std::size_t idx) {
        if (idx >= elementCount) sthrow(ArrayException, "Vector out of bounds");
        else {
            return elements[idx];
        }
    }

    const T & get(std::size_t idx) const {
        if (idx >= elementCount) sthrow(ArrayException, "Vector out of bounds");
        else {
            return elements[idx];
        }
    }

    void set(std::size_t idx, const T & t) {
        if (idx >= elementCount) sthrow(ArrayException, "Vector out of bounds");
        else {
            elements[idx] = t;
        }
    }

    void trim() {
        Array<T> oldElements = elements;
        elements = Array<T>(elementCount);
        arraycopy(oldElements, 0, elements, 0, elementCount);
    }

    bool add(const T & t) {
        ensureCapacity(elementCount + 1);
        elements[elementCount] = t;
        elementCount++;
        return true;
    }

    bool addAll(const Collection<T> & c) {
	Array<T> ar = c.toArray();
	sforeach(T& t, ar) {
            this->add(t);
        }
        return true;
    }

    void clear() {
        elementCount = 0;
        elements.clear();
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
        Vector * v = dynamic_cast<Vector> (c);
        if (v == NULL) return false;
        else if (this->size() != c.size()) return false;
        else {
            for (std::size_t x = 0; x < c.size(); x++) {
                if (*this[x] != c[x]) return false;
            }
            return true;
        }
    }

    bool empty() const {
        return size() == 0;
    }
    virtual Collection<T> filter(typename Collection<T>::FilterFunction func,
      Any& clientData) {
        Vector<T> toReturn;
        for(idx_t i = 0; i < size(); i++) {
            if(func((*this)[i],clientData)) toReturn.push((*this)[i]);
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
            arraycopy(elements, idx + 1, elements, idx,
                elementCount - idx);
    }

    bool removeAll(const Collection<T> & c) {
        std::size_t i;
        std::size_t j;
        for (i = 0; i < elementCount; i++) {
            if (c.contains(elements[i])) break;
        }
        if (i == elementCount) return false;

        for (j = i++; i < elementCount; i++) {
            if (!c.contains(elements[i])) elements[j++] = elements[i];
        }
        elementCount -= i - j;
        return true;
    }

    bool retainAll(const Collection<T> & c) {
        std::size_t i;
        std::size_t j;
        for (i = 0; i < elementCount; i++) {
            if (!c.contains(elements[i])) break;
        }
        if (i == elementCount) return false;

        for (j = i++; i < elementCount; i++) {
            if (c.contains(elements[i])) elements[j++] = elements[i];
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

    T& front() {
        return elements[0];
    }
    const T & front() const {
        return elements[0];
    }
    
    T& back() {
        return elements[elementCount - 1];
    }

    const T & back() const {
        return elements[elementCount - 1];
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
            if (Equals((*this)[i], t)) {
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

    Vector<T> & operator=(const Vector<T> & rhs) const {
        delete elements;
        elements = Array<T>(rhs.elements.length);
        capacityIncrease = rhs.capacityIncrease;
        elementCount = rhs.elementCount;
        arraycopy(rhs.elements, 0, elements, 0, rhs.elements.length);
        return *this;
    }
private:
    std::size_t elementCount;
    std::size_t capacityIncrease;
    Array<T> elements;

    void ensureCapacity(std::size_t capacity) {
        if (capacity <= elements->length) return;
        std::size_t newsize;
        if (capacityIncrease == 0) newsize = elements->length * 2;
        else newsize = elements->length + capacityIncrease;
        Array<T> oldElements = elements;
        elements = Array<T>(newsize);
        arraycopy(oldElements, 0, elements, 0, oldElements.length);
        delete oldElements;
    }
};

SYLPH_END_NAMESPACE
#endif	/* VECTOR_H_ */

