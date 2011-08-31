/*
 * LibSylph Class Library
 * Copyright (C) 2011 Frank "SeySayux" Erens <seysayux@gmail.com>
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
 * Created on 19 augustus 2009, 13:12
 */

#include <gtest/gtest.h>

#include <Sylph/OS/OS.h>
#include <Sylph/Core/Application.h>
#include <Sylph/Core/Array.h>
#include <Sylph/Core/String.h>
#include <Sylph/Core/Common.h>
#include <Sylph/Core/AppType.h>
#include <Sylph/Core/UncaughtExceptionHandler.h>

#define SYLPH_APP_NAME "LibSylph Unit Tests"

#ifdef SYLPH_OS_MACOSX
int main(int argc, char * argv[], char * envp[], char * apple[]);
#else
int main(int argc, char * argv[]);
#endif
static inline void SylphInit(int argc, char * argv[], char * apple[]) {
    Sylph::Application::init(argc, argv, apple, Sylph::SYLPH_APP_TYPE,
            SYLPH_APP_NAME);
}

#ifdef SYLPH_OS_MACOSX

int main(int argc, char * argv[], char * envp[], char * apple[]) {
    try {
        SylphInit(argc, argv, apple);
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
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
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    } catch(const Sylph::Assertion& as) {
        Sylph::UncaughtExceptionHandler::handler->handleAssertion(as);
        throw;
    } catch (const Sylph::Exception & ex) {
        Sylph::UncaughtExceptionHandler::handler->handle(ex);
        throw;
    }
}
#endif

