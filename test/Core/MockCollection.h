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
 */

#ifndef SYLPHTEST_CORE_MOCKCOLLECTION_H_
#define SYLPHTEST_CORE_MOCKCOLLECTION_H_

#include <Sylph/Core/Collection.h>
#include <Sylph/Core/Tuple.h>
#include <Sylph/Core/Range.h>

namespace Mock {

    using Sylph::Tuple;
    using Sylph::range;

    template<class T>
    class Iterator {

    };

    template<class T>
    class Collection {
    public:
        typedef Mock::Iterator<T> iterator;
        typedef Mock::Iterator<T> const_iterator;
        typedef Mock::Iterator<T> Iterator;
        typedef Mock::Iterator<T> ConstIterator;

        typedef T Type;
        typedef T& Reference;
        typedef const T& ConstReference;
        typedef T* Pointer;
        typedef const T* ConstPointer;
    public:
        Collection();
        Collection(const Collection<T>&);
        Collection(std::initializer_list<T>);
        Collection(Collection<T>&&);
        Collection(ConstIterator, ConstIterator);
        Collection(const Tuple<ConstIterator,ConstIterator>&);
        virtual ~Collection();

        Iterator begin();
        Iterator end();
        ConstIterator begin() const;
        ConstIterator end() const;
        ConstIterator cbegin() const;
        ConstIterator cend() const;

        bool contains(const T&) const;
        template<template<class> class C>
        auto containsAll(const C<T>&) const ->
                S_ENABLE_IF(bool, S_TRAIT(IsCollection, C));
        bool containsAll(ConstIterator, ConstIterator) const;
        bool containsAll(const Tuple<ConstIterator, ConstIterator>&) const;
        bool containsAll(std::initializer_list<T>);

        Iterator find(const T&);
        Iterator find(const T&, ConstIterator);
        Iterator findLast(const T&);
        Iterator findLast(const T&, ConstIterator);

        ConstIterator find(const T&) const;
        ConstIterator find(const T&, ConstIterator) const;
        ConstIterator findLast(const T&) const;
        ConstIterator findLast(const T&, ConstIterator) const;

        size_t size() const;
        bool empty() const; 

        Collection<T>& operator=(const Collection<T>& other);
        Collection<T>& operator=(Collection<T>&&);
        Collection<T>& operator=(const Tuple<ConstIterator, ConstIterator>&);
        Collection<T>& operator=(std::initializer_list<T>);

        bool operator==(const Collection<T>&) const;
        bool operator!=(const Collection<T>&) const;
        bool operator<=(const Collection<T>&) const;
        bool operator>=(const Collection<T>&) const;
        bool operator<(const Collection<T>&) const;
        bool operator>(const Collection<T>&) const;
    };

    template<class T>
    class SequentialCollection : public Collection<T> {
    public:
        typedef Mock::Iterator<T> reverse_iterator;
        typedef Mock::Iterator<T> const_reverse_iterator;
        typedef Mock::Iterator<T> ReverseIterator;
        typedef Mock::Iterator<T> ConstReverseIterator;
    public:
        ReverseIterator rbegin();
        ReverseIterator rend();
        ConstReverseIterator rbegin() const;
        ConstReverseIterator rend() const;
        ConstReverseIterator crbegin() const;
        ConstReverseIterator crend() const;
    };

    template<class T>
    class ExpandableCollection : public Collection<T> {
    public:
        bool add(const T&);
        bool add(T&&);
        template<class... A>
        bool emplace(A&&...);

        bool remove(const T&);
        void removeAt(typename Collection<T>::ConstIterator);
        void removeBetween(typename Collection<T>::ConstIterator,
                typename Collection<T>::ConstIterator);
        void removeBetween(const Tuple<typename Collection<T>::ConstIterator,
                typename Collection<T>::ConstIterator>&);

        size_t addAll(const Collection<T>&);
        size_t retainAll(const Collection<T>&);
        size_t removeAll(const Collection<T>&);

        template<template<class> class C>
        auto addAll(const C<T>&) -> 
                S_ENABLE_IF(void, S_TRAIT(IsCollection, C));
        void addAll(typename Collection<T>::ConstIterator, 
                typename Collection<T>::ConstIterator);
        void addAll(const Tuple<
                typename Collection<T>::ConstIterator, 
                typename Collection<T>::ConstIterator>&);
        void addAll(std::initializer_list<T>);

        template<template<class> class C>
        auto retainAll(const C<T>&) -> 
                S_ENABLE_IF(void, S_TRAIT(IsCollection, C));
        void retainAll(typename Collection<T>::ConstIterator, 
                typename Collection<T>::ConstIterator);
        void retainAll(const Tuple<
                typename Collection<T>::ConstIterator, 
                typename Collection<T>::ConstIterator>&);
        void retainAll(std::initializer_list<T>);

        template<template<class> class C>
        auto removeAll(const C<T>&) -> 
                S_ENABLE_IF(void, S_TRAIT(IsCollection, C));
        void removeAll(typename Collection<T>::ConstIterator, 
                typename Collection<T>::ConstIterator);
        void removeAll(const Tuple<
                typename Collection<T>::ConstIterator, 
                typename Collection<T>::ConstIterator>&);
        void removeAll(std::initializer_list<T>);

        void clear();

        ExpandableCollection<T>& operator+=(const T& t);
        ExpandableCollection<T>& operator+=(const Collection<T>& t);
        ExpandableCollection<T>& operator+=(const Tuple<
                typename Collection<T>::ConstIterator,
                typename Collection<T>::ConstIterator>&);
        ExpandableCollection<T>& operator+=(std::initializer_list<T>);

        ExpandableCollection<T>& operator<<(const T& t);
        ExpandableCollection<T>& operator<<(const Collection<T>& t);
        ExpandableCollection<T>& operator<<(const Tuple<
                typename Collection<T>::ConstIterator,
                typename Collection<T>::ConstIterator>&);
        ExpandableCollection<T>& operator<<(std::initializer_list<T>);

    };

    template<class T>
    class ExpandableSequence : public SequentialCollection<T>, 
            public ExpandableCollection<T> {
    public:
        const T& peekFront() const;
        T& peekFront();
        T popFront();
        void pushFront(const T&);

        const T& peekBack() const;
        T& peekBack();
        T popBack();
        void pushBack(const T&);

        void append(const T&);
        void prepend(const T&);

        template<template<class> class C>
        auto appendAll(const C<T>&) -> 
                S_ENABLE_IF(void, S_TRAIT(IsCollection, C));
        void appendAll(typename Collection<T>::ConstIterator, 
                typename Collection<T>::ConstIterator);
        void appendAll(const Tuple<
                typename Collection<T>::ConstIterator, 
                typename Collection<T>::ConstIterator>&);
        void appendAll(std::initializer_list<T>);

        template<template<class> class C>
        auto prependAll(const C<T>&) -> 
                S_ENABLE_IF(void, S_TRAIT(IsCollection, C));
        void prependAll(typename Collection<T>::ConstIterator, 
                typename Collection<T>::ConstIterator);
        void prependAll(const Tuple<
                typename Collection<T>::ConstIterator, 
                typename Collection<T>::ConstIterator>&);
        void prependAll(std::initializer_list<T>);
        
        const T& first() const;
        const T& last() const;
        T& first();
        T& last();

        void insert(typename Collection<T>::ConstIterator, const T&);
        template<template<class> class C>
        auto insertAll(typename Collection<T>::ConstIterator,
                const C<T>&) ->
                S_ENABLE_IF(void, S_TRAIT(IsCollection, C));
        void insertAll(typename Collection<T>::ConstIterator,
                typename Collection<T>::ConstIterator, 
                typename Collection<T>::ConstIterator);
        void insertAll(typename Collection<T>::ConstIterator, const Tuple<
                typename Collection<T>::ConstIterator, 
                typename Collection<T>::ConstIterator>&);
        void insertAll(typename Collection<T>::ConstIterator,
                std::initializer_list<T>);

        template<class... A>
        void emplace(typename Collection<T>::ConstIterator, A&&... a);
        template<class... A>
        void emplaceFront(A&&... a);
        template<class... A>
        void emplaceBack(A&&... a);
    };

    template<class T>
    class RandomAccessCollection : public SequentialCollection<T> {
    public:
        T& operator[](idx_t);
        const T& operator[](idx_t) const;
        T& operator[](range);
        const T& operator[](range) const;

        sidx_t indexOf(const T&, idx_t) const;
        sidx_t lastIndexOf(const T&, idx_t) const;
    };

    template<class T>
    class ExpandableRandomAccessCollection : public ExpandableSequence<T>,
            public RandomAccessCollection<T> {
    public:
        void removeAt(sidx_t);
        void removeBetween(sidx_t, sidx_t);
        void removeBetween(range);

        void insert(sidx_t, const T&);
        template<template<class> class C>
        auto insertAll(sidx_t, const C<T>&) ->
                S_ENABLE_IF(void, S_TRAIT(IsCollection, C)); 
        void insertAll(sidx_t, typename Collection<T>::ConstIterator,
                typename Collection<T>::ConstIterator);
        void insertAll(sidx_t, const Tuple<
                typename Collection<T>::ConstIterator,
                typename Collection<T>::ConstIterator>&);
        void insertAll(sidx_t,
                std::initializer_list<T>);

        template<class... A>
        void emplace(sidx_t, A&&... a);
    };

    template<class T>
    class ArrayBackedCollection : public Collection<T> {
    public:
        size_t capacity() const;
        void resize(size_t);
        void reserve(size_t);
        void fit(size_t);
    };
}

S_BEGIN_TRAITS
S_SET_TRAIT(IsCollection, Mock::Collection);
S_SET_TRAIT(IsCollection, Mock::SequentialCollection);
S_SET_TRAIT(IsCollection, Mock::ExpandableCollection);
S_SET_TRAIT(IsCollection, Mock::ExpandableSequence);
S_SET_TRAIT(IsCollection, Mock::RandomAccessCollection);
S_SET_TRAIT(IsCollection, Mock::ExpandableRandomAccessCollection);
S_SET_TRAIT(IsCollection, Mock::ArrayBackedCollection);

S_SET_TRAIT(IsSequentialCollection, Mock::SequentialCollection);
S_SET_TRAIT(IsSequentialCollection, Mock::ExpandableSequence);
S_SET_TRAIT(IsSequentialCollection, Mock::RandomAccessCollection);
S_SET_TRAIT(IsSequentialCollection, Mock::ExpandableRandomAccessCollection);

S_SET_TRAIT(IsExpandableCollection, Mock::ExpandableCollection);
S_SET_TRAIT(IsExpandableCollection, Mock::ExpandableSequence);
S_SET_TRAIT(IsExpandableCollection, Mock::RandomAccessCollection);
S_SET_TRAIT(IsExpandableCollection, Mock::ExpandableRandomAccessCollection);

S_SET_TRAIT(IsExpandableSequence, Mock::ExpandableSequence);
S_SET_TRAIT(IsExpandableSequence, Mock::ExpandableRandomAccessCollection);

S_SET_TRAIT(IsRandomAccessCollection, Mock::RandomAccessCollection);
S_SET_TRAIT(IsRandomAccessCollection, Mock::ExpandableRandomAccessCollection);

S_SET_TRAIT(IsExpandableRandomAccessCollection, 
        Mock::ExpandableRandomAccessCollection);

template<class T>
S_SET_TRAIT_TPL(IsArrayBacked, Mock::ArrayBackedCollection<T>);
S_END_TRAITS

#endif /* SYLPHTEST_CORE_MOCKCOLLECTION_H_ */

// vim: ts=4:sts=4:sw=4:sta:et:tw=80:nobk:pa+=,../../src
