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
 *
 * Created on 9 november 2008, 11:48
 */

#ifndef SYLPH_CORE_APPLICATION_H_
#define	SYLPH_CORE_APPLICATION_H_

#include "Object.h"
#include "Array.h"
#include "String.h"

#include "AppType.h"

#include "../OS/GuessOS.h"


#define thisapp ::Sylph::Application::self_app

SYLPH_BEGIN_NAMESPACE

class ApplicationSelf;
class File;

template<class T> class Array;
class String;


/**
 * Class representing an application. An application a combination of an
 * executable file with any resources required to run it.<p>
 * An executable file is any file containing executable object code that can be
 * directly invoked by the operating system through a well-defined entry point.
 * Probably the most important example of an instance of this class is
 * @c a pointer to an Application object representing the application from
 * which it is dereferenced.<p>
 * An application is considered <i>relocatable</i> if and only if, once built
 * for a specific target, the application can be run from any absolute path
 * on that target and can be run on any other compatible system, without
 * needing to be rebuilt.
 * An application is considered <i>self-contained</i> if and only if the
 * application ships with all required resources and frameworks, except for
 * standard or very common libraries, all these files are in one directory
 * hierarchy and this directory hierarchy is not shared with other applications.
 * Futhermore, each self-contained application must be relocatable.
 * It is not possible to directly instantiate an Application object. Future
 * releases may contain functions to create Application objects and run the
 * accompanying object code.
 */
class Application : public Object {
    friend class ApplicationSelf;
public:

    /**
     * Returns the location of the file containing the object code of the
     * application.<p>
     * In case the application for which the location is requested is
     * @c thisapp, the exact method used to determine the location is
     * platform-dependant and may fail. In this case, the value is either set
     * to an empty string or a garbage value. Depending on the implementation,
     * an error may be raised as well during initialisation.
     * @return the application's location.
     */
    const String location() {
        return _location;
    }

    static ApplicationSelf * self_app;

    /**
     * Initialize the current application. This function will give the correct
     * value to @c thisapp. Note that if you use <code>int
     * SylphMain(Array<String>)</code> as the entry point for your application
     * (the default), you do not need  to call this function explicitly.
     * Instead, it will be called for you  before the SylphMain function.
     * Depending on the implementation, this function may or may not set up
     * other important resources.
     * @param argc The number of arguments passed to the entry point designated
     * by the platform.
     * @param argv An array of C strings containing the arguments passed to
     * the entry point designated by the platform. This array is expected to
     * have a length of argc or more. If argc is larger than the actual length
     * of argv, undefined behaviour may occur.
     * @param apple The so-called 'apple-vector', an array of chars unique to
     * the Mac OS X-platform. This array is used to determine the location of
     * the binary solely on the Mac platform and is the fourth argument to the
     * @c main entry function. On other platforms, this array may be substituted
     * by a @c null pointer. Substituting this array on the Mac platform for
     * anything else than the actual apple vector passed to the @c main function
     * may lead to undefined behaviour.
     * @param type An enumerated type representing the implementation to use
     * for resource retrieval.
     * @param name The name of the application. Used in debug messages and for
     * retrieving configuration files.
     */
    static void init(int argc, char * argv[], char * apple[], AppType type,
            String name);

protected:
    String _location;

private:
    Application();
    virtual ~Application();


};

/**
 * An Application representing the currently running application. You cannot
 * directly instantiate this class. You need to implement this classes' methods
 * and use Application::init for correct initialisation. The constant @c thisapp
 * is of the type ApplicationSelf. It contains some extra methods that are not
 * available for ordinary applications.
 */
class ApplicationSelf : public Application {
    friend class Application;
public:
    const String appName() {
        return _appName;
    }

    /**
     * Returns an enumerated type representing the implementation used to back
     * this ApplicationSelf. The returned value is set by Application::init.
     * @return an enumeration corresponding to the implementation of
     * ApplicationSelf used.
     */
    AppType appType();

    /**
     * Closes the application with a given error message. The exact way this
     * error message is displayed is not specified, however, it is usually
     * displayed on the terminal. The application will send a failure status
     * code to the operating system.
     * @param reason The error message that will be displayed to the user.
     * @param exit Whether the application will exit after showing the failure.
     * This is useful to do some manual clean-up before exiting. Not exiting
     * after using this function is undefined behavior.
     */
    void fail(const String reason, bool exit = true);
    /**
     * Closes the application with a given error message. The exact way this
     * error message is displayed is not specified, however, it is usually
     * displayed on the terminal. The application will send a failure status
     * code to the operating system.<p>
     * This function is usually called as <code>fail("Error", __FILE__,
     * __LINE__)</code> so that the preprocessor may substitute the parameters.
     * @param reason The error message that will be displayed to the user.
     * @param file The source code file this error occured in.
     * @param line The source code line this error occured on.
     * @param exit Whether the application will exit after showing the failure.
     * This is useful to do some manual clean-up before exiting. Not exiting
     * after using this function is undefined behavior.
     */
    void fail(const String reason, const String file, unsigned int line,
        bool exit = true);


    /**
     * Returns the canonical path to the bundle this executable is part of.
     * If this application isn't part of a bundle, the empty file will be
     * returned. 
     * @return The canonical path to the bundle this executable is part of.
     */
    virtual const File& bundle() = 0;
    /**
     * Returns the path to the resource directory specific for this application.
     * @return A File object for this application's resources.
     */
    virtual const File& resourceDir() = 0;
    /**
     * Returns the path to a resource specific to this application.
     * @param rsc The path to a resource, relative to the resource directory
     * for this application.
     * @return A File object pointing to the resource with the given name.
     */
    virtual const File resource(String rsc) = 0;
    /**
     * Returns the path to the library directory specific for this application.
     * @return A File object pointing to the directory in this Application's
     * bundle for library files and framework bundles.
     */
    virtual const File& libraryDir() = 0;
    /**
     * Returns the path to the directory for storing plugins specific for this
     * application.
     */
    virtual const File& pluginDir() = 0;
    /** */
    virtual const File& plugindisabledDir() = 0;

    /** */
    virtual const File& systemLibraryDir() = 0;
    /** */
    virtual const File& systemSettings() = 0;
    /** */
    virtual const File& systemSettingsDir() = 0;
    /** */
    virtual const File& systemPluginDir() = 0;
    /** */
    virtual const File& systemPluginDisabledDir() = 0;
    /** */
    virtual const File& systemResourceDir() = 0;
    /** */
    virtual const File systemResource(String rsc) = 0;

    virtual const File& userHome() = 0;

    /** */
    virtual const File& userLibraryDir() = 0;
    /** */
    virtual const File& userSettings() = 0;
    /** */
    virtual const File& userSettingsDir() = 0;
    /** */
    virtual const File& userPluginDir() = 0;
    /** */
    virtual const File& userPluginDisabledDir() = 0;
    /** */
    virtual const File& userResourceDir() = 0;
    /** */
    virtual const File userResource(String rsc) = 0;

    /**
     * @return The grandfather of the executable in of this file.
     */
    virtual const File& prefix() = 0;

protected:
    ApplicationSelf() {
        _preconstruct();
    }
    virtual ~ApplicationSelf();

    void _fail(const String appName, const String reason, bool exit = true);
    void _fail(const String appName, const String reason,
            const String file, unsigned int line, bool exit = true);

private:
    void _preconstruct();
    String _appName;
    AppType _appType;


};

SYLPH_END_NAMESPACE

#endif	/* SYLPH_CORE_APPLICATION_H_ */

// vim: ts=4:sts=4:sw=4:sta:et:tw=80:nobk
