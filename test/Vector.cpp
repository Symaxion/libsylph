#include "SylphTest.h"
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
        // This will be fixed in 0.2
        /*sidx_t cur = 1000;
        Vector<int> testObj1 ((size_t) 5);
        for(std::size_t x = 0; x < 1000; x++) {
            testObj1.add(x);
        }

        typedef std::reverse_iterator<Vector<int>::iterator> reverse_iterator;

        reverse_iterator it(testObj1.end());
        reverse_iterator rend(testObj1.begin());

        for(;it != rend; ++it) {
            EXPECT_EQ(testObj1[cur],*it);
            cur--;
        }
        EXPECT_EQ(-1, cur);*/
        //FAIL() << "Error with reverse_iterator";
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

