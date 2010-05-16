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
#include "Util.h"
#include "Equals.h"
#include "Iterator.h"

#include <vector>
#include <initializer_list>

SYLPH_BEGIN_NAMESPACE

SYLPH_PUBLIC

/**
 * @todo Write documentation!
 */
template<class T>
class Vector : public Object {
public:
    class iterator : public RandomAccessIterator<T, iterator> {
    public:
        typedef RandomAccessIterator<T, iterator> super;

        iterator(bool begin = false, Vector<T>* obj = NULL)
        : super(begin), _obj(obj) {
            _currentIndex = begin ? 0 : _obj->size()-1;
        }

        iterator(bool begin = false, const Vector<T>* obj = NULL)
        : super(begin), _obj(const_cast<Vector<T>*> (obj)) {
            _currentIndex = begin ? 0 : _obj->size()-1;
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
            return _currentIndex < _obj->size()-1;
        }

        void next() const {
            _currentIndex++;
        }

        bool hasPrevious() const {
            return _currentIndex > 0;
        }

        void previous() const {
            _currentIndex--;
        }

        idx_t currentIndex() const {
            return _currentIndex;
        }

        size_t length() const {
            return _obj->size()-1;
        }
    private:
        mutable idx_t _currentIndex;
        Vector<T>* _obj;
    };
    S_ITERABLE(T)


   explicit Vector(std::size_t initialCount = 16) :
        elements((std::size_t)initialCount), currentcapacity((std::size_t)initialCount) {
    }

    virtual ~Vector() {}

    void add(const T & t) {
        ensureCapacity(currentsize + 1);
	currentsize++;
        set(currentsize-1, t);        
    }

    void addAll(Vector<T> & c) {
        for (Vector<int>::iterator it = c.begin();
                it != c.end(); ++it) {
                add(*it);
        }
    }

    std::size_t capacity() const {
        return currentcapacity;
    }

    void clear() {
        currentcapacity = 0;
        currentsize = 0;
        elements.clear();
    }

    bool contains(const T & t) {
         return indexOf(t) != -1;
    }	

    bool empty() {
        return currentsize == 0;
    }

    const T & get(std::size_t idx) const {
        checkIfOutOfBounds(idx);
        return elements[idx];
    }

   T & get(std::size_t idx) {
       checkIfOutOfBounds(idx);
       return elements[idx];
    }

    sidx_t indexOf(const T & t, std::idx_t idx = 0) {
        static Equals<T> equf;
        for (std::size_t i = idx; i < currentsize; i++) {
	  if (equf(get(i), t)) {
                return i;
            }
        }
        return -1;
    }

    int lastIndexOf(const T & t) {
        return lastIndexOf(t, currentsize-1);
    }

    sidx_t lastIndexOf(const T & t, std::size_t idx) {
        static Equals<T> equf;
        checkIfOutOfBounds(idx);
        for (std::size_t i = idx; i >= 0; i--) {
	  if (equf(get(i), t)) {
                return i;
            }
        }
        return -1;
    }

    void remove(const T & t) {
        removeAt(indexOf(t));
    }

    void removeAt(std::size_t idx) {
        currentcapacity--;
        currentsize--;
        if (idx < currentcapacity)
            arraycopy(elements, idx + 1, elements, idx,
                currentcapacity - idx);
    }

    void set(std::size_t idx, const T & t) {
        checkIfOutOfBounds(idx);
        elements[idx] = t;
    }

   std::size_t size() const {
        return currentsize;
    }

    Array<T> toArray() const {
        return elements;
    }

    bool operator==(const Vector<T> & c) {
        if (c == NULL) return false;
	else if (currentcapacity != c->capacity()) return false; 
        else if (currentsize != c->size()) return false; 
	else {
	   for (std::size_t x = 0; x < c->size(); x++) {
	      if (get(x) != c->get(x)) return false;
            }
            return true;
        }
    }

    T & operator[](std::idx_t idx) {
        return get(idx);
    }

    const T & operator[](std::idx_t idx) const {
        return get(idx);
    }

   void operator=(const Vector<T> & rhs) {
        elements = Array<T>(rhs.elements.length);
        currentcapacity = rhs.capacity();
        currentsize = rhs.size();
        arraycopy(rhs.elements, 0, elements, 0, rhs.elements.length);
    }

private:
    std::size_t currentcapacity;
    std::size_t currentsize;
    Array<T> elements;

    void ensureCapacity(std::size_t capacity) {
        if (capacity > elements.length) {
            std::size_t newsize;
            newsize = elements.length * 2;
            currentcapacity = newsize;
            Array<T> oldElements = elements;
            elements = Array<T>(newsize);
            arraycopy(oldElements, 0, elements, 0, oldElements.length);
        }
    }

    void checkIfOutOfBounds(std::size_t idx) {
         if (idx >= currentsize) sthrow(ArrayException, "Vector out of bounds");
    }

};



SYLPH_END_NAMESPACE
#endif	/* VECTOR_H_ */
