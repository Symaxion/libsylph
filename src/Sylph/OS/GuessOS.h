/* 
 * File:   GuessOS.h
 * Author: frank
 *
 * Created on 30 januari 2009, 9:08
 */

#ifndef _GUESSOS_H
#define	_GUESSOS_H

// Partially copied from The Boost Library, v 1.37.0
// Original copyright below:

//  Boost compiler configuration selection header file

//  (C) Copyright John Maddock 2001 - 2002.
//  (C) Copyright Jens Maurer 2001.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

#if defined(linux) || defined(__linux) || defined(__linux__)
// linux:
#  define SYLPH_OS_LINUX

#ifndef APP_TYPE
#define APP_TYPE S_APPTYPE_BUNDLE
#endif

#elif defined(__CYGWIN__)
// cygwin is not win32 -- Linux can be used as a substitute:
#  define SYLPH_OS_CYGWIN
#  define SYLPH_OS_LINUX

#ifndef APP_TYPE
#define APP_TYPE S_APPTYPE_BUNDLE
#endif

#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
// win32:
#  define SYLPH_OS_WINDOWS

#ifndef APP_TYPE
#define APP_TYPE S_APPTYPE_WINDOWS
#endif

#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
// MacOS
#  define SYLPH_OS_MACOSX

#ifndef APP_TYPE
#define APP_TYPE S_APPTYPE_MACOS
#endif

#endif


#endif	/* _GUESSOS_H */

