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
        UErrorCode err;
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
