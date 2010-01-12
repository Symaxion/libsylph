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
#include "Sylph/Core/UncaughtExceptionHandler.h"

#ifndef SYLPH_NO_SYLPHMAIN
#ifndef SYLPH_APP_NAME
#define SYLPH_APP_NAME "Application"
#endif

#ifdef SYLPH_OS_MACOSX
int main(int argc, char * argv[], char * envp[], char * apple[]);
#else
int main(int argc, char * argv[]);
#endif
static inline void SylphInit(int argc, char * argv[], char * apple[]) {
    Sylph::Application::init(argc, argv, apple, Sylph::SYLPH_APP_TYPE,
            SYLPH_APP_NAME);
}
#ifdef SYLPH_MAIN_CLASSIC_PARAMS
extern int SylphMain(int argc, char** argv);
#else
extern int SylphMain(Sylph::Array<Sylph::String> argv);
#endif

#ifdef SYLPH_OS_MACOSX

int main(int argc, char * argv[], char * envp[], char * apple[]) {
    try {
        SylphInit(argc, argv, apple);
        #ifdef SYLPH_MAIN_CLASSIC_PARAMS
        return SylphMain(argc, argv);
        #else
        Array<String> args(argc);
        for(int i = 0; i < argc; ++i) {
            args[i] = argv[i];
        }
        return SylphMain(args);
        #endif
    } catch(const Sylph::Assertion& as) {
        Sylph::UncaughtExceptionHandler::handler->handleAssertion(as);
        throw;
    } catch (const Sylph::Exception & ex) {
        Sylph::UncaughtExceptionHandler::handler->handle(ex);
        throw;
    }
}
#else

int main(int argc, char * argv[]) {
    try {
        SylphInit(argc, argv, Sylph::null);
        #ifdef SYLPH_MAIN_CLASSIC_PARAMS
        return SylphMain(argc, argv);
        #else
        Array<String> args(argc);
        for(int i = 0; i < argc; ++i) {
            args[i] = argv[i];
        }
        return SylphMain(args);
        #endif
    } catch(const Sylph::Assertion& as) {
        Sylph::UncaughtExceptionHandler::handler->handleAssertion(as);
        throw;
    } catch (const Sylph::Exception & ex) {
        Sylph::UncaughtExceptionHandler::handler->handle(ex);
        throw;
    }
}
#endif

#endif
#endif	/* SYLPH_H_ */

