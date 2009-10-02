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
 * Created on 17 januari 2009, 15:17
 */

#ifndef OS_H_
#define	OS_H_

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

#endif	/* OS_H_ */

