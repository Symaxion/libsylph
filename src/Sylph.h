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
 * Created on 17 januari 2009, 15:14
 */

#ifndef SYLPH_H_
#define	SYLPH_H_

#include "Sylph/OS/OS.h"
#include "Sylph/Core/Application.h"
#include "Sylph/Core/Array.h"
#include "Sylph/Core/String.h"
#include "Sylph/Core/Common.h"
#include "Sylph/Core/AppType.h"

SYLPH_BEGIN_NAMESPACE
    /**
     * Creates a new (non-LibSylph) object using the LibSylph garbage
     * collection. Example (using Qt):
     * <pre>
     * QPushButton but * = newgc<QPushButton>("Hello");
     * </pre>
     * The syntax is very similar to that of the normal new operator.
     */
     template<class T,class... Args> T * newgc(const Args...& args);
     template<class T> void deletegc(const T * t);
     template<class T> void cleanupgc(void *obj, void *displ);
SYLPH_END_NAMESPACE

#ifndef SYLPH_NO_SYLPHMAIN
#ifdef SYLPH_OS_MACOSX
int main(int argc, char * argv[], char * envp[], char * apple[]);
#else
int main(int argc, char * argv[]);
#endif
static inline void SylphInit(int argc, char * argv[], char * apple[]) {
    Sylph::Application::init(argc, argv, apple, Sylph::APP_TYPE);
}
int SylphMain(Sylph::Array<Sylph::String> & argv);
#endif

#endif	/* SYLPH_H_ */

