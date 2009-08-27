#include "LinuxFHSAppSelf.h"
#include "../Core/File.h"

#ifdef SYLPH_OS_LINUX

#include <binreloc.h>

#include <pwd.h>

SYLPH_BEGIN_NAMESPACE

LinuxFHSAppSelf::LinuxFHSAppSelf(int argc, char * argv[]) {
    // First, make binreloc work...
    BrInitError error;

    if (br_init(&error) == 0 && error != BR_INIT_ERROR_DISABLED)
        _fail("LibSylph", "Couldn't init binreloc!", __FILE__, __LINE__);
    _location = br_find_exe("");
    if (_location == "") {
        _fail("LibSylph", "Couldn't init binreloc!", __FILE__, __LINE__);
    }

}

const File& LinuxFHSAppSelf::bundle() {
    return prefix();
}

const File& LinuxFHSAppSelf::resourceDir() {
    static File f = prefix() / "share" / appName();
    return f;
}

const File LinuxFHSAppSelf::resource(String rsc) {
    return resourceDir() / rsc;
}

const File& LinuxFHSAppSelf::libraryDir() {
    static File f = prefix() / "lib";
    return f;
}

const File& LinuxFHSAppSelf::pluginDir() {
    static File f = prefix() / "lib" / appName() / "plugins";
    return f;
}

const File& LinuxFHSAppSelf::plugindisabledDir() {
    static File f = prefix() / "lib" / appName() / "plugins-disabled";
}

const File& LinuxFHSAppSelf::systemLibraryDir() {
    return libraryDir();
}

const File& LinuxFHSAppSelf::systemSettings() {
    static File f = systemSettingsDir() / (appName() + ".conf");
    return f;
}

const File& LinuxFHSAppSelf::systemSettingsDir() {
    static File f = "/etc/" + appName() + ".d";
    return f;
}

const File& LinuxFHSAppSelf::systemPluginDir() {
    return pluginDir();
}

const File& LinuxFHSAppSelf::systemPluginDisabledDir() {
    return plugindisabledDir();
}

const File& LinuxFHSAppSelf::systemResourceDir() {
    return resourceDir();
}

const File LinuxFHSAppSelf::systemResource(String rsc) {
    return resource(rsc);
}

const File& LinuxFHSAppSelf::userHome() {
    static File f = getpwuid(geteuid())->pw_dir;
    return f;
}

const File& LinuxFHSAppSelf::userLibraryDir() {
    static File f = userHome() / ".local/lib";
    return f;
}

const File& LinuxFHSAppSelf::userSettings() {
    static File f = userSettingsDir() / (appName()+".conf");
    return f;
}

const File& LinuxFHSAppSelf::userSettingsDir() {
    static File f = userHome() / ".config" / appName();
    return f;
}

const File& LinuxFHSAppSelf::userPluginDir() {
    static File f = userLibraryDir() / appName() / "plugins";
    return f;
}

const File& LinuxFHSAppSelf::userPluginDisabledDir() {
    static File f = userLibraryDir() / appName() / "plugins-disabled";
    return f;
}

const File& LinuxFHSAppSelf::userResourceDir() {
    static File f = userHome() / ".local/share";
    return f;
}

const File LinuxFHSAppSelf::userResource(String rsc) {
    return userResourceDir() / rsc;
}

const File& LinuxFHSAppSelf::prefix() {
    static File f = File(_location).parent().parent();
    return f;
}

SYLPH_END_NAMESPACE

#endif // SYLPH_OS_LINUX