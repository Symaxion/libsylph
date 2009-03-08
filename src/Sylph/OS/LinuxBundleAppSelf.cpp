#include "LinuxBundleAppSelf.h"

#include <binreloc.h>

#include <string>

SYLPH_START_NAMESPACE(OS)

namespace SC = Sylph::Core;

void LinuxBundleAppSelf::construct(int argc, char * argv[], char * apple[]) {
    // First, make binreloc work...
    BrInitError error;

    if (br_init(&error) == 0 && error != BR_INIT_ERROR_DISABLED)
        _fail("LibSylph", "Couldn't init binreloc!", __FILE__, __LINE__);
    _location = br_find_exe("");
    if (_location == "") {
        _fail("LibSylph", "Couldn't init binreloc!", __FILE__, __LINE__);
    }

}

const SC::File * LinuxBundleAppSelf::getBundle() {
    if (_bundle == NULL) {
        _bundle = new SC::File(br_dirname(br_find_prefix("")));
    }
    return _bundle;
}

const SC::File * LinuxBundleAppSelf::getPrefix() {
    if (_prefix == NULL) {
        _prefix = new SC::File(br_find_prefix(""));
    }
    return _prefix;
}

const SC::File * LinuxBundleAppSelf::getResourceDir() {
    if (_resourcedir == NULL) {
        _resourcedir = new SC::File(getBundle(), "Resources");
    }
    return _resourcedir;
}

SYLPH_END_NAMESPACE(OS)