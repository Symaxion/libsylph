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
 *  Created on: 3 jan. 2011
 */

#ifndef SYLPH_CORE_COLLECTION_H_
#define SYLPH_CORE_COLLECTION_H_

#include "Object.h"
#include "Traits.h"
#include "Function.h"
#include "Primitives.h"

SYLPH_BEGIN_NAMESPACE

namespace Traits {
    // Collection related

    /**
     * Operations supported:
     * begin/end: iterator
     * contains(T)
     * indexOf(T[,idx_t])
     * lastIndexOf(T[,idx_t])
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
     *
     * Operations depending on T:
     * operator==
     * operator!=
     * operator<
     * other comparison operators
     */
    template<class T>
    struct IsCollection : public FalseType {
    };

    /**
     * Traits:
     * IsCollection
     *
     * Operations supported:
     * operator[](idx_t)
     * rbegin/rend: iterator
     */
    template<class T>
    struct IsSequentialCollection : public FalseType {
    };

    /**
     * Traits:
     * IsCollection
     *
     * Operations supported:
     * add(T): ensures element is in collection
     * remove(T)
     * removeAt(iterator)
     * addAll(Collection<T>)
     * removeAll(Collection<T>)
     * clear()
     * operator+=
     * operator<<
     */
    template<class T>
    struct IsExpandableCollection : public FalseType {
    };

    /**
     * Traits:
     * Sequential and Expandable
     *
     * Operations supported:
     * peekFront(T)
     * pushFront(T)
     * popFront(T)
     * peekBack(T)
     * pushBack(T)
     * popBack(T)
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
    template<class T>
    struct IsExpandableSequence : public And<IsSequentialCollection<T>::value,
    IsExpandableCollection<T>::value> {
    };

    /**
     * Traits:
     * IsSequentialCollection
     *
     * RandomAccessIterator available
     * insert(idx_t,T)
     * removeAt(idx_t)
     * emplace(idx_t,A...)
     */
    template<class T>
    struct IsRandomAccessCollection : public FalseType {
    };

    template<class T>
    struct IsEfficientFrontInsertable : public FalseType {
    };

    template<class T>
    struct IsEfficientMiddleInsertable : public FalseType {
    };

    template<class T>
    struct IsEfficientBackInsertable : public FalseType {
    };

    template<class T>
    struct IsEfficientFrontRetrievable : public FalseType {
    };

    template<class T>
    struct IsEfficientMiddleRetrievable : public FalseType {
    };

    template<class T>
    struct IsEfficientBackRetrievable : public FalseType {
    };

    /**
     * Traits:
     * IsCollection
     */
     template<class T>
     struct IsUniqueElementCollection : public FalseType {
     };
}

// Functions

SYLPH_END_NAMESPACE

#endif /* SYLPH_CORE_COLLECTION_H_ */
