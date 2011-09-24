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
 */

#include "SylphTest.h"
#include <Sylph/Core/Function.h>
#include <Sylph/Core/Debug.h>

#include <Sylph/Core/String.h>

using namespace Sylph;

namespace {

    int add3(int i) {
        return i + 3;
    }

    int square(int i) {
        return i*i;
    }

    class TestFunction : public ::testing::Test {
    };

    TEST_F(TestFunction, testMap) {
        Array<int> a = {1,2,3};
        Array<int> result = map(Op::inc<int&>)(a);
        Array<int> expected = {2,3,4};
        EXPECT_EQ(expected,result);
    }

    TEST_F(TestFunction, testChain) {
        auto squareplus3 = chain(add3, square);
        for(int i = -10; i <= 10; ++i) {
            EXPECT_EQ(add3(square(i)), squareplus3(i));
        }
    }

    TEST_F(TestFunction, testInvoke) {
        auto endsWithFoo = invoke(&String::endsWith, (String)"foo");
        String s = "foo";
        String t = "myfoo";
        String u = "foobar";

        EXPECT_TRUE(endsWithFoo(s));
        EXPECT_TRUE(endsWithFoo(t));
        EXPECT_FALSE(endsWithFoo(u));
    }

    TEST_F(TestFunction, testForAll) {
        Array<int> a = { 1, 4, 2, 4, 7 };
        function<bool(int)> lt9 = bind(Op::lst<int,int>,P::_1,9);
        EXPECT_TRUE(forall(a,lt9));
    }

    TEST_F(TestFunction, testForAllNegative) {
        Array<int> a = { 1, 4, 2, 4, 7 };
        function<bool(int)> lt7 = bind(Op::lst<int,int>,P::_1,7);
        EXPECT_FALSE(forall(a,lt7));
    }

    TEST_F(TestFunction, testForAny) {
        Array<int> a = { 1, 4, 2, 4, 7 };
        function<bool(int)> mt5 = bind(Op::grt<int,int>,P::_1,5);
        EXPECT_TRUE(forany(a,mt5));
    }

    TEST_F(TestFunction, testForAnyNegative) {
        Array<int> a = { 1, 4, 2, 4, 7 };
        function<bool(int)> mt9 = bind(Op::grt<int,int>,P::_1,9);
        EXPECT_FALSE(forany(a,mt9));
    }

    TEST_F(TestFunction, testCall) {
        int i = call(square,3);
        EXPECT_EQ(9,i);
    }
}
