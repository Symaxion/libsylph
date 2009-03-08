/*
 * File:   application.h
 * Author: frank
 *
 * Created on 9 november 2008, 11:48
 */

#ifndef _APPLICATION_H
#define	_APPLICATION_H

#include "Object.h"

#include "../../Sylph.h"

#include <vector>
#include <string>

#define thisapp ::Sylph::Core::Application::self_app

SYLPH_START_NAMESPACE(Core)
        using namespace std;

        class ApplicationSelf;
        class File;

        SYLPH_PUBLIC
        class Application : public Object {
            friend class ApplicationSelf;
        public:

            const string & location() {
                return _location;
            }

            static ApplicationSelf * self_app;

            static void init(int argc, char * argv[], char * apple[], AppType type);

        protected:

            string _location;

        private:
            Application();
            virtual ~Application();


        };

        ApplicationSelf * Application::self_app;

        class ApplicationSelf : public Application {
            friend class Application;
        public:

            const vector<string> & arguments() {
                return _arguments;
            }

            const string & appName() {
                return _appName;
            }

            AppType appType();

            void fail(const string & reason);
            void fail(const string & reason, const string & file, int line);


            virtual const File * getBundle() = 0;
            virtual const File * getResourceDir() = 0;
            virtual const File * getPrefix() = 0;

        protected:
            void _fail(const string & appName, const string & reason);
            void _fail(const string & appName, const string & reason,
                    const string & file, int line);

        private:
            void _preconstruct();
            vector<string> _arguments;
            string _appName;
            AppType _appType;

            ApplicationSelf(int argc, char * argv[], char * apple[]) : _arguments(argv, argv + argc) {
                _preconstruct();
                construct(argc, argv, apple);
            }
            virtual ~ApplicationSelf();
            virtual void construct(int argc, char * argv[], char * apple[]) = 0;

        };

SYLPH_END_NAMESPACE(Core)

#endif	/* _APPLICATION_H */

