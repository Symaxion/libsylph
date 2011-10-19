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
