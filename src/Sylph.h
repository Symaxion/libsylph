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
 * Created on 25 april 2009, 15:42
 */

#ifndef SYLPH_H_
#define	SYLPH_H_

/**
 * @file
 * @headerfile Sylph.h
 * This file is a shortcut to include many commonly used headers. Actually, it
 * will include the following headers (relative to @c Sylph/Core):
 * <code><ul>
 * <li>Any.h</li>
 * <li>Application.h</li>
 * <li>Array.h</li>
 * <li>ByteBuffer.h</li>
 * <li>Dictionary.h</li>
 * <li>Exception.h</li>
 * <li>File.h</li>
 * <li>I18N.h</li>
 * <li>PointerManager.h</li>
 * <li>Primitives.h</li>
 * <li>Range.h</li>
 * <li>String.h</li>
 * <li>StringBuffer.h</li>
 * <li>Util.h</li>
 * <li>Vector.h</li>
 * </ul></code>
 * It also has 'using' statements for following classes:
 * <code><ul>
 * <li>Sylph::Array</li>
 * <li>Sylph::Dictionary</li>
 * <li>Sylph::String</li>
 * <li>Sylph::range</li>
 * </ul></code>
 * You can turn this of by defining the macro @c SYLPH_NO_COMMON_USING before
 * inclusion.
 */

#include "Sylph/Core/Any.h"
#include "Sylph/Core/Application.h"
#include "Sylph/Core/Array.h"
#include "Sylph/Core/ByteBuffer.h"
#include "Sylph/Core/Dictionary.h"
#include "Sylph/Core/Exception.h"
#include "Sylph/Core/File.h"
#include "Sylph/Core/I18N.h"
#include "Sylph/Core/PointerManager.h"
#include "Sylph/Core/Primitives.h"
#include "Sylph/Core/Range.h"
#include "Sylph/Core/String.h"
<<<<<<< HEAD
#include "Sylph/Core/Common.h"
#include "Sylph/Core/AppType.h"
#include "Sylph/Core/UncaughtExceptionHandler.h"
#include "Sylph/Core/Thread.h"

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
    Sylph::Thread::current().setName("Main");
}
#ifdef SYLPH_MAIN_CLASSIC_PARAMS
extern int SylphMain(int argc, char** argv);
#else
extern int SylphMain(Sylph::Array<Sylph::String> argv);
=======
#include "Sylph/Core/StringBuffer.h"
#include "Sylph/Core/Util.h"
#include "Sylph/Core/Vector.h"

#ifndef SYLPH_NO_COMMON_USING
using Sylph::Array;
using Sylph::Dictionary;
using Sylph::String;
using Sylph::range;
>>>>>>> master
#endif


<<<<<<< HEAD
int main(int argc, char * argv[], char * envp[], char * apple[]) {
    try {
        SylphInit(argc, argv, apple);
        #ifdef SYLPH_MAIN_CLASSIC_PARAMS
        Sylph::Thread::exit(SylphMain(argc, argv));
        #else
        Array<String> args(argc);
        for(int i = 0; i < argc; ++i) {
            args[i] = argv[i];
        }
        Sylph::Thread::exit(SylphMain(args));
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
        Sylph::Thread::exit(SylphMain(argc, argv));
        #else
        Array<String> args(argc);
        for(int i = 0; i < argc; ++i) {
            args[i] = argv[i];
        }
        Sylph::Thread::exit(SylphMain(args));
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
=======
#endif	/* SYLPH_CORE_COMMON_H_ */
>>>>>>> master

