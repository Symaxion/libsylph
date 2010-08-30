/*
 * LibSylph Class Library
 * Copyright (C) 2010 Frank "SeySayux" Erens <seysayux@gmail.com>
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
 * Created on 30 januari 2009, 9:08
 */

// Partially copied from The Boost Library, v 1.37.0
// Original copyright below:

//  Boost compiler configuration selection header file

//  (C) Copyright John Maddock 2001 - 2002.
//  (C) Copyright Jens Maurer 2001.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

#ifndef GUESSOS_H_
#define	GUESSOS_H_

#if defined(linux) || defined(__linux) || defined(__linux__)
// linux:
#  define SYLPH_OS_LINUX

#ifndef SYLPH_APP_TYPE
#define SYLPH_APP_TYPE S_APPTYPE_BUNDLE
#endif

#elif defined(__CYGWIN__)
// cygwin is not win32 -- Linux can be used as a substitute:
#  define SYLPH_OS_CYGWIN
#  define SYLPH_OS_LINUX

#ifndef SYLPH_APP_TYPE
#define SYLPH_APP_TYPE S_APPTYPE_BUNDLE
#endif

#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
// win32:
#  define SYLPH_OS_WINDOWS

#ifndef SYLPH_APP_TYPE
#define SYLPH_APP_TYPE S_APPTYPE_WINDOWS
#endif

#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
// MacOS
#  define SYLPH_OS_MACOSX

#ifndef SYLPH_APP_TYPE
#define SYLPH_APP_TYPE S_APPTYPE_MACOS
#endif

#endif


#endif	/* GUESSOS_H_ */

