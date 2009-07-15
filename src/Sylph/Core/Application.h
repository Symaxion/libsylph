/*
 * File:   Application.h
 * Author: frank
 *
 * Created on 9 november 2008, 11:48
 */

#ifndef APPLICATION_H_
#define	APPLICATION_H_

#include "Object.h"
#include "Array.h"

#include "../../Sylph.h"


#define thisapp ::Sylph::Application::self_app

SYLPH_BEGIN_NAMESPACE

class ApplicationSelf;
class String;
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


    virtual const File& getBundle() = 0;
    virtual const File& getResourceDir() = 0;
    virtual const File& getPrefix() = 0;

protected:
    void _fail(const String appName, const String reason);
    void _fail(const String appName, const String reason,
            const String file, unsigned int line);

private:
    void _preconstruct();
    String _appName;
    AppType _appType;

    ApplicationSelf(int argc, char * argv[], char * apple[]) {
        _preconstruct();
        construct(argc, argv, apple);
    }
    virtual ~ApplicationSelf();
    virtual void construct(int argc, char * argv[], char * apple[]) = 0;

};

SYLPH_END_NAMESPACE

#endif	/* APPLICATION_H_ */

