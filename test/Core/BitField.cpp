/*
 * LibSylph Class Library
 * Copyright (C) 2012 Randy "Villadelfia" Thiemann <uselinuxnow@gmail.com>
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
#include <Sylph/Core/BitField.h>
#include <Sylph/Core/Range.h>
#include <Sylph/Core/Debug.h>

using namespace Sylph;

namespace {
    class TestBitField : public ::testing::Test {
    };

    //Test if MSB and LSB get set correctly.
    TEST_F(TestBitField, testCtor) {
        BitField<4u> b;
        EXPECT_EQ(4u * CHAR_BIT - 1, b.MSB);
        EXPECT_EQ(0u, b.LSB);
    }

    //Test if the bitfield gets initialized as 0.
    TEST_F(TestBitField, testInitZero) {
        BitField<1024u> b;
        for(idx_t i = 0; i < CHAR_BIT * 1024u; ++i)
            EXPECT_FALSE(b.get(i));
    }

    //Test if the bitfield gets initialized as 0, using the indexing operator.
    TEST_F(TestBitField, testIndexing) {
        BitField<1024u> b;
        for(idx_t i = 0; i < CHAR_BIT * 1024u; ++i)
            EXPECT_FALSE(b[i]);
    }

    //Test if setting bits works.
    TEST_F(TestBitField, testSet) {
        BitField<1024u> b;
        for(idx_t i = 0; i < CHAR_BIT * 1024u; ++i) {
            b.set(i);
            EXPECT_TRUE(b.get(i));
            EXPECT_TRUE(b[i]);
        }
    }

    //Test if setting bits works using the indexing operator.
    TEST_F(TestBitField, testSetIndex) {
        BitField<1024u> b;
        for(idx_t i = 0; i < CHAR_BIT * 1024u; ++i) {
            b[i] = 1;
            EXPECT_TRUE(b.get(i));
            EXPECT_TRUE(b[i]);
            b[i] = 0;
            EXPECT_FALSE(b[i]);
            EXPECT_FALSE(b.get(i));
        }
    }

    //Test if resetting bits works.
    TEST_F(TestBitField, testReset) {
        BitField<1024u> b;
        for(idx_t i = 0; i < CHAR_BIT * 1024u; ++i) {
            EXPECT_FALSE(b.get(i));
            EXPECT_FALSE(b[i]);
            b.reset(i);
            EXPECT_FALSE(b.get(i));
            EXPECT_FALSE(b[i]);
            b.set(i);
            EXPECT_TRUE(b.get(i));
            EXPECT_TRUE(b[i]);
            b.reset(i);
            EXPECT_FALSE(b.get(i));
            EXPECT_FALSE(b[i]);
        }
    }

    //Test if toggling bits works.
    TEST_F(TestBitField, testToggle) {
        BitField<1024u> b;
        for(idx_t i = 0; i < CHAR_BIT * 1024u; ++i) {
            b.toggle(i);
            EXPECT_TRUE(b.get(i));
            EXPECT_TRUE(b[i]);
            b.toggle(i);
            EXPECT_FALSE(b[i]);
            EXPECT_FALSE(b.get(i));
        }
    }

    //Test if toggling bits works using the indexing operator.
    TEST_F(TestBitField, testToggleIndex) {
        BitField<1024u> b;
        for(idx_t i = 0; i < CHAR_BIT * 1024u; ++i) {
            b[i] ^= 1;
            EXPECT_TRUE(b.get(i));
            EXPECT_TRUE(b[i]);
            b[i] ^= 1;
            EXPECT_FALSE(b[i]);
            EXPECT_FALSE(b.get(i));
        }
    }

    //Test setting a range.
    TEST_F(TestBitField, testSetRange) {
        BitField<1024u> b;
        for(idx_t i = 0; i < CHAR_BIT * 1024u; ++i)
            EXPECT_FALSE(b.get(i));
        irange r(b.LSB, b.MSB);
        b.set(r);
        for(idx_t i = 0; i < CHAR_BIT * 1024u; ++i)
            EXPECT_TRUE(b.get(i));
    }

    //Test resetting a range.
    TEST_F(TestBitField, testResetRange) {
        BitField<1024u> b;
        for(idx_t i = 0; i < CHAR_BIT * 1024u; ++i)
            EXPECT_FALSE(b.get(i));
        irange r(b.LSB, b.MSB);
        b.set(r);
        for(idx_t i = 0; i < CHAR_BIT * 1024u; ++i)
            EXPECT_TRUE(b.get(i));
        b.reset(r);
        for(idx_t i = 0; i < CHAR_BIT * 1024u; ++i)
            EXPECT_FALSE(b.get(i));
    }
    
    //Test toggling a range.
    TEST_F(TestBitField, testToggleRange) {
        BitField<1024u> b;
        for(idx_t i = 0; i < CHAR_BIT * 1024u; ++i)
            EXPECT_FALSE(b.get(i));
        irange r(b.LSB, b.MSB);
        b.toggle(r);
        for(idx_t i = 0; i < CHAR_BIT * 1024u; ++i)
            EXPECT_TRUE(b.get(i));
        b.toggle(r);
        for(idx_t i = 0; i < CHAR_BIT * 1024u; ++i)
            EXPECT_FALSE(b.get(i));
        b.toggle(r);
        for(idx_t i = 0; i < CHAR_BIT * 1024u; ++i)
            EXPECT_TRUE(b.get(i));
    }
}

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk:pa+=,../../src
