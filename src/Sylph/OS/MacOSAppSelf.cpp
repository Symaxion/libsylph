#include "MacOSAppSelf.h"
#include "../Core/File.h"

#include <string>
#include <pwd.h>

SYLPH_BEGIN_NAMESPACE

MacOSAppSelf::MacOSAppSelf(int argc, char * argv[], char * apple[]) {
    _location= String(apple[0]);
}

const File& MacOSAppSelf::bundle() {
    static File f = File(_location).parent().parent().parent();
    return f;
}

const File& MacOSAppSelf::resourceDir() {
    static File f = bundle() / "Contents/Resources";
    return f;
}

const File MacOSAppSelf::resource(String rsc) {
    return resourceDir() / rsc;
}

const File& MacOSAppSelf::libraryDir() {
    static File f = bundle() / "Contents/Frameworks";
    return f;
}

const File& MacOSAppSelf::pluginDir() {
    static File f = bundle() / "Contents/Plugins";
    return f;
}

const File& MacOSAppSelf::plugindisabledDir() {
    static File f = bundle() / "Contents/Plugins-Disabled";
    return f;
}

const File& MacOSAppSelf::systemLibraryDir() {
    static File f = "/Library";
    return f;
}

const File& MacOSAppSelf::systemSettings() {
    static File f = "/Library/Preferences/" + appName() + ".prp";
    return f;
}

const File& MacOSAppSelf::systemSettingsDir() {
    static File f = "/Library/Preferences";
    return f;
}

const File& MacOSAppSelf::systemPluginDir() {
    static File f = systemResource("Plugins");
    return f;
}

const File& MacOSAppSelf::systemPluginDisabledDir() {
    static File f = systemResource("Plugins-Disabled");
    return f;
}

const File& MacOSAppSelf::systemResourceDir() {
    static File f = "/Library/Application Support/"+appName();
    return f;
}

const File MacOSAppSelf::systemResource(String rsc) {
    return systemResourceDir() / rsc;
}

const File& MacOSAppSelf::userHome() {
    static File f = getpwuid(geteuid())->pw_dir;
    return f;
}

const File& MacOSAppSelf::userLibraryDir() {
    static File f = userHome() / "Library";
    return f;
}

const File& MacOSAppSelf::userSettings() {
    static File f = userLibraryDir() / ("Preferences/"+appName() + ".prp");
    return f;
}

const File& MacOSAppSelf::userSettingsDir() {
    static File f = userLibraryDir() / "Preferences";
    return f;
}

const File& MacOSAppSelf::userPluginDir() {
    static File f = userResource("Plugins");
    return f;
}

const File& MacOSAppSelf::userPluginDisabledDir() {
    static File f = userResource("Plugins-Disabled");
    return f;
}

const File& MacOSAppSelf::userResourceDir() {
    static File f = userLibraryDir() / ("Application Support/" + appName());
    return f;
}

const File MacOSAppSelf::userResource(String rsc) {
    return userResourceDir() / rsc;
}

const File& MacOSAppSelf::prefix() {
    static File f = File(_location).parent().parent();
    return f;
}

SYLPH_END_NAMESPACE
