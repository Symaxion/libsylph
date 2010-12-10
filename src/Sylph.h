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
        abort();
    } catch (const Sylph::Exception & ex) {
        Sylph::UncaughtExceptionHandler::handler->handle(ex);
        abort();
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
        abort();
    } catch (const Sylph::Exception & ex) {
        Sylph::UncaughtExceptionHandler::handler->handle(ex);
        abort();
    }
}
#endif

#endif
#endif	/* SYLPH_H_ */

