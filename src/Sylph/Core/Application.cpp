#include "Application.h"

#include "File.h"

#include <iostream>
#include <cstdlib>

#include <gc.h>

#include "../OS/LinuxBundleAppSelf.h"
#include "../OS/LinuxFHSAppSelf.h"
#include "../OS/MacOSAppSelf.h"
#include "../OS/MacOSFHSAppSelf.h"
#include "../OS/WindowsAppSelf.h"


namespace Sylph {
namespace Core {

    namespace SO = Sylph::OS;

    Application::Application() {

    }

    Application::~Application() {

    }
    void Application::init(int argc, char* argv[], char * apple[], AppType type) {
        switch(type) {
            case S_APPTYPE_BUNDLE:
                self_app = new SO::LinuxBundleAppSelf(argc,argv);
                break;
            case S_APPTYPE_FHS:
                self_app = new SO::LinuxFHSAppSelf(argc,argv);
                break;
            case S_APPTYPE_MACOS:
                self_app = new SO::MacOSAppSelf(argc,argv,apple);
                break;
            case S_APPTYPE_MACOS_FHS:
                break;
            case S_APPTYPE_WINDOWS:
                break;
            default:
                _fail("LibSylph","Unknown App Type!",__FILE__,__LINE__);
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
    void _fail(const string & appName, const string & reason) {
        cout << appName <<" error: " << reason << endl;
        exit(1);
    }
    void _fail(const string & appName, const string & reason,
                const string & file, int line) {
        cout << appName <<" error: " << reason << "@" << file << ":" << line << endl;
    }

}
}

