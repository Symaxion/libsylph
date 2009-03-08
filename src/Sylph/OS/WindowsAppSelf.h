/* 
 * File:   WindowsAppSelf.h
 * Author: frank
 *
 * Created on 30 januari 2009, 9:21
 */

#ifndef _WINDOWSAPPSELF_H
#define	_WINDOWSAPPSELF_H

#include "../Core/Application.h"

SYLPH_START_NAMESPACE(OS)

namespace SC = Sylph::Core;

class WindowsAppSelf : public SC::ApplicationSelf {
public:
    WindowsAppSelf(int argc, char * argv[]) :
         SC::ApplicationSelf(argc,argv,NULL) {}
    virtual ~WindowsAppSelf() {}
    void construct(int argc, char * argv[], char * apple[]);
    const SC::File * getBundle();
    const SC::File * getResourceDir();
    const SC::File * getPrefix();
private:
    SC::File * _me;

    SC::File * _prefix;
    SC::File * _resourcedir;
};

SYLPH_END_NAMESPACE(OS)

#endif	/* _WINDOWSAPPSELF_H */

