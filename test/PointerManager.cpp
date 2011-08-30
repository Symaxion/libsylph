#include "SylphTest.h"
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
