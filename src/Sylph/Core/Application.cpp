#include "Application.h"

#include <iostream>
#include <cstdlib>

#include <gc.h>

#include "../OS/LinuxBundleAppSelf.h"
#include "../OS/LinuxFHSAppSelf.h"
#include "../OS/MacOSAppSelf.h"
#include "../OS/MacOSFHSAppSelf.h"
#include "../OS/WindowsAppSelf.h"


SYLPH_BEGIN_NAMESPACE

    Application::Application() {

    }

    Application::~Application() {

    }
    void Application::init(int argc, char* argv[], char * apple[], AppType type) {
        switch(type) {
            case S_APPTYPE_BUNDLE:
                self_app = new LinuxBundleAppSelf(argc,argv);
                break;
            case S_APPTYPE_FHS:
                self_app = new LinuxFHSAppSelf(argc,argv);
                break;
            case S_APPTYPE_MACOS:
                self_app = new MacOSAppSelf(argc,argv,apple);
                break;
            case S_APPTYPE_MACOS_FHS:
                self_app = new MacOSFHSAppSelf(argc,argv,apple);
                break;
            case S_APPTYPE_WINDOWS:
                self_app = new WindowsAppSelf(argc,argv);
                break;
            default:
                std::cout << "LibSylph error: Unknown App Type! "<< "@"
                         << __FILE__<<":"<<__LINE__ << std::endl;
        }
        self_app->_appType = type;
    }

    void ApplicationSelf::_preconstruct() {
        // First, do the GC stuff...
        GC_INIT();
    }

    AppType ApplicationSelf::appType() {
        return _appType;
    }

    ApplicationSelf::~ApplicationSelf() {}

    void ApplicationSelf::fail(const string & reason) {
        _fail(appName, reason);
    }
    void ApplicationSelf::fail(const string & reason, const string & file, int line) {
        _fail(appName, reason, file, line);
    }
    void ApplicationSelf::_fail(const string & appName, const string & reason) {
        std::cout << appName <<" error: " << reason << std::endl;
        exit(1);
    }
    void ApplicationSelf::_fail(const string & appName, const string & reason,
                const string & file, int line) {
        std::cout << appName <<" error: " << reason << "@" << file << ":" <<
           line << std::endl;
    }

SYLPH_END_NAMESPACE
