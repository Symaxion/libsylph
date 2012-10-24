/*
 * LibSylph Class Library
 * COPYRIGHT HERE
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
#include <HEADER_HERE>
#include <Sylph/Core/Debug.h>

using namespace Sylph;

SYLPH_BEGIN_NAMESPACE

namespace {

    class TEST_NAME_HERE : public ::testing::Test {

    };

    TEST_F(TEST_NAME_HERE, testExample) {
        EXPECT_EQ(0, 3 - 2 - 1);
    }
} // namespace

SYLPH_END_NAMESPACE

// vim: ts=4:sts=4:sw=4:sta:et:tw=80:nobk:pa+=,../../src
