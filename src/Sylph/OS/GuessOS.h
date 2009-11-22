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

