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
 *  Created on: Aug 20, 2012
 */

#ifndef SYLPH_OS_GCC_H_
#define SYLPH_OS_GCC_H_

// GCC supports va_args, even in non-C++11 mode.
#undef SYLPH_FTR_NO_VA_ARGS

#if __GNUC__ <= 3 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 3)
// GCC 4.3 and below

#define SYLPH_FTR_NO_GEN_INIT
#define SYLPH_FTR_NO_STATIC_ASSERT
#define SYLPH_FTR_NO_AUTO
#define SYLPH_FTR_NO_TRAILING_RETURN
#define SYLPH_FTR_NO_DEFAULT_DELETE
#define SYLPH_FTR_NO_ATOMIC

#endif

#if __GNUC__ == 4

#if __GNUC_MINOR__ <= 4
// GCC 4.4 and below
#define SYLPH_FTR_NO_LAMBDAS
#define SYLPH_FTR_NO_EXPLICIT_CONVERSION
#define SYLPH_FTR_NO_UNICODE_LITERALS

#endif

#if __GNUC_MINOR__ <= 5
// GCC 4.5 and below
#define SYLPH_FTR_NO_NULLPTR
#define SYLPH_FTR_NO_FWDDECL_ENUMS
#define SYLPH_FTR_NO_CONSTEXPR
#define SYLPH_FTR_NO_RANGE_FOR 

// GCC had rvalues since 4.3, but they did not become useful (for move operations)
// until 4.6
#define SYLPH_FTR_NO_RVALUES 

#endif

#if __GNUC_MINOR__ <= 6
// GCC 4.6 and below
#define SYLPH_FTR_NO_USER_LITERALS
#define SYLPH_FTR_NO_TEMPLATE_TYPEDEF
#define SYLPH_FTR_NO_DELEGATING_CONSTRUCTORS
#define SYLPH_FTR_NO_OVERRIDE

#endif

#if __GNUC_MINOR__ <= 7
// GCC 4.7 and below
#endif

#endif

#include "GccLike.h"

#endif /* SYLPH_OS_GCC_H_ */

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
