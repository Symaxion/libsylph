/*
 * LibSylph Class Library
 * Copyright (C) 2012 Frank "SeySayux" Erens <seysayux@gmail.com>
 * Copyright (C) 2010 Scott "ernieballsep" Philbrook <ernieballsep@gmail.com>
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
#include <Sylph/Core/Array.h>
#include <Sylph/Core/Debug.h>
#include <Sylph/Core/Vector.h>

#include <iterator>
#include <time.h>

using namespace Sylph;

namespace {

    class TestVector : public ::testing::Test {
    };

    TEST_F(TestVector, testCapacity) {
        Vector<int> testObj1((size_t) 5);
        EXPECT_EQ(5u, testObj1.capacity());
    }

    TEST_F(TestVector, testOverflowCapacity) {
        Vector<int> testObj1((size_t) 5);
        EXPECT_THROW(testObj1[7] = 1, ArrayException);
    }
    TEST_F(TestVector, testOverflowSize) {
        Vector<int> testObj1((size_t) 5);
        testObj1.add(1); testObj1.add(2); testObj1.add(3);
        EXPECT_THROW(testObj1[3] = 1, ArrayException);
    }

    TEST_F(TestVector, testCapacityIncreaseCondition) {
        Vector<int> testObj1((size_t) 5);
        testObj1.add(7);
        EXPECT_EQ(5u, testObj1.capacity());

        Vector<int> testObj2((size_t) 1);
        EXPECT_NO_THROW({
            testObj2.add(1); testObj2.add(1);
        });
        EXPECT_EQ(2u, testObj2.capacity());
    }

    TEST_F(TestVector, testAdd) {
        Vector<int> testObj1((size_t) 5);
        testObj1.add(7);
	    testObj1.add(5);
        EXPECT_EQ(7,testObj1[0]);
        EXPECT_EQ(5,testObj1[1]);
    }

    TEST_F(TestVector, testSize) {
        Vector<int> testObj1((size_t) 5);
        testObj1.add(7);
        testObj1.add(5);
        testObj1.add(3);
        testObj1.add(4);
        EXPECT_EQ(4u, testObj1.size());
    }	

    TEST_F(TestVector, testAddLargeAmountOfNumbers) {
        Vector<int> testObj1((size_t) 5);
        for(idx_t x =0; x < 1000; x++) {
            testObj1.add(x);
            EXPECT_EQ((signed)x,testObj1[x]);	
        }
    }	

    TEST_F(TestVector, testAddLargeAmountofRandomNumbers) {
        Vector<int> testObj1((size_t) 5);
	
        // initialize random seed:
        srand(time(null));

        for(idx_t x = 0; x < 1000; x++) {
            int randomnumber = rand() % 10 + 1;
            testObj1.add(randomnumber);
            EXPECT_EQ(randomnumber, testObj1[x]);
        }

        EXPECT_EQ(1000u, testObj1.size());
    }			

    TEST_F(TestVector, testGet) {
        Vector<int> testObj1((size_t) 5);
        testObj1.add(7);
        testObj1.add(5);
        EXPECT_EQ(7,testObj1.get(0));
        EXPECT_EQ(5,testObj1.get(1));
    }

    TEST_F(TestVector, testBracketAssignment) {
        Vector<int> testObj1((size_t) 5);
        testObj1.add(7);
        testObj1[0] = 5; 
        EXPECT_EQ(5,testObj1.get(0));
    }

    TEST_F(TestVector, testGetAssignment) {
        Vector<int> testObj1((size_t) 5);
        testObj1.add(7);
        testObj1.get(0) = 5;
        EXPECT_EQ(5,testObj1.get(0));
    }

    TEST_F(TestVector, testEmpty) {
        Vector<int> testObj1((size_t) 5);
        ASSERT_TRUE(testObj1.empty());
        testObj1.add(7);
        ASSERT_FALSE(testObj1.empty());
        testObj1.clear();
       	ASSERT_TRUE(testObj1.empty());
    }

    TEST_F(TestVector, testContains) {
        Vector<int> testObj1((size_t) 5);
        testObj1.add(7);
        ASSERT_TRUE(testObj1.contains(7));
    }

    TEST_F(TestVector, testIndexOf) {
        Vector<int> testObj1((size_t) 5);
        testObj1.add(7);
        testObj1.add(5);
        EXPECT_EQ(1, testObj1.indexOf(5));
    }	
 
   TEST_F(TestVector, testLastIndexOfNoStartIndex) {
        Vector<int> testObj1((size_t) 5);
        testObj1.add(7);
        testObj1.add(5);
        testObj1.add(3);
        testObj1.add(4);
        testObj1.add(7);
        EXPECT_EQ(4, testObj1.lastIndexOf(7));
        EXPECT_EQ(2, testObj1.lastIndexOf(3));
    }		

    TEST_F(TestVector, testLastIndexOfStartIndex) {
        Vector<int> testObj1((size_t) 5);
        testObj1.add(7);
        testObj1.add(5);
        testObj1.add(3);
        testObj1.add(4);
        testObj1.add(7);
        EXPECT_EQ(0, testObj1.lastIndexOf(7,3));
    }
 
    TEST_F(TestVector, testRemove) {
        Vector<int> testObj1((size_t) 5);
        testObj1.add(7);
        testObj1.add(5);
        testObj1.add(3);
        testObj1.add(4);
        testObj1.add(7);
        testObj1.remove(3);
        EXPECT_EQ(4u, testObj1.size());
        EXPECT_EQ(4, testObj1.get(2));
    }	

    TEST_F(TestVector, testRemoveAt) {
        Vector<int> testObj1((size_t) 5);
        testObj1.add(7);
        testObj1.add(5);
        testObj1.add(3);
        testObj1.add(4);
        testObj1.add(7);
        testObj1.removeAt(3);
        EXPECT_EQ(4u, testObj1.size());
        EXPECT_EQ(7, testObj1.get(3));
    }		
	
    TEST_F(TestVector, testSelfEquality) {
        Vector<int> testObj1((size_t) 5);
	
        // initialize random seed:
        srand(time(null));

        for(idx_t x = 0; x < 1000; x++) {
            int randomnumber = rand() % 10 + 1;
            testObj1.add(randomnumber);
        }

        ASSERT_TRUE(testObj1 == testObj1);
    }		 

    TEST_F(TestVector, testDifferentVectors) {
        Vector<int> testObj1((size_t) 5);
        Vector<int> testObj2((size_t) 5);

        // initialize random seed: 
  	    srand(time(null));

        for(std::size_t x = 0; x < 1000; x++) {
            int randomnumber = rand() % 10 + 1;
            testObj1.add(randomnumber);
            testObj2.add(randomnumber + 1);
        }

        EXPECT_FALSE(testObj1 == testObj2);
        EXPECT_FALSE(testObj2 == testObj1);
    }			
	
    TEST_F(TestVector, testCapacityEquality) {
        Vector<int> testObj1((size_t) 5);
	    Vector<int> testObj2((size_t) 8);
	    ASSERT_TRUE(testObj1 == testObj2);
    }		

    TEST_F(TestVector, testIterator) {
        idx_t cur = 0;
        Vector<int> testObj1((size_t) 5);
        for(idx_t x = 0; x < 1000; x++) {
            testObj1.add(x);
        }

        for(Vector<int>::iterator it = testObj1.begin();
                it != testObj1.end(); ++it) {
            EXPECT_EQ(*it, testObj1[cur]);
            cur++;
        }

        EXPECT_EQ(1000u, cur); 
    }		

    TEST_F(TestVector, testReverseIterator) {
        idx_t cur = 1000u;
        Vector<int> testObj1 ((size_t) 5);
        for(std::size_t x = 0; x < 1000; x++) {
            testObj1.add(x);
        }

        typedef Vector<int>::reverse_iterator reverse_iterator;

        for(reverse_iterator it = testObj1.rbegin();
                it != testObj1.rend(); ++it) {
            cur--;
            EXPECT_EQ(testObj1[cur],*it);
        }
        EXPECT_EQ(0u, cur);
    }	

    TEST_F(TestVector, testAddAll) {
        Vector<int> testObj1((size_t) 5);
        Vector<int> testObj2((size_t) 5);

        for(idx_t x = 0; x < 2000; x++) {
            if(x <= 1000) {
                testObj1.add(x);
            } else {
                testObj2.add(x);
            }
        }
  
        testObj1.addAll(testObj2);
        ASSERT_EQ(2000u, testObj1.size());

        for(idx_t x = 0; x < 2000; x++) {
            EXPECT_EQ((signed)x, testObj1.get(x));
        }
    }
  
    TEST_F(TestVector, testAssign) {
        Vector<int> testObj1((size_t) 5);
        Vector<int> testObj2((size_t) 5);
        for(idx_t x = 0; x < 2000; x++) {
            if(x < 1000) {
                testObj1.add(x);
            } else {
                testObj2.add(x);
            }
        }
  
        testObj1=testObj2;
	    for (idx_t x = 1000; x < 2000; x++) {
            EXPECT_EQ((signed)x, testObj1.get(x-1000));
        }

    }

} // namespace

