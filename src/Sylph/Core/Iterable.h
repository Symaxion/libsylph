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
 * Created on 6 december 2008, 17:15
 */

#ifndef SYLPH_CORE_ITERABLE_H_
#define	SYLPH_CORE_ITERABLE_H_

#include "Object.h"
#include <iterator>

SYLPH_BEGIN_NAMESPACE

SYLPH_END_NAMESPACE

// TODO: move this to a separate header
template<class A>
struct remove_const {
    typedef A type;
};

template<class A>
struct remove_const<const A> {
    typedef A type;
};

template<class A>
struct add_const {
    typedef const A type;
};

template<class A>
struct add_const<const A> {
    typedef const A type;
};

template<class A, class B>
struct move_const {
    typedef typename remove_const<B>::type type;
};

template<class A, class B>
struct move_const<const A, B> {
    typedef typename add_const<B>::type type;
};

template<bool B, class T = void>
struct enable_unless {
    typedef T type;
};

template<class T>
struct enable_unless<true, T> {
};


#define S_ITERATOR sylph__Iterator

#define S_ITERABLE(Class, type) \
public: \
typedef type Type; \
typedef sylph__Iterator<Class,type> iterator; \
typedef sylph__Iterator<const Class,const type> const_iterator; \
\
    virtual iterator begin() { return iterator(true, this); }\
    virtual iterator end() { return iterator(false, this); }\
\
    virtual const_iterator begin() const { return const_iterator(true, this); }\
    virtual const_iterator end() const { return const_iterator(false, this); }

#define S_REVERSE_ITERABLE(Class, type) \
public: \
typedef std::reverse_iterator<iterator> reverse_iterator; \
typedef std::reverse_iterator<const_iterator> \
        const_reverse_iterator; \
\
    virtual reverse_iterator rbegin() { return reverse_iterator(end()); } \
    virtual reverse_iterator rend() { return reverse_iterator(begin()); } \
\
    virtual const_reverse_iterator rbegin() const { \
        return const_reverse_iterator(end()); \
    } \
    virtual const_reverse_iterator rend() const { \
        return const_reverse_iterator(begin()); \
    }

#endif	/* SYLPH_CORE_ITERABLE_H_ */

