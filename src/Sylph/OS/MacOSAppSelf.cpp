/*
 * LibSylph Class Library
 * Copyright (C) 2011 Frank "SeySayux" Erens <seysayux@gmail.com>
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

#include "MacOSAppSelf.h"
#include "../Core/File.h"

#ifdef SYLPH_OS_MACOSX

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

#endif // SYLPH_OS_MACOSX
