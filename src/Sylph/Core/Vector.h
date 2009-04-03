/*
 * File:   vector.h
 * Author: frank
 *
 * Created on 6 december 2008, 12:07
 */

#ifndef VECTOR_H_
#define	VECTOR_H_

#include "Object.h"
#include "Collection.h"

#include <vector>
#include <initializer_list>

SYLPH_BEGIN_NAMESPACE

SYLPH_PUBLIC
template<class T>
class Array;

template<class T>
class Vector : public virtual Collection<T> {
public:
    typedef T Type;
    
public:
    explicit Vector(std::size_t initialCount = 16, std::size_t increase = 0);
    Vector(const std::vector<T> & orig);
    Vector(const Array<T> & orig);
    Vector(const Vector<T> & orig);
    Vector(const std::initializer_list<T> & orig);

    virtual ~Vector();

    void push(const T & t);
    T pop();
    T & get(std::size_t idx);
    const T & get(std::size_t idx) const;
    void set(std::size_t idx, const T & t);
    void trim();

    bool add(const T & t);
    bool addAll(const Collection<T> & c);
    void clear();
    bool contains(const T & t) const;
    bool containsAll(const Collection<T> & c) const;
    bool operator ==(const Collection<T> & c) const;
    Vector<T> * deepCopy() const;

    int hashCode() const;
    bool empty() const;
    void remove(T & t);
    void removeAt(std::size_t idx);
    bool removeAll(const Collection<T> & c);
    bool retainAll(const Collection<T> & c);
    std::size_t size() const;
    const Array<T> toArray() const;

    const T & front() const;
    const T & back() const;
    int indexOf(const T & t, std::size_t idx = 0) const;
    int lastIndexOf(const T & t, std::size_t idx = elementCount) const;

    Iterator<T> iterator() const;
    MutableIterator<T> mutableIterator();

    T & operator[](std::size_t idx) { return get(idx); }
    const T & operator[](std::size_t idx) const { return get(idx); }
    Vector & operator=(const Vector & rhs) const;
private:
    std::size_t capacity;
    std::size_t elementCount;
    std::size_t capacityIncrease;
    Array<T> * elements;

    void ensureCapacity(std::size_t capacity);
};

SYLPH_END_NAMESPACE
#endif	/* VECTOR_H_ */

