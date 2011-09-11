/*
 * LibSylph Class Library
 * Copyright (C) 2011 Frank "SeySayux" Erens <seysayux@gmail.com>
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

#include "SylphTest.h"
#include <Sylph/Core/HashMap.h>
#include <Sylph/Core/Debug.h>

using namespace Sylph;

namespace {

    void testEqualityHelper(HashMap<String,String>& h,
            bool order = true) {
        if(order) {
            h["a"] = "alpha";
            h["b"] = "beta";
            h["g"] = "gamma";
            h["d"] = "delta";
        } else {
            h["g"] = "gamma";
            h["d"] = "delta";
            h["b"] = "beta";
            h["a"] = "alpha";
        }
    }

    class TestHashMap : public ::testing::Test {

    };

    TEST_F(TestHashMap, testInEqOut) {
        HashMap<String,String> h;
        h["English"] = "English";
        h["French"] = "français";
        h["Spanish"] = "español";
        h["Dutch"] = "Nederlands";
        ASSERT_EQ(4u,h.size());
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
        ASSERT_EQ(4u,h.size());
        h.clear();
        EXPECT_EQ(0u,h.size());
    }

    TEST_F(TestHashMap, testRehash) {
        HashMap<String,String> h((size_t) 3);
        h["English"] = "English";
        h["French"] = "français";
        h["Spanish"] = "español";
        h["Dutch"] = "Nederlands";
        ASSERT_EQ(4u,h.size());
        EXPECT_EQ(String("English"),h["English"]);
        EXPECT_EQ(String("français"),h["French"]);
        EXPECT_EQ(String("español"),h["Spanish"]);
        EXPECT_EQ(String("Nederlands"),h["Dutch"]);
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

    TEST_F(TestHashMap, testEmptyIterator) {
        HashMap<String, String> h;

        ASSERT_NO_THROW({
           for(HashMap<String,String>::iterator it = h.begin();
                it != h.end(); ++it) {
               // hopefully not optimised out...
           }
        });
    }

    TEST_F(TestHashMap, testEmptyEquality) {
        /*HashMap<String,String> g;
        HashMap<String,String> h;

        ASSERT_NO_THROW(g == h);
        EXPECT_TRUE(g == h);*/
        SYLPH_STUB_TEST;
    }

    TEST_F(TestHashMap, testRealEquality) {
        HashMap<String, String> h;
        HashMap<String, String> g;

        testEqualityHelper(h);
        testEqualityHelper(g);

        ASSERT_NO_THROW(g == h);
        EXPECT_TRUE(g == h);
    }

    TEST_F(TestHashMap, testInequality) {
        HashMap<String, String> h;
        HashMap<String, String> g;

        testEqualityHelper(h);
        g["a"] = "aleph";

        ASSERT_NO_THROW(g == h);
        EXPECT_FALSE(g == h);
    }

    TEST_F(TestHashMap, testSequenceEquality) {
        HashMap<String, String> h;
        HashMap<String, String> g;

        testEqualityHelper(h);
        testEqualityHelper(g, false);

        ASSERT_NO_THROW(g == h);
        EXPECT_TRUE(g == h);
    }


} // namespace
