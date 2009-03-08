/* 
 * File:   MacOSFHSAppSelf.h
 * Author: frank
 *
 * Created on 30 januari 2009, 9:21
 */

#ifndef _MACOSFHSAPPSELF_H
#define	_MACOSFHSAPPSELF_H

#include "../Core/Application.h"

SYLPH_START_NAMESPACE(OS)

namespace SC = Sylph::Core;

class MacOSFHSAppSelf : public SC::ApplicationSelf {
public:
    MacOSFHSAppSelf(int argc, char * argv[],char * apple[]) :
         SC::ApplicationSelf(argc,argv,apple) {}
    virtual ~MacOSFHSAppSelf() {}
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

#endif	/* _MACOSFHSAPPSELF_H */

