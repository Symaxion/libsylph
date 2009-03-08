#include "WindowsAppSelf.h"
#include "Sylph/Core/File.h"

#include <string>

SYLPH_START_NAMESPACE(OS)

namespace SC = Sylph::Core;

void WindowsAppSelf::construct(int argc, char * argv[], char * apple[]) {
    _me = argv[0];
}

const SC::File * WindowsAppSelf::getBundle() {
    return NULL;
}

const SC::File * WindowsAppSelf::getPrefix() {
    if (_prefix == NULL) {
        _prefix = new SC::File(_me->getParent());
    }
    return _prefix;
}

const SC::File * WindowsAppSelf::getResourceDir() {
    if (_resourcedir == NULL) {
        _resourcedir = new SC::File(getPrefix(), "data");
    }
    return _resourcedir;
}

SYLPH_END_NAMESPACE(OS)
