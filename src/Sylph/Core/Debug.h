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
 * Created on 14 december 2009, 16:19
 */

#ifndef SYLPH_CORE_DEBUG_H_
#define	SYLPH_CORE_DEBUG_H_

#include "Exception.h"
#include "String.h"
#include "CurrentFunction.h"
#include <iostream>

SYLPH_BEGIN_NAMESPACE
/**
 * @todo Write documentation!
 */
S_CREATE_EXCEPTION(Assertion);
#define S_CREATE_ASSERTION(Class) S_CREATE_EXCEPTION2(Class,Assertion)

#define SYLPH_STUB std::cerr << "Warning: stub function: " << \
    S_CURRENT_FUNCTION << " in " << __FILE__ << ":" << __LINE__ << "\n"

template<class A>
inline void Assert(bool b) {
    if(!b) throw A("");
}

template<class A>
inline void Assert(bool b, String s) {
    if(!b) throw A(s);
}

#define S_ASSERT(Pred) Assert<Assertion>(Pred,#Pred)

#ifdef SYLPH_DEBUG
#define S_DEBUG(Str) std::cerr << "Debug: " << Str << "\n";
#else
#define S_DEBUG(Str)
#endif

SYLPH_END_NAMESPACE


#endif	/* SYLPH_CORE_DEBUG_H_ */

