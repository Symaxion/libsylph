#include "SylphTest.h"
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
