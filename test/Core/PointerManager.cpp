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
#include <Sylph/Core/PointerManager.h>
#include <Sylph/Core/Array.h>
#include <Sylph/Core/Debug.h>

namespace {
    class TestPointerManager : public ::testing::Test {
        
    };

    class DestructorCounting {
    public:
        DestructorCounting(){}
        ~DestructorCounting() {
            ++destroyed;
        }

        static idx_t destroyed;
    };

    idx_t DestructorCounting::destroyed = 0;

    void testPointerManagerHelper() {
        Sylph::Array<DestructorCounting*> arr(5);
        for(idx_t i = 0; i < 5; ++i) {
            arr[i] = new DestructorCounting;
        }
        Sylph::PointerManager pm = Sylph::manage(arr);
    }

    TEST_F(TestPointerManager,testPointerManager) {
        ASSERT_NO_THROW(testPointerManagerHelper());
        EXPECT_EQ(5u,DestructorCounting::destroyed);
    }
}
