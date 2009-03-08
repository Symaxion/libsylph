#include "MacOSAppSelf.h"
#include "Sylph/Core/File.h"

#include <binreloc.h>

#include <string>

SYLPH_START_NAMESPACE(OS)

namespace SC = Sylph::Core;

void MacOSFHSAppSelf::construct(int argc, char * argv[], char * apple[]) {
    _me = new SC::File(apple[0]);
}

const SC::File * MacOSFHSAppSelf::getBundle() {
    return NULL;
}

const SC::File * MacOSFHSAppSelf::getPrefix() {
    if (_prefix == NULL) {
        _prefix = new SC::File(_me->getParent().getParent());
    }
    return _prefix;
}

const SC::File * MacOSFHSAppSelf::getResourceDir() {
    if (_resourcedir == NULL) {
        _resourcedir = new SC::File(getBundle(), "share");
    }
    return _resourcedir;
}

SYLPH_END_NAMESPACE(OS)
