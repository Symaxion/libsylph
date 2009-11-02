#include "Application.h"
#include "String.h"
#include "File.h"

#include <iostream>
#include <cstdlib>

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
    void Application::init(int argc, char* argv[], char * apple[], AppType type) {
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
    }

    void ApplicationSelf::_preconstruct() {
        // can be used for preconstruction. Doesn't do anything yet (used for
        // gc, but Object now handles this)
    }

    AppType ApplicationSelf::appType() {
        return _appType;
    }

    ApplicationSelf::~ApplicationSelf() {}

    void ApplicationSelf::fail(const String reason) {
        _fail(appName(), reason);
    }
    void ApplicationSelf::fail(const String reason, const String file,
            unsigned int line) {
        _fail(appName(), reason, file, line);
    }
    void ApplicationSelf::_fail(const String appName, const String reason) {
        std::cout << appName <<" error: " << reason << std::endl;
        exit(1);
    }
    void ApplicationSelf::_fail(const String appName, const String reason,
                const String file, unsigned int line) {
        std::cout << appName <<" error: " << reason << "@" << file << ":" <<
           line << std::endl;
        exit(1);
    }

SYLPH_END_NAMESPACE
