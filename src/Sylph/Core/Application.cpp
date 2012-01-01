/*
 * LibSylph Class Library
 * Copyright (C) 2012 Frank "SeySayux" Erens <seysayux@gmail.com>
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
 */

#include "Application.h"
#include "String.h"
#include "File.h"

#include <iostream>
#include <cstdlib>
#include <unicode/uclean.h>

#include "../OS/LinuxBundleAppSelf.h"
#include "../OS/LinuxFHSAppSelf.h"
#include "../OS/MacOSAppSelf.h"
#include "../OS/MacOSFHSAppSelf.h"
//#include "../OS/WindowsAppSelf.h"


SYLPH_BEGIN_NAMESPACE

ApplicationSelf * Application::self_app = 0;

    Application::Application() {

    }

    Application::~Application() {

    }
    void Application::init(int argc, char* argv[], char * apple[], AppType type,
            String name) {
        switch(type) {
            #ifdef SYLPH_OS_LINUX
            case S_APPTYPE_BUNDLE:
                self_app = new LinuxBundleAppSelf(argc,argv);
                break;
            case S_APPTYPE_FHS:
                self_app = new LinuxFHSAppSelf(argc,argv);
                break;
            #endif
            #ifdef SYLPH_OS_MACOSX
            case S_APPTYPE_MACOS:
                self_app = new MacOSAppSelf(argc,argv,apple);
                break;
            case S_APPTYPE_MACOS_FHS:
                self_app = new MacOSFHSAppSelf(argc,argv,apple);
                break;
            #endif
            default:
                std::cout << "LibSylph error: Unknown or unsupported App Type! "<< "@"
                         << __FILE__<<":"<<__LINE__ << std::endl;
                exit(1);
        }
        self_app->_appType = type;
        self_app->_appName = name;
    }

    void ApplicationSelf::_preconstruct() {
        // Unicode stuff
        UErrorCode err = U_ZERO_ERROR;
        u_init(&err);
        if(U_FAILURE(err)) {
            fail(u_errorName(err));
        }
    }

    AppType ApplicationSelf::appType() {
        return _appType;
    }

    ApplicationSelf::~ApplicationSelf() {}

    void ApplicationSelf::fail(const String reason, bool exit) {
        _fail(appName(), reason, exit);
    }
    void ApplicationSelf::fail(const String reason, const String file,
            unsigned int line, bool exit) {
        _fail(appName(), reason, file, line, exit);
    }
    void ApplicationSelf::_fail(const String appName, const String reason,
            bool exit) {
        std::cout << appName <<" error: " << reason << std::endl;
        if(exit) ::exit(1);
    }
    void ApplicationSelf::_fail(const String appName, const String reason,
                const String file, unsigned int line, bool exit) {
        std::cout << appName <<" error: " << reason << "@" << file << ":" <<
           line << std::endl;
        if(exit) ::exit(1);
    }

SYLPH_END_NAMESPACE
