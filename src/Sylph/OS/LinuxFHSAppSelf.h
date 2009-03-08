/* 
 * File:   LinuxFHSAppSelf.h
 * Author: frank
 *
 * Created on 30 januari 2009, 9:20
 */

#ifndef _LINUXFHSAPPSELF_H
#define	_LINUXFHSAPPSELF_H

#include "../Core/Application.h"

SYLPH_START_NAMESPACE(OS)

namespace SC = Sylph::Core;

class LinuxFHSAppSelf : public SC::ApplicationSelf {
public:
    LinuxFHSAppSelf(int argc, char * argv[]) :
         SC::ApplicationSelf(argc,argv,NULL) {}
    virtual ~LinuxFHSAppSelf() {}
    void construct(int argc, char * argv[], char * apple[]);
    const SC::File * getBundle();
    const SC::File * getResourceDir();
    const SC::File * getPrefix();
private:
    SC::File * _prefix;
    SC::File * _resourcedir;
};

SYLPH_END_NAMESPACE(OS)

#endif	/* _LINUXFHSAPPSELF_H */

