@.Header:
#include <Sylph/Core/String.h>

// for strcmp
#include <cstring>

using namespace Sylph;
@.End

@.SetUp:
@.End

@.TearDown:
@.End

@testFromAscii:
        String s = "foobar";
        Array<uchar> a = s.utf16();
        CPPUNIT_ASSERT(a[0] == 'f');
        CPPUNIT_ASSERT(a[1] == 'o');
        CPPUNIT_ASSERT(a[2] == 'o');
        CPPUNIT_ASSERT(a[3] == 'b');
        CPPUNIT_ASSERT(a[4] == 'a');
        CPPUNIT_ASSERT(a[5] == 'r');
@.End

@testFromUtf8:
        String s = "éèçàŒù£";
        Array<uchar> a = s.utf16();
        CPPUNIT_ASSERT(a[0] == 0x00E9);
        CPPUNIT_ASSERT(a[1] == 0x00E8);
        CPPUNIT_ASSERT(a[2] == 0x00E7);
        CPPUNIT_ASSERT(a[3] == 0x00E0);
        CPPUNIT_ASSERT(a[4] == 0x008C);
        CPPUNIT_ASSERT(a[5] == 0x00F9);
        CPPUNIT_ASSERT(a[6] == 0x00A3);
        CPPUNIT_ASSERT(a[7] == 0xF8FF);
@.End

@testRealEquality:
        String s = "foobar";
        String t = "foobar";
        String u = "barfoo";
        CPPUNIT_ASSERT(s == t);
        CPPUNIT_ASSERT(t == s);
        CPPUNIT_ASSERT(s != u);
        CPPUNIT_ASSERT(u != s);
        CPPUNIT_ASSERT(t != u);
        CPPUNIT_ASSERT(u != t);
@.End

@testUnicodeRealEquality:
        String s = "éèçàŒù£";
        String t = "éèçàŒù£";
        String u = "Œù£éèçà";
        CPPUNIT_ASSERT(s == t);
        CPPUNIT_ASSERT(t == s);
        CPPUNIT_ASSERT(s != u);
        CPPUNIT_ASSERT(u != s);
        CPPUNIT_ASSERT(t != u);
        CPPUNIT_ASSERT(u != t);
@.End

@testCopyEquality:
        String s = "foobar";
        String t = s.copy();
        CPPUNIT_ASSERT(s == t);
        CPPUNIT_ASSERT(t == s);
@.End

@testUnicodeCopyEquality:
        String s = "éèçàŒù£";
        String t = s.copy();
        CPPUNIT_ASSERT(s == t);
        CPPUNIT_ASSERT(t == s);
@.End

@testRefcountEquality:
        String s = "foobar";
        String t = s;
        CPPUNIT_ASSERT(s == t);
        CPPUNIT_ASSERT(t == s);
@.End

@testSelfEquality:
        String s = "foobar";
        CPPUNIT_ASSERT(s == s);
@.End

@testUnicodeSelfEquality:
        String s = "éèçàŒù£";
        CPPUNIT_ASSERT(s == s);
@.End

@testBoolConstructor:
        String s = true;
        CPPUNIT_ASSERT(s == "true");
        String t = false;
        CPPUNIT_ASSERT(t == "false");
@.End

@testIntConstructor:
        String s = 12345678;
        CPPUNIT_ASSERT(s == "12345678");
        String t = 12345678901234LL;
        CPPUNIT_ASSERT(t == "12345678901234");
@.End

@testFloatConstructor:
        String s = 3.14f;
        CPPUNIT_ASSERT(s == "3.14");
        String t = 3.14;
        CPPUNIT_ASSERT(t == "3.14");
@.End

@testLength:
        String s = "foobar";
        CPPUNIT_ASSERT(s.length() == 6);
        String t = "éèçàŒù£";
        CPPUNIT_ASSERT(t.length() == 8);
@.End

@testCharAt:
        String s = "foobar";
        CPPUNIT_ASSERT(s.at(0) == 'f');
        CPPUNIT_ASSERT(s.at(1) == 'o');
        CPPUNIT_ASSERT(s.at(2) == 'o');
        CPPUNIT_ASSERT(s.at(3) == 'b');
        CPPUNIT_ASSERT(s.at(4) == 'a');
        CPPUNIT_ASSERT(s.at(5) == 'r');
@.End

@testUnicodeCharAt:
        String s = "éèçàŒù£";
        CPPUNIT_ASSERT(s.at(0) == 0x00E9);
        CPPUNIT_ASSERT(s.at(1) == 0x00E8);
        CPPUNIT_ASSERT(s.at(2) == 0x00E7);
        CPPUNIT_ASSERT(s.at(3) == 0x00E0);
        CPPUNIT_ASSERT(s.at(4) == 0x008C);
        CPPUNIT_ASSERT(s.at(5) == 0x00F9);
        CPPUNIT_ASSERT(s.at(6) == 0x00A3);
        CPPUNIT_ASSERT(s.at(7) == 0xF8FF);
@.End

@testInvalidUnicode:
        char invalid[] = {};
        String s = invalid;
        //2do
@.End

@testAstralPlaneUnicode:
        char astral[] = {};
        String s = astral;
        //2do
@.End

@testToAscii:
        String s = "foobar";
        const char * c = s.ascii();
        CPPUNIT_ASSERT(std::strcmp(c,"foobar") == 0);
        String t = "français";
        const char * c2 = t.ascii();
        CPPUNIT_ASSERT(std::strcmp(c,"fran?ais") == 0);
@.End

@testToUtf8:
        String s = "foobar";
        const char * c = s.utf8();
        CPPUNIT_ASSERT(std::strcmp(c,"foobar") == 0);
        String t = "français";
        const char * c2 = t.utf8();
        CPPUNIT_ASSERT(std::strcmp(c,"français") == 0);
@.End

@testLowerCase:
        String s = "foo";
        CPPUNIT_ASSERT(s.toLowerCase() == "foo");
        s = "FoO";
        CPPUNIT_ASSERT(s.toLowerCase() == "foo");
        s = "FoX";
        CPPUNIT_ASSERT(!(s.toLowerCase() == "foo"));
@.End

@testUpperCase:
        String s = "FOO";
        CPPUNIT_ASSERT(s.toUpperCase() == "FOO");
        s = "fOO";
        CPPUNIT_ASSERT(s.toUpperCase() == "FOO");
        s = "FoX";
        CPPUNIT_ASSERT(!(s.toUpperCase() == "foo"));
@.End

@testEqualsIgnoreCase:
    String s = "foo";
    String t = "FOO";
    CPPUNIT_ASSERT(s.equalsIgnoreCase(s));
    CPPUNIT_ASSERT(s.equalsIgnoreCase(t));
    CPPUNIT_ASSERT(t.equalsIgnoreCase(t));
    CPPUNIT_ASSERT(t.equalsIgnoreCase(s));
    CPPUNIT_ASSERT(!s.equalsIgnoreCase("Fox"));
    CPPUNIT_ASSERT(!t.equalsIgnoreCase("Fox"));
@.End

@testContainment:
@.End

@testTrim:
@.End

@testSubstring:
@.End

@testIndexOf:
@.End

@testMerge:
@.End

@testHashUniqueness:
@.End

@testToBool:
        String s = "true";
        CPPUNIT_ASSERT(s.boolValue());
        s = "TrUe";
        CPPUNIT_ASSERT(s.boolValue());
        s = "";
        CPPUNIT_ASSERT(!s.boolValue());
        s = "false";
        CPPUNIT_ASSERT(!s.boolValue());
        s = "ololol";
        CPPUNIT_ASSERT(!s.boolValue());
        s = "ééé";
        CPPUNIT_ASSERT(!s.boolValue());
@.End

@testToInt:
        String a = "123";
        CPPUNIT_ASSERT(a.intValue() == 123);
        String b = "-123";
        CPPUNIT_ASSERT(b.intValue() == -123);
        String c = " 333 ";
        CPPUNIT_ASSERT(c.intValue() == 333);
        String d = "foobar";
        CPPUNIT_ASSERT(d.intValue() == 0);
@.End

@testToFloat:
@.End

@testAppend:
        String a = "foo";
        String b = "bar";
        String c = a + b;
        a += b;
        CPPUNIT_ASSERT(a == "foobar");
        CPPUNIT_ASSERT(c == "foobar");
@.End

@testMultiply:
        String s = "-";
        String t = s * 5;
        CPPUNIT_ASSERT(t == "-----");

        String u = "é";
        String v = u * 5;
        CPPUNIT_ASSERT(v == "ééééé");
@.End

@testInvoke:
@.End