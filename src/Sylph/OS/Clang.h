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

#ifndef SYLPH_OS_CLANG_H_
#define SYLPH_OS_CLANG_H_

#include "GccLike.h" // Common for compilers supporting GCC extensions

#if !__has_feature(cxx_generalized_initializers)
#define SYLPH_FTR_NO_GEN_INIT
#endif

#if !__has_feature(cxx_static_assert)
#define SYLPH_FTR_NO_STATIC_ASSERT
#endif

#if !__has_feature(cxx_auto_type)
#define SYLPH_FTR_NO_AUTO
#endif

#if !__has_feature(cxx_trailing_return)
#define SYLPH_FTR_NO_TRAILING_RETURN
#endif

#if !__has_feature(cxx_defaulted_functions) || \
        !__has_feature(cxx_deleted_functions) 
#define SYLPH_FTR_NO_DEFAULT_DELETE
#endif

/*
FIXME: Clang does not report this.
#if !__has_feature()
#define SYLPH_FTR_NO_ATOMIC
#endif
*/

#if !__has_feature(cxx_lambdas)
#define SYLPH_FTR_NO_LAMBDAS
#endif

#if !__has_feature(cxx_explicit_conversions)
#define SYLPH_FTR_NO_EXPLICIT_CONVERSION
#endif

#if !__has_feature(cxx_unicode_literals)
#define SYLPH_FTR_NO_UNICODE_LITERALS
#endif

#if !__has_feature(cxx_nullptr)
#define SYLPH_FTR_NO_NULLPTR
#endif

/*
FIXME: Clang does not report this.
#if !__has_feature()
#define SYLPH_FTR_NO_FWDDECL_ENUMS
#endif
*/

#if !__has_feature(cxx_constexpr)
#define SYLPH_FTR_NO_CONSTEXPR
#endif

#if !__has_feature(cxx_range_for)
#define SYLPH_FTR_NO_RANGE_FOR 
#endif

#if !__has_feature(cxx_static_assert)
#define SYLPH_FTR_NO_RVALUES 
#endif

#if !__has_feature(cxx_user_literals)
#define SYLPH_FTR_NO_USER_LITERALS
#endif

#if !__has_feature(cxx_alias_templates)
#define SYLPH_FTR_NO_TEMPLATE_TYPEDEF
#endif

#if !__has_feature(cxx_delegating_constructors)
#define SYLPH_FTR_NO_DELEGATING_CONSTRUCTORS
#endif

#if !__has_feature(cxx_alias_templates)
#define SYLPH_FTR_NO_OVERRIDE
#endif

#endif /* SYLPH_OS_CLANG_H_ */

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
