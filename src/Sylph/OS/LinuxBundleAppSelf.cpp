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
 */

#include "LinuxBundleAppSelf.h"
#include "../Core/File.h"

#ifdef SYLPH_OS_LINUX

#include <binreloc.h>

#include <unistd.h>
#include <pwd.h>
#include <unistd.h>

SYLPH_BEGIN_NAMESPACE

LinuxBundleAppSelf::LinuxBundleAppSelf(int argc, char * argv[]) {
    // First, make binreloc work...
    BrInitError error;

    if (br_init(&error) == 0 && error != BR_INIT_ERROR_DISABLED)
        _fail("LibSylph", "Couldn't init binreloc!", __FILE__, __LINE__);
    _location = br_find_exe("");
    if (_location == "") {
        _fail("LibSylph", "Couldn't init binreloc!", __FILE__, __LINE__);
    }

}

const File& LinuxBundleAppSelf::bundle() {
    static File f = File(_location).parent().parent().parent();
    return f;
}

const File& LinuxBundleAppSelf::resourceDir() {
    static File f = bundle() / "Contents/Resources";
    return f;
}

const File LinuxBundleAppSelf::resource(String rsc) {
    return resourceDir() / rsc;
}

const File& LinuxBundleAppSelf::libraryDir() {
    static File f = bundle() / "Contents/Frameworks";
    return f;
}

const File& LinuxBundleAppSelf::pluginDir() {
    static File f = bundle() / "Contents/Plugins";
    return f;
}

const File& LinuxBundleAppSelf::plugindisabledDir() {
    static File f = bundle() / "Contents/Plugins-Disabled";
    return f;
}

const File& LinuxBundleAppSelf::systemLibraryDir() {
    static File f = "/Library";
    return f;
}

const File& LinuxBundleAppSelf::systemSettings() {
    static File f = "/Library/Preferences/" + appName() + ".prp";
    return f;
}

const File& LinuxBundleAppSelf::systemSettingsDir() {
    static File f = "/Library/Preferences";
    return f;
}

const File& LinuxBundleAppSelf::systemPluginDir() {
    static File f = systemResource("Plugins");
    return f;
}

const File& LinuxBundleAppSelf::systemPluginDisabledDir() {
    static File f = systemResource("Plugins-Disabled");
    return f;
}

const File& LinuxBundleAppSelf::systemResourceDir() {
    static File f = "/Library/Application Support/"+appName();
    return f;
}

const File LinuxBundleAppSelf::systemResource(String rsc) {
    return systemResourceDir() / rsc;
}

const File& LinuxBundleAppSelf::userHome() {
    static File f = getpwuid(geteuid())->pw_dir;
    return f;
}

const File& LinuxBundleAppSelf::userLibraryDir() {
    static File f = userHome() / "Library";
    return f;
}

const File& LinuxBundleAppSelf::userSettings() {
    static File f = userLibraryDir() / ("Preferences/"+appName() + ".prp");
    return f;
}

const File& LinuxBundleAppSelf::userSettingsDir() {
    static File f = userLibraryDir() / "Preferences";
    return f;
}

const File& LinuxBundleAppSelf::userPluginDir() {
    static File f = userResource("Plugins");
    return f;
}

const File& LinuxBundleAppSelf::userPluginDisabledDir() {
    static File f = userResource("Plugins-Disabled");
    return f;
}

const File& LinuxBundleAppSelf::userResourceDir() {
    static File f = userLibraryDir() / ("Application Support/" + appName());
    return f;
}

const File LinuxBundleAppSelf::userResource(String rsc) {
    return userResourceDir() / rsc;
}

const File& LinuxBundleAppSelf::prefix() {
    static File f = File(_location).parent().parent();
    return f;
}

SYLPH_END_NAMESPACE
#endif // SYLPH_OS_LINUX
