/*
 * File:   library.cpp
 * Author: frank
 *
 * Created on 23 november 2008, 15:23
 */

#include "Library.h"

#include <binreloc.h>
#include <gc.h>

namespace Sylph {
namespace Core {

    Library::Library() {
        BrInitError error;

        br_init_lib_from_symbol(this, &error);
        //TODO catch errors

        _location = br_find_exe("");

        GC_INIT();
    }

    Library::~Library() {

    }

    const string & Library::location() {
        return _location;

    }

    const File Library::getBundle() {
    	static std::string path;
    	if(path == "") path = br_find_prefix("");
        return path;
    }

    const File Library::getResourceDir() {
        return File(getBundle(),"Resources");
    }
}
}
