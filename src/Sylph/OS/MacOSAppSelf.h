/*
 * LibSylph Class Library
 * Copyright (C) 2009 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LibSylph Pulbic License as published
 * by the LibSylph Developers; either version 1.0 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LibSylph
 * Public License for more details.
 *
 * You should have received a copy of the LibSylph Public License
 * along with this Library, if not, contact the LibSylph Developers.
 *
 * Created on 30 januari 2009, 9:19
 */

#ifndef MACOSAPPSELF_H_
#define	MACOSAPPSELF_H_

#include "../Core/Application.h"

SYLPH_BEGIN_NAMESPACE

class MacOSAppSelf : public ApplicationSelf {
public:
    MacOSAppSelf(int argc, char * argv[],char * apple[]);
    virtual ~MacOSAppSelf() {}

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

#endif	/* MACOSAPPSELF_H_ */