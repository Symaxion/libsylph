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

#ifdef SYLPH_OS_WINDOWS
#include <windows.h>
#include <stdlib.h>

// TODO: maybe expose this publicly?
const char* WindowsStringToCString(LPTSTR buf) {
#ifdef UNICODE
    size_t buflen = WideCharToMultiByte(CP_UTF8, 0, buf, -1, NULL, 0, 
            NULL, NULL);
    char* newbuf = malloc(buflen);
    WideCharToMultiByte(CP_UTF8, 0, buf, -1, newbuf, buflen, NULL, NULL);
    return newbuf;
#else
    return buf;
#endif
}

const char* WindowsModuleLocator(const HMODULE mod) {
    size_t size = 1024;
    LPTSTR buf = 0;

    do {
        buf = (TCHAR*)realloc(buf, size);
        GetModuleFileName(mod, buf, 255);
        size <<= 1;
    } while(GetLastError() == ERROR_INSUFFICIENT_BUFFER);

    return WindowsStringToCString(buf);
}

const char* WindowsExeLocator() {
    return WindowsModuleLocator(0);
}

const char* WindowsLibLocator(const void* symbol) {
    MEMORY_BASIC_INFORMATION mbi;
    VirtualQuery(&symbol,&mbi,sizeof(mbi));
    HMODULE mod = mbi.AllocationBase;

    return WindowsModuleLocator(mod);
}

const char* (*ExeLocator)() = WindowsExeLocator;
const char* (*LibLocator)(const void*) = WindowsLibLocator;

#endif

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
