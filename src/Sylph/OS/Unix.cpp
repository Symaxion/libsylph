/*
 * LibSylph Class Library
 * Copyright (C) 2012 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not
 *   claim that you wrote the original software. If you use this software
 *   in a product, an acknowledgment in the product documentation would be
 *   appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not be
 *   misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any source
 *   distribution.
 */

#include "GuessOS.h"

#ifdef SYLPH_OS_POSIX

#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

static char* systrdup(const char *in) {
    char* toreturn;
    size_t len;

    len = strlen(in) + 1;

    toreturn = (char*)malloc(len);
    memcpy(toreturn, in, len);

    return toreturn;
}

const char* DladdrLibLocator(const void* symbol) {
    Dl_info info;

    dladdr(symbol, &info);
    
    return systrdup(info.dli_fname);
} 

#endif

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
