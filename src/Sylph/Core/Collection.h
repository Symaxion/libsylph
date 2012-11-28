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
 *  Created on: 3 jan. 2011
 */

#ifndef SYLPH_CORE_COLLECTION_H_
#define SYLPH_CORE_COLLECTION_H_

#include "Object.h"
#include "Traits.h"
#include "Primitives.h"
#include <initializer_list>

SYLPH_BEGIN_NAMESPACE

namespace Traits {
    // Collection related

    /**
     * Operations supported:
     * begin/end: iterator
     * cbegin/cend: iterator
     * contains(T)
     * containsAll(Collection)
     * containsAll(iterator, iterator)
     * find(T [,iterator])
     * findLast(T [,iterator])
     * size()
     * empty(): size() == 0
     *
     * Constructors:
     * Default constructor
     * Copy constructor
     * Initializer-list constructor
     * Move constructor
     *
     * Operators:
     * Assignment
     * Move assignment
     * operator+ (joining)
     * operator| (T, Collection): contains (global implementation)
     * operator| (Collection, Collection): containsAll (global implementation)
     *
     * Operations depending on T:
     * operator==
     * operator!=
     * operator<
     * other comparison operators
     */
    template<template<class...> class T>
    struct IsCollection : public FalseType {
    };

    /**
     * Traits:
     * IsCollection
     *
     * Operations supported:
     * rbegin/rend: iterator
     * crbegin/crend: iterator
     */
    template<template<class...> class T>
    struct IsSequentialCollection : public FalseType {
    };

    /**
     * Traits:
     * IsCollection
     *
     * Operations supported:
     * add(T): ensures element is in collection
     * emplace(T): like add, but in-place construction
     * remove(T)
     * removeAt(iterator)
     * removeAt(iterator, iterator)
     * addAll(Collection<T>)
     * addAll(iterator, iterator)
     * removeAll(Collection<T>)
     * removeAll(iterator, iterator)
     * retainAll(Collection<T>)
     * retainAll(iterator, iterator)
     * clear()
     * operator+=
     * operator<<
     */
    template<template<class...> class T>
    struct IsExpandableCollection : public FalseType {
    };

    /**
     * Traits:
     * Sequential and Expandable
     *
     * Operations supported:
     * peekFront()
     * pushFront(T)
     * popFront()
     * peekBack()
     * pushBack(T)
     * popBack()
     *
     * append(T)
     * prepend(T)
     * appendAll(Collection<T>)
     * prependAll(Collection<T>)
     * first()
     * last()
     *
     * insert(iterator,T)
     * emplace(iterator,A...)
     * emplaceBack(A...)
     * emplaceFront(A...)
     */
    template<template<class...> class T>
    struct IsExpandableSequence : public And<IsSequentialCollection<T>::value,
            IsExpandableCollection<T>::value> {
    };

    /**
     * Traits:
     * IsSequentialCollection
     *
     * RandomAccessIterator available
     * operator[](idx_t)
     * indexOf(T[,idx_t])
     * lastIndexOf(T[,idx_t])
     */
    template<template<class...> class T>
    struct IsRandomAccessCollection : public FalseType {
    };

    /**
     * Traits:
     * IsExpandableSequence
     * IsRandomAccessCollection
     *
     * insert(idx_t,T)
     * removeAt(idx_t)
     * emplace(idx_t,A...)
     */
    template<template<class...> class T>
    struct IsExpandableRandomAccessCollection :
            public And<IsExpandableSequence<T>::value,
            IsRandomAccessCollection<T>::value> {
    };

    /**
     * FIXME: might not be really suited for Collection.h, as it can be applied
     * to streams and other stuff. Move this to Array.h?
     *
     * size()
     * capacity()
     * resize(size_t)
     * reserve(size_t) -> resize(size() + size_t)
     * fit(size_t) -> resize(size())
     */
    template<class T>
    struct IsArrayBacked : public FalseType {
    };

    template<template<class...> class T>
    struct IsEfficientFrontInsertable : public FalseType {
    };

    template<template<class...> class T>
    struct IsEfficientMiddleInsertable : public FalseType {
    };

    template<template<class...> class T>
    struct IsEfficientBackInsertable : public FalseType {
    };

    template<template<class...> class T>
    struct IsEfficientFrontRetrievable : public FalseType {
    };

    template<template<class...> class T>
    struct IsEfficientMiddleRetrievable : public FalseType {
    };

    template<template<class...> class T>
    struct IsEfficientBackRetrievable : public FalseType {
    };

    /**
     * Traits:
     * IsCollection
     */
    template<template<class...> class T>
    struct IsUniqueElementCollection : public FalseType {
    };
}

// Functions

/**
 * Alias for Collection::contains().
 *
 * This operator is a shorthand for the contains() operation provided by every
 * collection. So, instead of writing
 * <pre>
 *      if(c.contains(t)) // ...
 * </pre>
 * one could write:
 * <pre>
 *      if(t|c) // Read: "if t in c"
 * </pre>
 */
template<class T, template<class> class C>
auto operator|(const T& t, const C<T>& c) -> 
        S_ENABLE_IF(bool, S_TRAIT(IsCollection, C)) {
    return c.contains(t);
}

 /**
 * Alias for Collection::containAlls().
 *
 * This operator is a shorthand for the containsAll() operation provided by every
 * collection. So, instead of writing
 * <pre>
 *      if(c.containsAll(c)) // ...
 * </pre>
 * one could write:
 * <pre>
 *      if(c2|c) // Read: "if c2 in c"
 * </pre>
 */
template<template<class> class C, template<class> class C2, class T>
auto operator|(const C2<T>& c2, const C<T>& c) -> 
        S_ENABLE_IF(bool, S_AND(
                    S_TRAIT(IsCollection, C),
                    S_TRAIT(IsCollection, C2))) {
    return c.containsAll(c2);
}

SYLPH_END_NAMESPACE

#endif /* SYLPH_CORE_COLLECTION_H_ */

// vim: ts=4:sts=4:sw=4:sta:et:tw=80:nobk
