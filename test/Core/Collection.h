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
 *  Created on: Jul 27, 2012
 */

#ifndef SYLPHTEST_CORE_COLLECTION_H_
#define SYLPHTEST_CORE_COLLECTION_H_

#include "../SylphTest.h"

#include <Sylph.h>
#include <Sylph/Core/Collection.h>
#include <Sylph/Core/Function.h>

#include <Sylph/OS/GuessCompiler.h>

namespace Sfinae {

    template<template<class> class T>
    void isCollection() {
        sidx_t si;
        size_t s;
        bool b;

        T<int> t1;
        T<int> t2(t1);
        T<int> t3({0,1,2,3});
        T<int> t4(move(t3));
        b = constify(t1).contains(0);
        si = constify(t1).indexOf(0);
        si = constify(t1).indexOf(0, (idx_t)0);
        si = constify(t1).lastIndexOf(0);
        si = constify(t1).lastIndexOf(0, (idx_t)0);
        s = constify(t1).size();
        b = constify(t1).empty();

        t2 = t1;
        t4 = move(t2);

        t2 = t1 + t4;

        b = 3 | t1;

        b = t1 == t2;
        b = t1 != t2;
        b = t1 < t2;

        (void)si;
        (void)s;
        (void)b;
    }
}

#ifndef SYLPH_NO_TEST_COMPILE ////////////////////////

#define TEST_IS_COLLECTION_COMPILE(Class) \
    TEST_F(Test##Class, testIsCollectionCompile) { \
        void(*f)(void) = &Sfinae::isCollection<Class>; \
        (void)f; \
    } \
    SYLPH_END_MACRO 

#else ////////////////////////////////////////////////

#define TEST_IS_COLLECTION_COMPILE(Class) \
    SYLPH_END_MACRO

#endif ///////////////////////////////////////////////

#define TEST_IS_COLLECTION_TRAITS(Class) \
    TEST_F(Test##Class, testIsCollectionTraits) { \
        ASSERT_TRUE(S_TRAIT(IsCollection, Class)); \
    } \
    SYLPH_END_MACRO

//////////////////////////////////////////////////////

#define TEST_IS_COLLECTION_RUNTIME(Class) \
    TEST_F(Test##Class, testIsCollectionRuntime) { \
        SYLPH_STUB_TEST; \
    } \
    SYLPH_END_MACRO

//////////////////////////////////////////////////////

#define TEST_IS_COLLECTION(Class) \
    TEST_IS_COLLECTION_COMPILE(Class); \
    TEST_IS_COLLECTION_TRAITS(Class); \
    TEST_IS_COLLECTION_RUNTIME(Class);

#endif /* SYLPHTEST_CORE_COLLECTION_H_ */

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk:pa+=,../../src
