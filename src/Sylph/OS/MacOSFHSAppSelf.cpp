#include "MacOSFHSAppSelf.h"
#include "../Core/File.h"

#ifdef SYLPH_OS_MACOSX

#include <string>
#include <pwd.h>

SYLPH_BEGIN_NAMESPACE

MacOSFHSAppSelf::MacOSFHSAppSelf(int argc, char * argv[], char * apple[]) {
    _location= String(apple[0]);
}

const File& MacOSFHSAppSelf::bundle() {
    return prefix();
}

const File& MacOSFHSAppSelf::resourceDir() {
    static File f = prefix() / "share" / appName();
    return f;
}

const File MacOSFHSAppSelf::resource(String rsc) {
    return resourceDir() / rsc;
}

const File& MacOSFHSAppSelf::libraryDir() {
    static File f = prefix() / "lib";
    return f;
}

const File& MacOSFHSAppSelf::pluginDir() {
    static File f = prefix() / "lib" / appName() / "plugins";
    return f;
}

const File& MacOSFHSAppSelf::plugindisabledDir() {
    static File f = prefix() / "lib" / appName() / "plugins-disabled";
}

const File& MacOSFHSAppSelf::systemLibraryDir() {
    return libraryDir();
}

const File& MacOSFHSAppSelf::systemSettings() {
    static File f = systemSettingsDir() / (appName() + ".conf");
    return f;
}

const File& MacOSFHSAppSelf::systemSettingsDir() {
    static File f = "/etc/" + appName() + ".d";
    return f;
}

const File& MacOSFHSAppSelf::systemPluginDir() {
    return pluginDir();
}

const File& MacOSFHSAppSelf::systemPluginDisabledDir() {
    return plugindisabledDir();
}

const File& MacOSFHSAppSelf::systemResourceDir() {
    return resourceDir();
}

const File MacOSFHSAppSelf::systemResource(String rsc) {
    return resource(rsc);
}

const File& MacOSFHSAppSelf::userHome() {
    static File f = getpwuid(geteuid())->pw_dir;
    return f;
}

const File& MacOSFHSAppSelf::userLibraryDir() {
    static File f = userHome() / ".local/lib";
    return f;
}

const File& MacOSFHSAppSelf::userSettings() {
    static File f = userSettingsDir() / (appName()+".conf");
    return f;
}

const File& MacOSFHSAppSelf::userSettingsDir() {
    static File f = userHome() / ".config" / appName();
    return f;
}

const File& MacOSFHSAppSelf::userPluginDir() {
    static File f = userLibraryDir() / appName() / "plugins";
    return f;
}

const File& MacOSFHSAppSelf::userPluginDisabledDir() {
    static File f = userLibraryDir() / appName() / "plugins-disabled";
    return f;
}

const File& MacOSFHSAppSelf::userResourceDir() {
    static File f = userHome() / ".local/share";
    return f;
}

const File MacOSFHSAppSelf::userResource(String rsc) {
    return userResourceDir() / rsc;
}

const File& MacOSFHSAppSelf::prefix() {
    static File f = File(_location).parent().parent();
    return f;
}

SYLPH_END_NAMESPACE

#endif // SYLPH_OS_MACOSX