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
 *  Created on: Aug 14, 2012
 */

#ifndef SYLPH_OS_GUESSCOMPILER_H_
#define SYLPH_OS_GUESSCOMPILER_H_

#if defined(SYLPH_NO_CXX0X) || defined(SYLPH_NO_CXX11)
#include "NoCxx11.h"
#endif

#if defined(__clang__)
#define SYLPH_CC_CLANG
#define SYLPH_CC_GCCLIKE
#include "Clang.h"
#elif defined(__GNUC__)
#define SYLPH_CC_GCC
#define SYLPH_CC_GCCLIKE
#include "Gcc.h"
#else

#ifndef SYLPH_COMPILER_SUFFICIENT
#error "I could not detect your compiler; set SYLPH_COMPILER_SUFFICIENT if you"\
    " want to continue."
#else
#define SYLPH_CC_UNKNOWN
#include "UnknownCompiler.h"
#endif /* SYLPH_COMPILER_SUFFICIENT */

#endif

// Now we know everything, let's set some common (standardized) stuff.
#include "AllCompilers.h"

#endif /* SYLPH_OS_GUESSCOMPILER_H_ */

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
