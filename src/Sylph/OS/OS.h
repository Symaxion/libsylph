/* 
 * File:   OS.h
 * Author: frank
 *
 * Created on 17 januari 2009, 15:17
 */

#ifndef _OS_H
#define	_OS_H

#include "GuessOS.h"

#if defined(SYLPH_OS_WINDOWS)
#define OS_TYPE "Windows"
#elif defined(SYLPH_OS_MACOSX)
#define OS_TYPE "Mac OS X"
#elif defined(SYLPH_OS_CYGWIN)
#define OS_TYPE "Cygwin"
#elif defined(SYLPH_OS_LINUX)
#define OS_TYPE "Linux"
#else
#error OS not supported
#endif

#endif	/* _OS_H */

