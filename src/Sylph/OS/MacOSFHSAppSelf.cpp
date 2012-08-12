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

#include "MacOSFHSAppSelf.h"
#include "../Core/File.h"

#ifdef SYLPH_OS_MACOSX

#include <string>
#include <pwd.h>
#include <unistd.h>

SYLPH_BEGIN_NAMESPACE

MacOSFHSAppSelf::MacOSFHSAppSelf(int, char**, char** apple) {
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
    return f;
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
