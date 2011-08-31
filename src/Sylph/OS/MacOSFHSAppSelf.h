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
 *
 * Created on 30 januari 2009, 9 : 21
 */

#ifndef MACOSFHSAPPSELF_H_
#define	MACOSFHSAPPSELF_H_

#include "../Core/Application.h"

SYLPH_BEGIN_NAMESPACE

class MacOSFHSAppSelf : public ApplicationSelf {
public:
    MacOSFHSAppSelf(int argc, char * argv[],char * apple[]);
    virtual ~MacOSFHSAppSelf() {}

    const File& bundle();
    const File& resourceDir();
    const File resource(String rsc);
    const File& libraryDir();
    const File& pluginDir();
    const File& plugindisabledDir();

    const File& systemLibraryDir();
    const File& systemSettings();
    const File& systemSettingsDir();
    const File& systemPluginDir();
    const File& systemPluginDisabledDir();
    const File& systemResourceDir();
    const File systemResource(String rsc);

    const File& userHome();

    const File& userLibraryDir();
    const File& userSettings();
    const File& userSettingsDir();
    const File& userPluginDir();
    const File& userPluginDisabledDir();
    const File& userResourceDir();
    const File userResource(String rsc);

    const File& prefix();
};

SYLPH_END_NAMESPACE

#endif	/* MACOSFHSAPPSELF_H_ */
