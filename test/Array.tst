@.Header:
#include <Sylph/Core/Array.h>

using namespace Sylph;

struct Dummy {};
@.End

@.SetUp:
        testObj1 = new Array<int>((size_t)5);
        testObj2 = new Array<Dummy>(4);
        ar1 = new Array<int>((size_t)4);
        ar2 = new Array<int>((size_t)4);
        ar3 = new Array<int>((size_t)7);
        arfilled1 = {5,2,9,1,7};
        arfilled2 = {8,0,2,3,4,6};
        arfilled3 = {8,0,2,3,4,6};
@.End

@.TearDown:
        delete testObj1;
        delete testObj2;
        delete ar1;
        delete ar2;
        delete ar3;
@.End

@testCorrectConstructed:
        CPPUNIT_ASSERT(testObj1->length == 5);
        CPPUNIT_ASSERT(testObj2->length == 4);
        CPPUNIT_ASSERT(ar1->length == 4);
        CPPUNIT_ASSERT(ar2->length == 4);
        CPPUNIT_ASSERT(ar3->length == 7);
        CPPUNIT_ASSERT(arfilled1.length == 5);
        CPPUNIT_ASSERT(arfilled2.length == 6);
        CPPUNIT_ASSERT(arfilled3.length == 6);
@.End

@testNulled:
        CPPUNIT_ASSERT((*testObj1)[0] == 0);
        CPPUNIT_ASSERT((*testObj1)[1] == 0);
        CPPUNIT_ASSERT((*testObj1)[2] == 0);
        CPPUNIT_ASSERT((*testObj1)[3] == 0);
        CPPUNIT_ASSERT((*testObj1)[4] == 0);
@.End

@testInEqOut:
        // first
        (*testObj1)[0] = 3;
        CPPUNIT_ASSERT((*testObj1)[0] == 3);
        // last
        (*testObj1)[4] = 7;
        CPPUNIT_ASSERT((*testObj1)[4] == 7);
        // middle
        (*testObj1)[2] = 2;
        CPPUNIT_ASSERT((*testObj1)[2] == 2);
@.End

@testInitlistFill:
        CPPUNIT_ASSERT(arfilled1.length == 5);
        CPPUNIT_ASSERT(arfilled1[0] == 5);
        CPPUNIT_ASSERT(arfilled1[1] == 2);
        CPPUNIT_ASSERT(arfilled1[2] == 9);
        CPPUNIT_ASSERT(arfilled1[3] == 1);
        CPPUNIT_ASSERT(arfilled1[4] == 7);
@.End

@testOverflow: throw(ArrayException)
        (*testObj1)[7] = 1;
@.End

@testLength:
        Array<bool> lengthtest((size_t)6);
        CPPUNIT_ASSERT(lengthtest.length == 6);
@.End

@testLengthOverflow: throw(ArrayException)
        Array<bool> lengthtest((size_t)6);
        lengthtest[6] = 3;
@.End

@testSelfEquality:
        CPPUNIT_ASSERT(*ar1 == *ar1);
@.End

@testEmptyEquality:
        CPPUNIT_ASSERT(*ar1 == *ar2);
        CPPUNIT_ASSERT(!(*ar1 == *ar3));
@.End

@testRealEquality:
        CPPUNIT_ASSERT(arfilled3 == arfilled2);
        CPPUNIT_ASSERT(arfilled3 != arfilled1);
@.End

@testComparisons:
        Array<char> ar4 = {'h','e','l','l','o'};
        Array<char> ar5 = {'h','e','l','m','e','t'};
        CPPUNIT_ASSERT(ar4 < ar5);
        CPPUNIT_ASSERT(!(ar5 < ar4));
@.End

@testCopyEquality:
        Array<int> arcopy = arfilled1.copy();
        CPPUNIT_ASSERT(arfilled1 == arcopy);
@.End

@testIterator:
        idx_t cur = 0;
        for(Array<int>::iterator it = arfilled1.begin();
                it != arfilled1.end(); ++it) {
                    CPPUNIT_ASSERT(arfilled1[cur] == *it);
                    cur++;
                }
@.End

@testNegativeIndices:
        CPPUNIT_ASSERT(arfilled1[-1] == 7);
        CPPUNIT_ASSERT(arfilled1[-2] == 1);
        //CPPUNIT_ASSERT(arfilled1[-arfilled1.length] == arfilled1[0]);
@.End

@testNegativeOverflow: throw(ArrayException)
        arfilled1[-(arfilled1.length+1)] = 3;
@.End

@testRanges:
        Array<int> section = arfilled2[range(2,4)];
        CPPUNIT_ASSERT(section.length == 3);
        CPPUNIT_ASSERT(section[0] == 2);
        CPPUNIT_ASSERT(section[1] == 3);
        CPPUNIT_ASSERT(section[2] == 4);
@.End

@testRefcounted:
        Array<int> tmp = arfilled1;
        CPPUNIT_ASSERT(tmp.carray() == arfilled1.carray());
@.End

@.Vars:
    Array<int> * testObj1;
    Array<Dummy> * testObj2;
    Array<int> * ar1;
    Array<int> * ar2;
    Array<int> * ar3;
    Array<int> arfilled1;
    Array<int> arfilled2;
    Array<int> arfilled3;
@.End
