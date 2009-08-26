#include <cppunit/extensions/HelperMacros.h>
#include <Sylph/Core/String.h>

using namespace Sylph;

class TestString : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestString);
    CPPUNIT_TEST_SUITE_END();
public:

    void setUp() { }

    void tearDown() { }

    void testFromAscii() {
        String s = "foobar";
        Array<uchar> a = s.utf16();
        CPPUNIT_ASSERT(a[0] == 'f');
        CPPUNIT_ASSERT(a[1] == 'o');
        CPPUNIT_ASSERT(a[2] == 'o');
        CPPUNIT_ASSERT(a[3] == 'b');
        CPPUNIT_ASSERT(a[4] == 'a');
        CPPUNIT_ASSERT(a[5] == 'r');
    }

    void testFromUtf8() {
        String s = "éèçàŒù£";
        Array<uchar> a = s.utf16();
        CPPUNIT_ASSERT(a[0] == 0x0000);
        CPPUNIT_ASSERT(a[0] == 0x0000);
        CPPUNIT_ASSERT(a[0] == 0x0000);
        CPPUNIT_ASSERT(a[0] == 0x0000);
        CPPUNIT_ASSERT(a[0] == 0x0000);
        CPPUNIT_ASSERT(a[0] == 0x0000);
        CPPUNIT_ASSERT(a[0] == 0x0000);
        CPPUNIT_ASSERT(a[0] == 0x0000);
        CPPUNIT_ASSERT(a[7] == 0xF8FF);
    }

    void testRealEquality() {
        String s = "foobar";
        String t = "foobar";
        String u = "barfoo";
        CPPUNIT_ASSERT(s == t);
        CPPUNIT_ASSERT(t == s);
        CPPUNIT_ASSERT(s != u);
        CPPUNIT_ASSERT(u != s);
        CPPUNIT_ASSERT(t != u);
        CPPUNIT_ASSERT(u != t);
    }

    void testUnicodeRealEquality() {
        String s = "éèçàŒù£";
        String t = "éèçàŒù£";
        String u = "Œù£éèçà";
        CPPUNIT_ASSERT(s == t);
        CPPUNIT_ASSERT(t == s);
        CPPUNIT_ASSERT(s != u);
        CPPUNIT_ASSERT(u != s);
        CPPUNIT_ASSERT(t != u);
        CPPUNIT_ASSERT(u != t);
    }

    void testCopyEquality() {
        String s = "foobar";
        String t = s.copy();
        CPPUNIT_ASSERT(s == t);
        CPPUNIT_ASSERT(t == s);
    }

    void testUnicodeCopyEquality() {
        String s = "éèçàŒù£";
        String t = s.copy();
        CPPUNIT_ASSERT(s == t);
        CPPUNIT_ASSERT(t == s);
    }

    void testRefcountEquality() {
        String s = "foobar";
        String t = s;
        CPPUNIT_ASSERT(s == t);
        CPPUNIT_ASSERT(t == s);
    }

    void testSelfEquality() { 
        String s = "foobar";
        CPPUNIT_ASSERT(s == s);
    }

    void testUnicodeSelfEquality() {
        String s = "éèçàŒù£";
        CPPUNIT_ASSERT(s == s);
    }

    void testBoolConstructor() {
        String s = true;
        CPPUNIT_ASSERT(s == "true");
        String t = false;
        CPPUNIT_ASSERT(t == "false");
    }

    void testIntConstructor() {
        String s = 12345678;
        CPPUNIT_ASSERT(s == "12345678");
        String t = 12345678901234LL;
        CPPUNIT_ASSERT(t == "12345678901234");
    }

    void testFloatConstructor() {
        String s = 3.14f;
        CPPUNIT_ASSERT(s == "3.14");
        String t = 3.14;
        CPPUNIT_ASSERT(t == "3.14");
    }

    void testLength() {
        String s = "foobar";
        CPPUNIT_ASSERT(s.length() == 6);
        String t = "éèçàŒù£";
        CPPUNIT_ASSERT(t.length() == 8);
    }

    void testCharAt() {
        String s = "foobar";
        CPPUNIT_ASSERT(s.at(0) == 'f');
        CPPUNIT_ASSERT(s.at(1) == 'o');
        CPPUNIT_ASSERT(s.at(2) == 'o');
        CPPUNIT_ASSERT(s.at(3) == 'b');
        CPPUNIT_ASSERT(s.at(4) == 'a');
        CPPUNIT_ASSERT(s.at(5) == 'r');
    }

    void testUnicodeCharAt() {
        String s = "éèçàŒù£";
        CPPUNIT_ASSERT(s.at(0) == 0x0000);
        CPPUNIT_ASSERT(s.at(1) == 0x0000);
        CPPUNIT_ASSERT(s.at(2) == 0x0000);
        CPPUNIT_ASSERT(s.at(3) == 0x0000);
        CPPUNIT_ASSERT(s.at(4) == 0x0000);
        CPPUNIT_ASSERT(s.at(5) == 0x0000);
        CPPUNIT_ASSERT(s.at(6) == 0x0000);
        CPPUNIT_ASSERT(s.at(7) == 0xF8FF);
    }

    void testInvalidUnicode() {
        char invalid[] = {};
        String s = invalid;
        //2do
    }

    void testAstralPlaneUnicode() {
        char astral[] = {};
        String s = astral;
        //2do
    }

    void testToAscii() { }

    void testToUtf8() { }

    void testLowerCase() { }

    void testUpperCase() { }

    void testEqualsIgnoreCase() { }

    void testContainment() { }

    void testTrim() { }

    void testSubstring() { }

    void testIndexOf() { }

    void testMerge() { }

    void testHashUniqueness() { }

    void testToBool() { }

    void testToInt() { }

    void testToFloat() { }

    void testEmptynessBool() { }

    void testAppend() { }

    void testMultiply() { }

    void testInvoke() { }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestString);