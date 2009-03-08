/* 
 * File:   Sylph.h
 * Author: frank
 *
 * Created on 17 januari 2009, 15:14
 */

#ifndef _SYLPH_H
#define	_SYLPH_H

#include "Sylph/OS/OS.h"
#include "Sylph/Core/Application.h"

namespace Sylph {
    enum AppType {
        S_APPTYPE_BUNDLE, S_APPTYPE_FHS, S_APPTYPE_MACOS, S_APPTYPE_MACOS_FHS,
        S_APPTYPE_WINDOWS
    };
    template<class T> T * newgc(T & t);
}

#ifdef SYLPH_OS_MACOSX
int main(int argc, char * argv[], char * envp[], char * apple[]);
#else
int main(int argc, char * argv[]);
#endif
static void SylphInit(int argc, char * argv[], char * apple[]) {
    Sylph::Core::Application::init(argc, argv, apple, APP_TYPE);
}
int SylphMain();

#endif	/* _SYLPH_H */

