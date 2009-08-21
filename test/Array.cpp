#include <cppunit/extensions/HelperMacros.h>
#include <Sylph/Core/Array.h>

using namespace Sylph;

struct Dummy {};

class TestArray : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestArray);
CPPUNIT_TEST(testCorrectConstructed);
CPPUNIT_TEST(testNulled);
CPPUNIT_TEST(testInEqOut);
CPPUNIT_TEST(testInitlistFill);
CPPUNIT_TEST_EXCEPTION(testOverflow, ArrayException);
CPPUNIT_TEST(testLength);
CPPUNIT_TEST_EXCEPTION(testLengthOverflow, ArrayException);
CPPUNIT_TEST(testSelfEquality);
CPPUNIT_TEST(testEmptyEquality);
CPPUNIT_TEST(testRealEquality);
CPPUNIT_TEST(testComparisons);
CPPUNIT_TEST(testCopyEquality);
CPPUNIT_TEST(testIterator);
CPPUNIT_TEST(testNegativeIndices);
CPPUNIT_TEST_EXCEPTION(testNegativeOverflow, ArrayException);
CPPUNIT_TEST(testRanges);
CPPUNIT_TEST(testRefcounted);
CPPUNIT_TEST_SUITE_END();
public:
    void setUp() {
        testObj1 = new Array<int>((size_t)5);
        testObj2 = new Array<Dummy>(4);
        ar1 = new Array<int>((size_t)4);
        ar2 = new Array<int>((size_t)4);
        ar3 = new Array<int>((size_t)7);
        arfilled1 = {5,2,9,1,7};
        arfilled2 = {8,0,2,3,4,6};
        arfilled3 = {8,0,2,3,4,6};
    }
    void tearDown() {
        delete testObj1;
        delete testObj2;
        delete ar1;
        delete ar2;
        delete ar3;
    }

    void testCorrectConstructed() {
        CPPUNIT_ASSERT(testObj1->length == 5);
        CPPUNIT_ASSERT(testObj2->length == 4);
        CPPUNIT_ASSERT(ar1->length == 4);
        CPPUNIT_ASSERT(ar2->length == 4);
        CPPUNIT_ASSERT(ar3->length == 7);
        CPPUNIT_ASSERT(arfilled1.length == 5);
        CPPUNIT_ASSERT(arfilled2.length == 6);
        CPPUNIT_ASSERT(arfilled3.length == 6);
    }

    void testNulled() {
        CPPUNIT_ASSERT((*testObj1)[0] == 0);
        CPPUNIT_ASSERT((*testObj1)[1] == 0);
        CPPUNIT_ASSERT((*testObj1)[2] == 0);
        CPPUNIT_ASSERT((*testObj1)[3] == 0);
        CPPUNIT_ASSERT((*testObj1)[4] == 0);
    }

    void testInEqOut() {
        // first
        (*testObj1)[0] = 3;
        CPPUNIT_ASSERT((*testObj1)[0] == 3);
        // last
        (*testObj1)[4] = 7;
        CPPUNIT_ASSERT((*testObj1)[4] == 7);
        // middle
        (*testObj1)[2] = 2;
        CPPUNIT_ASSERT((*testObj1)[2] == 2);
    }

    void testInitlistFill() {
        CPPUNIT_ASSERT(arfilled1.length == 5);
        CPPUNIT_ASSERT(arfilled1[0] == 5);
        CPPUNIT_ASSERT(arfilled1[1] == 2);
        CPPUNIT_ASSERT(arfilled1[2] == 9);
        CPPUNIT_ASSERT(arfilled1[3] == 1);
        CPPUNIT_ASSERT(arfilled1[4] == 7);
    }

    void testOverflow() {
        (*testObj1)[7] = 1;
    }

    void testLength() {
        Array<bool> lengthtest((size_t)6);
        CPPUNIT_ASSERT(lengthtest.length == 6);
    }

    void testLengthOverflow() {
        Array<bool> lengthtest((size_t)6);
        lengthtest[6] = 3;
    }

    void testSelfEquality() {
        CPPUNIT_ASSERT(*ar1 == *ar1);
    }
    void testEmptyEquality() {
        CPPUNIT_ASSERT(*ar1 == *ar2);
        CPPUNIT_ASSERT(!(*ar1 == *ar3));
    }

    void testRealEquality() {
        CPPUNIT_ASSERT(arfilled3 == arfilled2);
        CPPUNIT_ASSERT(arfilled3 != arfilled1);
    }

    void testComparisons() {
        Array<char> ar4 = {'h','e','l','l','o'};
        Array<char> ar5 = {'h','e','l','m','e','t'};
        CPPUNIT_ASSERT(ar4 < ar5);
        CPPUNIT_ASSERT(!(ar5 < ar4));
    }

    void testCopyEquality() {
        Array<int> arcopy = arfilled1.copy();
        CPPUNIT_ASSERT(arfilled1 == arcopy);
    }

    void testIterator() {
        idx_t cur = 0;
        for(Array<int>::iterator it = arfilled1.begin();
                it != arfilled1.end(); ++it) {
                    std::cout << cur;
                    CPPUNIT_ASSERT(arfilled1[cur] == *it);
                    cur++;
                }
    }

    void testNegativeIndices() {
        CPPUNIT_ASSERT(arfilled1[-1] == 7);
        CPPUNIT_ASSERT(arfilled1[-2] == 1);
        //CPPUNIT_ASSERT(arfilled1[-arfilled1.length] == arfilled1[0]);
    }

    void testNegativeOverflow() {
        arfilled1[-(arfilled1.length+1)] = 3;
    }

    void testRanges() {
        Array<int> section = arfilled2[range(2,4)];
        CPPUNIT_ASSERT(section.length == 3);
        CPPUNIT_ASSERT(section[0] == 2);
        CPPUNIT_ASSERT(section[1] == 3);
        CPPUNIT_ASSERT(section[2] == 4);
    }

    void testRefcounted() {
        Array<int> tmp = arfilled1;
        CPPUNIT_ASSERT(tmp.carray() == arfilled1.carray());
    }

private:
    Array<int> * testObj1;
    Array<Dummy> * testObj2;
    Array<int> * ar1;
    Array<int> * ar2;
    Array<int> * ar3;
    Array<int> arfilled1;
    Array<int> arfilled2;
    Array<int> arfilled3;
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestArray );
