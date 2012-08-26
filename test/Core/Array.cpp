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
 */

#include "../SylphTest.h"
#include "Collection.h"

#include <Sylph/Core/Array.h>
#include <Sylph/Core/Util.h>
#include <Sylph/Core/Debug.h>

using namespace Sylph;

struct Dummy {
};

namespace {

    class TestArray : public ::testing::Test {
    protected:

        virtual void SetUp() {
            testObj1 = new Array<int>((size_t) 5);
            testObj2 = new Array<Dummy > (4);
            ar1 = new Array<int>((size_t) 4);
            ar2 = new Array<int>((size_t) 4);
            ar3 = new Array<int>((size_t) 7);
            arfilled1 = {5, 2, 9, 1, 7};
            arfilled2 = {8, 0, 2, 3, 4, 6};
            arfilled3 = {8, 0, 2, 3, 4, 6};
        }

        virtual void TearDown() {
            delete testObj1;
            delete testObj2;
            delete ar1;
            delete ar2;
            delete ar3;
        }
        Array<int> * testObj1;
        Array<Dummy> * testObj2;
        Array<int> * ar1;
        Array<int> * ar2;            
        Array<int> * ar3;
        Array<int> arfilled1;
        Array<int> arfilled2;
        Array<int> arfilled3;
    };

    TEST_IS_COLLECTION(Array);
    TEST_IS_SEQ_COLLECTION(Array);
    TEST_IS_RANDOM_ACCESS_COLLECTION(Array);
    TEST_IS_EFFICIENT_FRONT_RETRIEVABLE(Array);
    TEST_IS_EFFICIENT_MIDDLE_RETRIEVABLE(Array);
    TEST_IS_EFFICIENT_BACK_RETRIEVABLE(Array);

    TEST_F(TestArray, testCorrectConstructed) {
        EXPECT_EQ(5u, testObj1->length);
        EXPECT_EQ(4u, testObj2->length);
        EXPECT_EQ(4u, ar1->length);
        EXPECT_EQ(4u, ar2->length);
        EXPECT_EQ(7u, ar3->length);
        EXPECT_EQ(5u, arfilled1.length);
        EXPECT_EQ(6u, arfilled2.length);
        EXPECT_EQ(6u, arfilled3.length);
    }

    TEST_F(TestArray, testNulled) {
        EXPECT_EQ(0, (*testObj1)[0]);
        EXPECT_EQ(0, (*testObj1)[1]);
        EXPECT_EQ(0, (*testObj1)[2]);
        EXPECT_EQ(0, (*testObj1)[3]);
        EXPECT_EQ(0, (*testObj1)[4]);
    }

    TEST_F(TestArray, testInEqOut) {
        // first
        (*testObj1)[0] = 3;
        EXPECT_EQ(3, (*testObj1)[0]);
        // last
        (*testObj1)[4] = 7;
        EXPECT_EQ(7, (*testObj1)[4]);
        // middle
        (*testObj1)[2] = 2;
        EXPECT_EQ(2, (*testObj1)[2]);
    }

    TEST_F(TestArray, testInitlistFill) {
        ASSERT_EQ(5u, arfilled1.length);
        EXPECT_EQ(5, arfilled1[0]);
        EXPECT_EQ(2, arfilled1[1]);
        EXPECT_EQ(9, arfilled1[2]);
        EXPECT_EQ(1, arfilled1[3]);
        EXPECT_EQ(7, arfilled1[4]);
    }

    TEST_F(TestArray, testOverflow) {
        ASSERT_THROW((*testObj1)[7] = 1, IndexException);
    }

    TEST_F(TestArray, testLength) {
        Array<bool> lengthtest((size_t) 6);
        ASSERT_EQ(6u, lengthtest.length);
    }

    TEST_F(TestArray, testLengthOverflow) {
        Array<bool> lengthtest((size_t) 6);
        ASSERT_THROW(lengthtest[6] = false, IndexException);
    }

    TEST_F(TestArray, testSelfEquality) {
        ASSERT_EQ(*ar1, *ar1);
    }

    TEST_F(TestArray, testEmptyEquality) {
        EXPECT_TRUE(*ar1 == *ar2);
        EXPECT_FALSE(*ar1 == *ar3);
    }

    TEST_F(TestArray, testRealEquality) {
        EXPECT_TRUE(arfilled3 == arfilled2);
        EXPECT_TRUE(arfilled3 != arfilled1);
    }

    TEST_F(TestArray, testComparisons) {
        Array<char> ar4 = {'h', 'e', 'l', 'l', 'o'};
        Array<char> ar5 = {'h', 'e', 'l', 'm', 'e', 't'};
        EXPECT_TRUE(ar4 < ar5);
        EXPECT_FALSE(ar5 < ar4);
    }

    TEST_F(TestArray, testCopyEquality) {
        Array<int> arcopy = arfilled1.copy();
        EXPECT_TRUE(arfilled1 == arcopy);
    }

    TEST_F(TestArray, testArrayCopy) {
        Array<int> arcopy((size_t)6u);
        arraycopy(arfilled2,2,arcopy,3,2);
        EXPECT_EQ(0,arcopy[0]);
        EXPECT_EQ(0,arcopy[1]);
        EXPECT_EQ(0,arcopy[2]);
        EXPECT_EQ(2,arcopy[3]);
        EXPECT_EQ(3,arcopy[4]);
        EXPECT_EQ(0,arcopy[5]);
    }

    TEST_F(TestArray, testIterator) {
        idx_t cur = 0;

        for (Array<int>::iterator it = arfilled1.begin();
                it != arfilled1.end(); ++it) {
            EXPECT_EQ(*it, arfilled1[cur]);
            cur++;
        }
    }

    TEST_F(TestArray, testReverseIterator) {
        idx_t cur = arfilled1.length - 1;

        for(Array<int>::reverse_iterator it = arfilled1.rbegin();
                it != arfilled1.rend(); ++it) {
            EXPECT_EQ(*it,arfilled1[cur]);
            cur--;
        }
    }

    TEST_F(TestArray, testNegativeIndices) {
        EXPECT_EQ(7, arfilled1[-1]);
        EXPECT_EQ(1, arfilled1[-2]);
        EXPECT_EQ(arfilled1[0], arfilled1[-arfilled1.length]);
    }

    TEST_F(TestArray, testNegativeOverflow) {
        ASSERT_THROW(arfilled1[-(arfilled1.length + 1)] = 3, IndexException);
    }

    TEST_F(TestArray, testRange) {
        Array<int> section = arfilled2[range(2, 4)];
        ASSERT_EQ(3u, section.length);
        EXPECT_EQ(2, section[0]);
        EXPECT_EQ(3, section[1]);
        EXPECT_EQ(4, section[2]);
    }

    TEST_F(TestArray, testNegativeRange) {
        Array<int> section = arfilled1[range(1,-1)];
        ASSERT_EQ(4u, section.length);
        EXPECT_EQ(2, section[0]);
        EXPECT_EQ(9, section[1]);
        EXPECT_EQ(1, section[2]);
        EXPECT_EQ(7, section[3]);
    }

    TEST_F(TestArray, testInvertedRange) {
        ASSERT_THROW(arfilled1[range(3,2)], IndexException);
    }

    TEST_F(TestArray, testInvertedNegativeRange) {
        ASSERT_THROW(arfilled1[range(-2,-3)], IndexException);
    }

    TEST_F(TestArray, testInvertedDifferentlySignedRange) {
        ASSERT_THROW(arfilled1[range(-1,1)], IndexException);
    }

    TEST_F(TestArray, testInvalidRange) {
        ASSERT_THROW(arfilled1[range(3,6)], IndexException);
    }

    TEST_F(TestArray, testInvalidNegativeRange) {
        ASSERT_THROW(arfilled1[range(-2,-7)], IndexException);
    }

    TEST_F(TestArray, testRefcounted) {
        Array<int> tmp = arfilled1;
        ASSERT_EQ(arfilled1.carray(), tmp.carray());
    }

    TEST_F(TestArray, testShift) {
        Array<int> tmp = arfilled1.copy();
        EXPECT_EQ(5, shift(tmp));
        EXPECT_EQ(4u, tmp.length);
        EXPECT_EQ(A_(2,9,1,7), tmp);
    }

} // namespace

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk:pa+=,../../src
