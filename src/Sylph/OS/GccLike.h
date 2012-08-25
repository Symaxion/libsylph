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

#ifndef SYLPH_OS_GCCLIKE_H_
#define SYLPH_OS_GCCLIKE_H_

#define SYLPH_UNUSED void sylph_unused() __attribute__((unused))
#define SYLPH_END_MACRO SYLPH_UNUSED
#define SYLPH_DEPECRATE(x) x __attribute__((deprecated))

// Feature check

#ifdef SYLPH_FTR_NO_GEN_INIT
#warning "Essential feature disabled: (SYLPH_FTR_NO_GEN_INIT)"
#endif

#ifdef SYLPH_FTR_NO_STATIC_ASSERT
#warning "Essential feature disabled: (SYLPH_FTR_NO_STATIC_ASSERT)"
#endif

#ifdef SYLPH_FTR_NO_AUTO
#warning "Essential feature disabled: (SYLPH_FTR_NO_AUTO)"
#endif

#ifdef SYLPH_FTR_NO_TRAILING_RETURN
#warning "Essential feature disabled: (SYLPH_FTR_NO_TRAILING_RETURN)"
#endif

#ifdef SYLPH_FTR_NO_DEFAULT_DELETE
#warning "Essential feature disabled: (SYLPH_FTR_NO_DEFAULT_DELETE)"
#endif

#ifdef SYLPH_FTR_NO_ATOMIC
#warning "Essential feature disabled: (SYLPH_FTR_NO_ATOMIC)"
#endif

#ifdef SYLPH_FTR_NO_LAMBDAS
#warning "Essential feature disabled: (SYLPH_FTR_NO_LAMBDAS)"
#endif

#ifdef SYLPH_FTR_NO_EXPLICIT_CONVERSION
#warning "Essential feature disabled: (SYLPH_FTR_NO_EXPLICIT_CONVERSION)"
#endif

#ifdef SYLPH_FTR_NO_UNICODE_LITERALS
#warning "Essential feature disabled: (SYLPH_FTR_NO_UNICODE_LITERALS)"
#endif

#ifdef SYLPH_FTR_NO_NULLPTR
#warning "Essential feature disabled: (SYLPH_FTR_NO_NULLPTR)"
#endif

#ifdef SYLPH_FTR_NO_FWDDECL_ENUMS
#warning "Essential feature disabled: (SYLPH_FTR_NO_FWDDECL_ENUMS)"
#endif

#ifdef SYLPH_FTR_NO_CONSTEXPR
#warning "Essential feature disabled: (SYLPH_FTR_NO_CONSTEXPR)"
#endif

#ifdef SYLPH_FTR_NO_RANGE_FOR 
#warning "Essential feature disabled: (SYLPH_FTR_NO_RANGE_FOR )"
#endif

#ifdef SYLPH_FTR_NO_RVALUES 
#warning "Essential feature disabled: (SYLPH_FTR_NO_RVALUES )"
#endif

#ifdef SYLPH_FTR_NO_USER_LITERALS
#warning "Essential feature disabled: (SYLPH_FTR_NO_USER_LITERALS)"
#endif

#ifdef SYLPH_FTR_NO_TEMPLATE_TYPEDEF
#warning "Essential feature disabled: (SYLPH_FTR_NO_TEMPLATE_TYPEDEF)"
#endif

#ifdef SYLPH_FTR_NO_DELEGATING_CONSTRUCTORS
#warning "Essential feature disabled: (SYLPH_FTR_NO_DELEGATING_CONSTRUCTORS)"
#endif

#ifdef SYLPH_FTR_NO_OVERRIDE
#warning "Essential feature disabled: (SYLPH_FTR_NO_OVERRIDE)"
#endif

#endif /* SYLPH_OS_GCCLIKE_H_ */

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
