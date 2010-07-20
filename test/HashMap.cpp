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
        Array<String> keys(4);
        Array<String> values(4);

        HashMap<String,String> h;
        h["English"] = "English";
        h["French"] = "français";
        h["Spanish"] = "español";
        h["Dutch"] = "Nederlands";

        //ASSERT_NO_THROW({
            idx_t i = 0;
            for(HashMap<String,String>::iterator it = h.begin();
                it != h.end(); ++it) {
                keys[i] = it->key;
                values[i] = *(it->value);
                i++;
            }
        //});

        for(idx_t i = 0; i < 4; i++) {
            EXPECT_EQ(h[keys[i]],values[i]);
        }
    }

    TEST_F(TestHashMap, testEmptyEquality) {
        HashMap<String,String> g;
        HashMap<String,String> h;

        ASSERT_NO_THROW(g == h);
        EXPECT_TRUE(g == h);
    }

    TEST_F(TestHashMap, testLengthEquality) {

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