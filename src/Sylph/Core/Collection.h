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
 * Created on 19 december 2008, 14:29
 */

#ifndef COLLECTION_H_
#define	COLLECTION_H_


#include "Object.h"
#include "Iterator.h"
#include "Hashable.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

/**
 * A Collection represents a group of objects, known as its <i>elements</i>.
 * Some collections allow duplicate elements and others do not. Some are ordered
 * and others unordered. This interface is used to pass around the various
 * Collection classes, such as Vector, and erm... -- well there are more to come
 * -- around with a maximum generality. Most @c Collection s do the same thing
 * (holding data) and the abstraction layer provided here makes dealing with
 * different types of @c Collection s easy.
 * <p>
 * All "destructive" methods (those not marked as @c const ) are allowed to
 * throw an @c UnsupportedOperationException. @c Collection that do not allow
 * @c NULL (0) elements are allowed to throw @c NullPointerException s .
 * @c Collection s that are backed by @c Array s are allowed to throw
 * @c ArrayException s if the underlying @c Array gets an out-of-bounds error.
 */
template<class T>
class Collection : public Hashable {
public:
    /**
     * A function that is used for filtering by the filter() method. This
     * function takes both an instance of the class this Array contains, and
     * a reference to a reference to any kind of other data that may need to
     * be passed to the FilterFunction.
     */
    typedef bool(*FilterFunction)(const T&, Any&);
public:

    virtual bool add(const T & t);
    virtual bool addAll(const Collection<T> & c);
    virtual void clear();
    virtual bool contains(const T & t) const = 0;
    virtual bool containsAll(const Collection<T> & c) const;
    virtual bool operator ==(const Collection<T> & c) const;

    virtual bool operator !=(const Collection<T> & c) const {
        return !(*this == c);
    }
    virtual sint hashCode() const = 0;
    virtual bool empty() const = 0;
    virtual Collection<T> filter(FilterFunction func, Any& clientData) = 0;
    virtual bool remove(const T & t);
    virtual bool removeAll(const Collection<T> & c);
    virtual bool retainAll(const Collection<T> & c);
    virtual std::size_t size() const = 0;
    virtual Array<T> toArray() const = 0;

    operator Array<T>() const {
        return toArray();
    }

    virtual Collection & operator<<(const T& t) { add(t); return *this; }
};
SYLPH_END_NAMESPACE

#endif	/* COLLECTION_H_ */

