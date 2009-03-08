/* 
 * File:   LinuxBundleAppSelf.h
 * Author: frank
 *
 * Created on 30 januari 2009, 9:19
 */

#ifndef _LINUXBUNDLEAPPSELF_H
#define	_LINUXBUNDLEAPPSELF_H

#include "../Core/Application.h"

SYLPH_START_NAMESPACE(OS)

namespace SC = Sylph::Core;

class LinuxBundleAppSelf : public SC::ApplicationSelf {
public:
    LinuxBundleAppSelf(int argc, char * argv[]) :
         SC::ApplicationSelf(argc,argv,NULL) {}
    virtual ~LinuxBundleAppSelf() {}
    void construct(int argc, char * argv[], char * apple[]);
    const SC::File * getBundle();
    const SC::File * getResourceDir();
    const SC::File * getPrefix();
private:
    SC::File * _bundle;
    SC::File * _prefix;
    SC::File * _resourcedir;
};

SYLPH_END_NAMESPACE(OS)

#endif	/* _LINUXBUNDLEAPPSELF_H */

