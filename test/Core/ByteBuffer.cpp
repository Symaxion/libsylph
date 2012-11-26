/*
 * LibSylph Class Library
 * Copyright (C) 2012 Frank "SeySayux" Erens <seysayux@gmail.com>
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
#include <Sylph/Core/ByteBuffer.h>
#include <Sylph/Core/Debug.h>

using namespace Sylph;

namespace {
    class TestByteBuffer : public ::testing::Test {

    };

    TEST_F(TestByteBuffer, testRead) {
        Array<byte> src = {0x13, 0x68, 0x22, 0x90, 0xA3, 0x27};
        ByteBuffer buf(src);
        ASSERT_EQ(6u, buf.size());
        Array<byte> dest((size_t)6);
        buf.read(dest);
        EXPECT_EQ(dest,src);
        EXPECT_TRUE(buf.eof());
    }

    TEST_F(TestByteBuffer, testWrite) {
        Array<byte> src = {0x13, 0x68, 0x22, 0x90, 0xA3, 0x27};
        ByteBuffer buf;
        buf.write(src);
        ASSERT_EQ(6u, buf.size());

        Array<byte> dest = buf.toArray();
        ASSERT_EQ(6u, dest.length);
        EXPECT_EQ(dest, src);

    }

    TEST_F(TestByteBuffer, testExpand) {
        ByteBuffer buf(ByteBuffer::RW, 2);
        Array<byte> src = {0x13, 0x68, 0x22, 0x90, 0xA3, 0x27};
        buf.write(src);
        ASSERT_EQ(6u, buf.size());

        Array<byte> dest = buf.toArray();
        ASSERT_EQ(6u, dest.length);
        EXPECT_EQ(dest, src);
    }

    TEST_F(TestByteBuffer, testFromString) {
        Array<byte> src = {0x13, 0x68, 0xC2, 0x90, 0xA3, 0x27};
        String s = "1368c290A327";

        ByteBuffer buf;
        buf.fromString(s);

        ASSERT_EQ(6u, buf.size());

        Array<byte> dest = buf.toArray();
        ASSERT_EQ(6u, dest.length);
        EXPECT_EQ(dest, src);
    }

    TEST_F(TestByteBuffer, testClose) {
        Array<byte> src = {0x13, 0x68, 0x22, 0x90, 0xA3, 0x27};
        ByteBuffer buf;

        buf.write(src);
        buf.close();

        EXPECT_THROW(buf.write(src),IllegalStateException);
    }
} // namespace

// vim: ts=4:sts=4:sw=4:sta:et:tw=80:nobk:path=../../../src
