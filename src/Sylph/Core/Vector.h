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

SYLPH_START_NAMESPACE(Core)

SYLPH_PUBLIC
template<typename T>
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
    bool addAll(Collection<T> & c);
    void clear();
    bool contains(T & t) const;
    bool containsAll(Collection<T> & c) const;
    bool operator ==(Collection<T> & c) const;
    Vector<T> * deepCopy() const;

    int hashCode() const;
    bool empty() const;
    void remove(T & t);
    void removeAt(std::size_t idx);
    bool removeAll(Collection<T> & c);
    bool retainAll(Collection<T> & c);
    std::size_t size() const;
    const Array<T> toArray() const;

    T & front();
    T & back();
    int indexOf(T & t, std::size_t idx = 0);
    int lastIndexOf(T & t, std::size_t idx = elementCount);

    Iterator<T> iterator() const;
    MutableIterator<T> mutableIterator();

    T & operator[](std::size_t idx) { return get(idx); }
    const T & operator[](std::size_t idx) const { return get(idx); }
private:
    std::size_t capacity;
    std::size_t elementCount;
    std::size_t capacityIncrease;
    Array<T> * elements;

    void ensureCapacity(std::size_t capacity);
};

SYLPH_END_NAMESPACE(Core)
#endif	/* VECTOR_H_ */

