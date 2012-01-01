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
 * Created on 20 december 2009, 17:07
 */

#ifndef SYLPHTEST_H_
#define	SYLPHTEST_H_

#ifndef ECLIPSE_PARSER
#include <gtest/gtest.h>
#endif

#define SYLPH_STUB_TEST ADD_FAILURE() << "FIXME: this is a stub testcase!"

// Eclipse stuff
#ifdef ECLIPSE_PARSER
namespace testing {
    class Test {};
    void InitGoogleTest(int*,char**) {}
}
#define RUN_ALL_TESTS() 0

#define TEST_F(X,Y) void ssylph__ ## X ## Y ()

#define ASSERT_EQ(X,Y)
#define EXPECT_EQ(X,Y)
#define ASSERT_NE(X,Y)
#define EXPECT_NE(X,Y)
#define ASSERT_TRUE(X)
#define EXPECT_TRUE(X)
#define ASSERT_FALSE(X)
#define EXPECT_FALSE(X)

#define EXPECT_STREQ(X,Y)
#define ASSERT_STREQ(X,Y)

#define EXPECT_FLOAT_EQ(X,Y)

#define ASSERT_NO_THROW(X) X
#define EXPECT_NO_THROW(X) X

#define ASSERT_THROW(X,Y) X
#define EXPECT_THROW(X,Y) X
#endif

#endif	/* SYLPHTEST_H_ */

