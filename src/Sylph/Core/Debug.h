/*
 * LibSylph Class Library
 * Copyright (C) 2009 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LibSylph Pulbic License as published
 * by the LibSylph Developers; either version 1.0 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LibSylph
 * Public License for more details.
 *
 * You should have received a copy of the LibSylph Public License
 * along with this Library, if not, contact the LibSylph Developers.
 *
 * Created on 14 december 2009, 16:19
 */

#ifndef SYLPH_DEBUG_H_
#define	SYLPH_DEBUG_H_
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

#define SYLPH_STUB_TEST FAIL() << "Stub test!"

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


#endif	/* SYLPH_DEBUG_H_ */

