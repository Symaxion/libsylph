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
 *  Created on: 12 sep. 2011
 */

#ifndef SYLPH_CORE_LIST_
#define SYLPH_CORE_LIST_

#include "Object.h"
#include "Iterator.h"
#include "Primitives.h"

SYLPH_BEGIN_NAMESPACE

template<class T>
class List {
public:
    struct ListNode {
        ListNode* prev;
        ListNode* next;
        T value;
    };

    template<class C, class V>
    class S_ITERATOR : public BidirectionalIterator<V, S_ITERATOR<C,V> > {
        typedef BidirectionalIterator<V, S_ITERATOR<C,V> > super;
    public:
        S_ITERATOR(bool begin = false, C* obj = null) : super(begin),
                cur(begin? obj->first : obj->last){
        }

        template<class C1, class V1>
        S_ITERATOR(const S_ITERATOR<C1,V1>& other) : cur(other.cur) {}

        template<class C1, class V1>
        bool equals(const S_ITERATOR<C1,V1>& other) const {
            return cur == other.cur;
        }

        typename super::value_type& dereference() {
            return cur->value;
        }

        typename super::const_reference dereference() const {
            return cur->value;
        }

        void next() {
            cur = cur->next;
        }

        bool hasNext() const {
            return cur->next != null;
        }

        void previous() {
            cur = cur->prev;
        }

        bool hasPrevious() const {
            return cur->prev != null;
        }
    public:
        ListNode* cur;
    };

    S_ITERABLE(List,T)
    S_REVERSE_ITERABLE(List,T)

public:
    List() : first(null), last(null) {}
    List(const List& other)

    size_t size() const {
        return _size;
    }

    void append(const T& t) {

    }

    void prepend(const T& t) {

    }

private:
    std::size_t _size;

    ListNode* first;
    ListNode* last;
};
SYLPH_END_NAMESPACE

#endif /* SYLPH_CORE_LIST_ */
