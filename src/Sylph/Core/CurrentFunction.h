/* 
 * File:   CurrentFunction.h
 * Author: Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * Created on 3 juli 2009, 11:58
 */

// Adapted from The Boost Libraries, version 1.39. Original license follows:

//
//  boost/current_function.hpp - BOOST_CURRENT_FUNCTION
//
//  Copyright (c) 2002 Peter Dimov and Multi Media Ltd.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  http://www.boost.org/libs/utility/current_function.html
//


#ifndef CURRENTFUNCTION_H_
#define	CURRENTFUNCTION_H_

#include "Object.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC
inline void currentFunctionHelper() {
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600))
#define S_CURRENT_FUNCTION __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define S_CURRENT_FUNCTION __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
#define S_CURRENT_FUNCTION __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define S_CURRENT_FUNCTION __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define S_CURRENT_FUNCTION __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define S_CURRENT_FUNCTION __func__
#else
#define S_CURRENT_FUNCTION "(unknown)"
#endif
}


SYLPH_END_NAMESPACE


#endif	/* CURRENTFUNCTION_H_ */

