/* 
 * File:   MacOSAppSelf.h
 * Author: frank
 *
 * Created on 30 januari 2009, 9:20
 */

#ifndef _MACOSAPPSELF_H
#define	_MACOSAPPSELF_H

#include "../Core/Application.h"

SYLPH_START_NAMESPACE(OS)

namespace SC = Sylph::Core;

class MacOSAppSelf : public SC::ApplicationSelf {
public:
    MacOSAppSelf(int argc, char * argv[],char * apple[]) :
         SC::ApplicationSelf(argc,argv,apple) {}
    virtual ~MacOSAppSelf() {}
    void construct(int argc, char * argv[], char * apple[]);
    const SC::File * getBundle();
    const SC::File * getResourceDir();
    const SC::File * getPrefix();
private:
    SC::File * _me;

    SC::File * _bundle;
    SC::File * _prefix;
    SC::File * _resourcedir;
};

SYLPH_END_NAMESPACE(OS)

#endif	/* _MACOSAPPSELF_H */

