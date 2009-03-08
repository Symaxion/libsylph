#include "MacOSAppSelf.h"
#include "Sylph/Core/File.h"

#include <binreloc.h>

#include <string>

SYLPH_START_NAMESPACE(OS)

namespace SC = Sylph::Core;

void MacOSAppSelf::construct(int argc, char * argv[], char * apple[]) {
    _me = new SC::File(apple[0]);
}

const SC::File * MacOSAppSelf::getBundle() {
    if (_bundle == NULL) {
        _bundle = new SC::File(_me->getParent().getParent().getParent());
    }
    return _bundle;
}

const SC::File * MacOSAppSelf::getPrefix() {
    if (_prefix == NULL) {
        _prefix = new SC::File(getBundle(),"Contents");
    }
    return _prefix;
}

const SC::File * MacOSAppSelf::getResourceDir() {
    if (_resourcedir == NULL) {
        _resourcedir = new SC::File(getBundle(), "Resources");
    }
    return _resourcedir;
}

SYLPH_END_NAMESPACE(OS)
