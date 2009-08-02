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
 * Created on 9 november 2008, 11:48
 */

#ifndef APPLICATION_H_
#define	APPLICATION_H_

#include "Object.h"
#include "Array.h"
#include "String.h"

#include "AppType.h"


#define thisapp ::Sylph::Application::self_app

SYLPH_BEGIN_NAMESPACE

class ApplicationSelf;
class File;

template<class T> class Array;

SYLPH_PUBLIC
class Application : public Object {
    friend class ApplicationSelf;
public:

    const String location() {
        return _location;
    }

    static ApplicationSelf * self_app;

    static void init(int argc, char * argv[], char * apple[], AppType type);

protected:
    String _location;

private:
    Application();
    virtual ~Application();


};

class ApplicationSelf : public Application {
    friend class Application;
public:
    const String appName() {
        return _appName;
    }

    AppType appType();

    void fail(const String reason);
    void fail(const String reason, const String file, unsigned int line);


    virtual const File& bundle() = 0;
    virtual const File& resourceDir() = 0;
    virtual const File& resource(String rsc) = 0;
    virtual const File& libraryDir() = 0;
    virtual const File& pluginDir() = 0;
    virtual const File& plugindisabledDir() = 0;

    virtual const File& systemLibraryDir() = 0;
    virtual const File& systemSettings() = 0;
    virtual const File& systemSettingsDir() = 0;
    virtual const File& systemPluginDir() = 0;
    virtual const File& systemPluginDisabledDir() = 0;
    virtual const File& systemResourceDir() = 0;
    virtual const File& systemResource(String rsc) = 0;

    virtual const File& userHome() = 0;

    virtual const File& userLibraryDir() = 0;
    virtual const File& userSettings() = 0;
    virtual const File& userSettingsDir() = 0;
    virtual const File& userPluginDir() = 0;
    virtual const File& userPluginDisabledDir() = 0;
    virtual const File& userResourceDir() = 0;
    virtual const File& userResource(String rsc) = 0;

    virtual const File& prefix() = 0;

protected:
    ApplicationSelf() {
        _preconstruct();
    }
    virtual ~ApplicationSelf();

    void _fail(const String appName, const String reason);
    void _fail(const String appName, const String reason,
            const String file, unsigned int line);

private:
    void _preconstruct();
    String _appName;
    AppType _appType;


};

SYLPH_END_NAMESPACE

#endif	/* APPLICATION_H_ */

