#include "SylphTest.h"
#include <Sylph/Core/HashMap.h>
#include <Sylph/Core/Debug.h>

using namespace Sylph;

namespace {
    class TestHashMap : public ::testing::Test {

    };

    TEST_F(TestHashMap, testInEqOut) {
        HashMap<String,String> h;
        h["English"] = "English";
        h["French"] = "français";
        h["Spanish"] = "español";
        h["Dutch"] = "Nederlands";
        ASSERT_EQ(4,h.size());
        EXPECT_EQ(String("English"),h["English"]);
        EXPECT_EQ(String("français"),h["French"]);
        EXPECT_EQ(String("español"),h["Spanish"]);
        EXPECT_EQ(String("Nederlands"),h["Dutch"]);
    }

    TEST_F(TestHashMap, testContainsKey) {
        HashMap<String,String> h;
        h["abc"] = "def";
        EXPECT_TRUE(h.containsKey("abc"));
        EXPECT_FALSE(h.containsKey("def"));
    }

    TEST_F(TestHashMap, testContainsValue) {
        HashMap<String,String> h;
        h["abc"] = "def";
        EXPECT_TRUE(h.containsValue(new String("def")));
        EXPECT_FALSE(h.containsValue(new String("abc")));
    }

    TEST_F(TestHashMap, testClear) {
        HashMap<String,String> h;
        h["English"] = "English";
        h["French"] = "français";
        h["Spanish"] = "español";
        h["Dutch"] = "Nederlands";
        ASSERT_EQ(4,h.size());
        h.clear();
        EXPECT_EQ(0,h.size());
    }

    TEST_F(TestHashMap, testRehash) {
        SYLPH_STUB_TEST;
    }

    TEST_F(TestHashMap, testIterator) {
        SYLPH_STUB_TEST;
    }

    TEST_F(TestHashMap, testEmptyEquality) {
        SYLPH_STUB_TEST;
    }

    TEST_F(TestHashMap, testRealEquality) {
        SYLPH_STUB_TEST;
    }

    TEST_F(TestHashMap, testInequality) {
        SYLPH_STUB_TEST;
    }

    TEST_F(TestHashMap, testSequenceEquality) {
        SYLPH_STUB_TEST;
    }


} // namespace