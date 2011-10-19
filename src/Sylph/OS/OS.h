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
 * Created on 17 januari 2009, 15:17
 */

#ifndef SYLPH_OS_OS_H_
#define	SYLPH_OS_OS_H_

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
#ifdef SYLPH_OS_MACOSX
#define S_MAIN_PARAMS int argc, char ** argv, char ** envp, char ** apple
#define S_INIT_PARAMS argc, argv, apple
#else
#define S_MAIN_PARAMS int argc, char ** argv
#define S_INIT_PARAMS argc, argv, 0
#endif

#endif	/* SYLPH_OS_OS_H_ */

