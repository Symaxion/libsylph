#include "SylphTest.h"
#include <Sylph/Core/Array.h>
#include <Sylph/Core/Debug.h>
#include <iostream>
#include <Sylph/Core/Vector.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace Sylph;

namespace {

    class TestVector : public ::testing::Test {
    };

    TEST_F(TestVector, testcapacity) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
        EXPECT_EQ(5, testObj1->capacity());
        delete testObj1;
    }

    TEST_F(TestVector, testOverflow) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
        ASSERT_THROW((*testObj1)[7] = 1, ArrayException);
        delete testObj1;
    }   

    TEST_F(TestVector, testCapacityIncrease) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
        testObj1->add(7);
        EXPECT_EQ(5, testObj1->capacity());
        delete testObj1;
    }

    TEST_F(TestVector, testAdd) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
        testObj1->add(7);
	testObj1->add(5);
        EXPECT_EQ(7,(*testObj1)[0]);
	EXPECT_EQ(5,(*testObj1)[1]);
        delete testObj1;
    }

    TEST_F(TestVector, testSize) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
 	testObj1->add(7);
	testObj1->add(5); 
	testObj1->add(3);
	testObj1->add(4);
	testObj1->add(7);
	EXPECT_EQ(5, testObj1->size());
        delete testObj1;
    }	

    TEST_F(TestVector, testAddLargeAmountOfnumbers) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
	for (std::size_t x =0; x < 1000; x++) {
	    testObj1->add(x);		
	    EXPECT_EQ(x,(*testObj1)[x]);	
	}
        delete testObj1;
    }	

    TEST_F(TestVector, testAddLargeAmountofRandomNumbers) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
	
	/* initialize random seed: */
  	srand ( time(NULL) );

	for (std::size_t x =0; x < 1000; x++) {
	    int randomnumber = rand() % 10 + 1;
	    testObj1->add(randomnumber);		
	    EXPECT_EQ(randomnumber,(*testObj1)[x]);	
	}
	EXPECT_EQ(1000, testObj1->size());
        delete testObj1;
    }			

    TEST_F(TestVector, testGet) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
        testObj1->add(7);
	testObj1->add(5);
        EXPECT_EQ(7,testObj1->get(0));
	EXPECT_EQ(5,testObj1->get(1));
        delete testObj1;
    }

    TEST_F(TestVector, testBracketAssignment) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
        testObj1->add(7);
	(*testObj1)[0] = 5; 
        EXPECT_EQ(5,testObj1->get(0));
        delete testObj1;
    }

    TEST_F(TestVector, testGetAssignment) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
        testObj1->add(7);
	testObj1->get(0) = 5; 
        EXPECT_EQ(5,testObj1->get(0));
        delete testObj1;
    }

    TEST_F(TestVector, testEmpty) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
	ASSERT_TRUE(testObj1->empty());
        testObj1->add(7); 
        ASSERT_FALSE(testObj1->empty());
	testObj1->clear();
       	ASSERT_TRUE(testObj1->empty());
        delete testObj1;
    }

   TEST_F(TestVector, testContains) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
        testObj1->add(7);
	ASSERT_TRUE(testObj1->contains(7));
        delete testObj1;
    }

   TEST_F(TestVector, testIndexOf) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
        testObj1->add(7);
	testObj1->add(5); 
	EXPECT_EQ(1, testObj1->indexOf(5));
        delete testObj1;
    }	
 
   TEST_F(TestVector, testLastIndexOfNoStartIndex) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
        testObj1->add(7);
	testObj1->add(5); 
	testObj1->add(3);
	testObj1->add(4);
	testObj1->add(7);
	EXPECT_EQ(4, testObj1->lastIndexOf(7));
	EXPECT_EQ(2, testObj1->lastIndexOf(3));	        
	delete testObj1;
    }		

    TEST_F(TestVector, testLastIndexOfStartIndex) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
        testObj1->add(7);
	testObj1->add(5); 
	testObj1->add(3);
	testObj1->add(4);
	testObj1->add(7);
	EXPECT_EQ(0, testObj1->lastIndexOf(7,3));      
	delete testObj1;
    }
 
    TEST_F(TestVector, testRemove) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
        testObj1->add(7);
	testObj1->add(5); 
	testObj1->add(3);
	testObj1->add(4);
	testObj1->add(7);
	testObj1->remove(3);
	EXPECT_EQ(4,  testObj1->size());      	
	EXPECT_EQ(4, testObj1->get(2));	
	delete testObj1;
    }	

    TEST_F(TestVector, testRemoveAt) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
        testObj1->add(7);
	testObj1->add(5); 
	testObj1->add(3);
	testObj1->add(4);
	testObj1->add(7);
	testObj1->removeAt(3);
	EXPECT_EQ(4,  testObj1->size());      	
	EXPECT_EQ(7, testObj1->get(3));	
	delete testObj1;
    }		
	
    TEST_F(TestVector, testSelfEquality) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
	
	/* initialize random seed: */
  	srand ( time(NULL) );

	for (std::size_t x =0; x < 1000; x++) {
	    int randomnumber = rand() % 10 + 1;
	    testObj1->add(randomnumber);		
	}
	ASSERT_TRUE(testObj1==testObj1);
        delete testObj1;
    }		 

    TEST_F(TestVector, testDifferentVectors) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
	Vector<int> * testObj2 = new Vector<int>((size_t) 5);
	/* initialize random seed: */
  	srand ( time(NULL) );

	for (std::size_t x =0; x < 1000; x++) {
	    int randomnumber = rand() % 10 + 1;
	    testObj1->add(randomnumber);
            testObj2->add(randomnumber + 1);		
	}

	ASSERT_FALSE(testObj1==testObj2);
	ASSERT_FALSE(testObj1==null); 	        
	delete testObj1;
    }			
	
    TEST_F(TestVector, testEqualityofDifferentCapacityVectors) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
	Vector<int> * testObj2 = new Vector<int>((size_t) 8);
	ASSERT_FALSE(testObj1==testObj2); 	        	

	/* initialize random seed: */
  	srand ( time(NULL) );

	for (std::size_t x =0; x < 1000; x++) {
	    int randomnumber = rand() % 10 + 1;
	    testObj1->add(randomnumber);
            testObj2->add(randomnumber + 1);		
	}

	ASSERT_FALSE(testObj1==testObj2);
	
	delete testObj1;
    }		

   TEST_F(TestVector, testIteratorAtBeginToEnd) {
        idx_t cur = 0;
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
	for (std::size_t x =0; x < 1000; x++) {
	    testObj1->add(x);		
	}

        for (Vector<int>::iterator it = testObj1->begin();
                it != testObj1->end(); ++it) {
                EXPECT_EQ(*it, (*testObj1)[cur]);
                cur++;
        }
	EXPECT_EQ(1000, cur); 
    }		

   TEST_F(TestVector, testIteratorAtEndToBegin) {
        idx_t cur = 999;
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
	for (std::size_t x =0; x < 1000; x++) {
	    testObj1->add(x);		
	}
	Vector<int>::iterator it = testObj1->end();
	it--; 
        for (;it >= testObj1->begin(); --it) {
	      EXPECT_EQ(*it, (*testObj1)[cur]);		 
              cur--;
	      if (it == testObj1->begin()) break;
        }
	EXPECT_EQ(-1, cur); 
    }	

    TEST_F(TestVector, testAddAll) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
	Vector<int> * testObj2 = new Vector<int>((size_t) 5);
	for (std::size_t x =0; x < 2000; x++) {
	  if (x <= 1000) {
	    testObj1->add(x);	
	  }
	  else {
	    testObj2->add(x);
	  }
	}
  
	testObj1->addAll((*testObj2));
	EXPECT_EQ(2000, testObj1->size());

	for (std::size_t x = 0; x < 2000; x++) {
	  EXPECT_EQ(x, testObj1->get(x));
	}
    }
  
    TEST_F(TestVector, testSetVectorsEqual) {
        Vector<int> * testObj1 = new Vector<int>((size_t) 5);
	Vector<int> * testObj2 = new Vector<int>((size_t) 5);
	for (std::size_t x =0; x < 2000; x++) {
	  if (x <= 1000) {
	    testObj1->add(x);	
	  }
	  else {
	    testObj2->add(x);
	  }
	}
  
	(*testObj1)=(*testObj2);
	for (std::size_t x = 0; x < 1999; x++) {
	  if (x >= 1000) {
	     EXPECT_EQ(x+1, testObj1->get(x-1000));
	  }
	}
    }
 } 

