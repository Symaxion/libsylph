#include "SylphTest.h"
#include <Sylph/Core/File.h>
#include <Sylph/Core/Debug.h>

using namespace Sylph;

namespace {
    class TestFile : public ::testing::Test {

    };

    TEST_F(TestFile,testParent) {
        ASSERT_NO_THROW({
            File f = "/var/foo/example";
            EXPECT_EQ("/var/foo",f.parent());

            EXPECT_EQ("/",File("/").parent());
        });
    }

    TEST_F(TestFile, testAppend) {
        File f = "/var/foo";
        f /= "example";
        EXPECT_EQ("/var/foo/example",f);

        f = "/var/foo/";
        f /= "example";
        EXPECT_EQ("/var/foo/example",f);
    }
}