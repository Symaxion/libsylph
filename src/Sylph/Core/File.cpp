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
 *
 */

#include "File.h"
#include "Primitives.h"
#include "../OS/GuessOS.h"
#include "StringBuffer.h"
#include "Debug.h"
#include "Vector.h"
#ifdef SYLPH_OS_WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <dirent.h>
#endif

SYLPH_BEGIN_NAMESPACE

#ifdef SYLPH_OS_WINDOWS
#warning "Sylph::File does not have Win32 support yet!"
#endif

//helper functions

// we need a replace function, but String doesn't yet have one -- using this
// one temporarily
// note -- only replaces first occurrence
String simple_replace(String orig, String replacee, String replacement,
        bool last = false) {
    // does the original contain the replacee?
    sidx_t index = last ? orig.lastIndexOf(replacee) : orig.indexOf(replacee);
    // nope.
    if (index == -1) return orig;

    StringBuffer buf;
    buf << orig.substring(0, index) << replacement <<
            orig.substring(index + replacement.length(), orig.length() - 1);

    return buf;
}

sidx_t filenamePos(String path) {
    // filename = everthing from last serparator
    return path.lastIndexOf(File::Separator) + 1;
}

sidx_t extensionPos(String path) {
    sidx_t idx = path.lastIndexOf(".");
    if (idx <= filenamePos(path)) return -1;
    else if (idx == sidx_t(path.length() - 1)) return -1;
    return idx;
}

bool isRoot(String path) {
#ifdef SYLPH_OS_WINDOWS
    return path.length() <= 3 && path.length() >= 2 && path[1] = ':';
#else
    return path == '/'
#endif
            ;
}

// end of helpers

const String File::Separator =
#ifdef SYLPH_OS_WINDOWS
        uchar('\\')
#else
        uchar('/')
#endif
;

File& File::replaceExtension(const String newExt) {
    // does this file have an extension?
    sidx_t oldExt = extensionPos(path);
    if (oldExt == -1) {
        // nope. Does it end in a . ?
        if (SYLPH_UNLIKELY(path.endsWith("."))) {
            // no need to add one
            path += newExt;
        } else {
            // nope, add a . ourselves.
            path += ("." + newExt);
        }
        return *this;
    }
    // okay, it already has one. String::replace doesn't exist yet, so...
    path = simple_replace(path, extension(), newExt, true);
    return *this;
}

String File::rootName() const {
#ifdef SYLPH_OS_WINDOWS
    // assume C for the moment
    return "C:\\";
#else
    // while Unix can have a different root, assume '/' for the moment
    return uchar('/');
#endif
}

File File::parent() const {
    // roots don't have parents. Poor orphans :(
    if (*this == rootName()) return *this;

    // Okay, just remove the last part now...
    String canonc = toCanonical().path;
    return canonc.substring(0, canonc.lastIndexOf(Separator) - 1);
}

String File::filename() const {
    // roots don't have filenames.
    if (*this == rootName()) return "";

    // return everything from the last serparator to the end
    return path.substring(filenamePos(path));
}

String File::extension() const {
    sidx_t expos = extensionPos(path);
    if (expos == -1) return "";
    return path.substring(expos + 1);
}

String File::stem() const {
    if (isRoot(path)) return "";
    sidx_t expos = extensionPos(path);
    return path.substring(filenamePos(path), expos == -1 ? path.length() - 1 :
            expos - 1);
}

bool File::absolute() const {
#ifdef SYLPH_OS_WINDOWS
    // assume C
    SYLPH_STUB;
    return path.startsWith("C:") || path.startsWith("c:");
#else
    return path.startsWith("/");
#endif
}

bool File::canonical() const {
    return this->path == toCanonical().path;
}

File File::toAbsolute() const {
#ifdef SYLPH_OS_WINDOWS
    //winsux
    SYLPH_STUB;
    return "";
#else
    // does it already start with a '/'?
    if (path.startsWith(uchar('/'))) return *this;

    // nope... Okay, assume it's relative to this directory.
    return workingDir() / path;

#endif

}

File File::toCanonical() const {
#ifdef SYLPH_OS_WINDOWS
    SYLPH_STUB;
    return "";
#else
    // first make it absolute
    String absolutePath = toAbsolute().path;

    // if it ends in /. it can safely be removed
    if (absolutePath.endsWith("/."))
        absolutePath = absolutePath.substring(0, absolutePath.length() - 3);
    File toReturn;
    for (const_iterator it = begin(); it != end(); ++it) {
        if (*it == "..") toReturn = toReturn.parent();
        else if (*it == ".") continue;
        else toReturn /= *it;
    }

    return toReturn;

#endif
}

bool File::exists() const throw(IOException) {
#ifdef SYLPH_OS_WINDOWS
    SYLPH_STUB;
    return true;
#else
    int ret = access(path, F_OK);
    if (ret == -1) {
        if (errno == ENOENT) return false;
        else sthrow(IOException, strerror(errno));
    }
    return true;
#endif
}

bool File::create() const throw(IOException) {
#ifdef SYLPH_OS_WINDOWS
    SYLPH_STUB;
    return false;
#else
    if (exists()) return false;
    int fd = open(path, O_CREAT | O_WRONLY, 0755);
    if (fd == -1) {
        sthrow(IOException, strerror(errno));
    } else {
        close(fd);
        return true;
    }
#endif

}

bool File::remove() const throw(IOException) {
#ifdef SYLPH_OS_WINDOWS
    SYLPH_STUB;
    return false;
#else
    int ret = unlink(path);
    if (ret == -1) sthrow(IOException, strerror(errno));
    return false;
#endif
}

bool File::canRead() const throw(IOException) {
#ifdef SYLPH_OS_WINDOWS
    SYLPH_STUB;
    return true;
#else
    if (!exists() && parent().canRead()) return true;
    int ret = access(path, R_OK);
    if (ret == -1) {
        if (errno == EACCES) return false;
        else sthrow(IOException, strerror(errno));
    }
    return true;
#endif
}

bool File::canWrite() const throw(IOException) {
#ifdef SYLPH_OS_WINDOWS
    SYLPH_STUB;
    return true;
#else
    if (!exists() && parent().canWrite()) return true;
    int ret = access(path, W_OK);
    if (ret == -1) {
        if (errno == EACCES) return false;
        else sthrow(IOException, strerror(errno));
    }
    return true;
#endif
}

bool File::mkdir() const throw(IOException) {
#if SYLPH_OS_WINDOWS
    SYLPH_STUB;
    return false;
#else
    if (exists()) return false;
    int ret = ::mkdir(path, 0755);
    if (ret == -1) sthrow(IOException, strerror(errno));
    else return true;
#endif
}

bool File::mkdirs() const throw(IOException) {
    File f;
    for (const_iterator it = begin(); it != end(); ++it) {
        if (f.exists()) {
            f /= *it;
            continue;
        } else {
            f /= *it;
            if (!f.mkdir()) return false;
        }
    }
    return true;
}

bool File::isFile() const throw(IOException) {
#ifdef SYLPH_OS_WINDOWS
    SYLPH_STUB_FUNCTION;
    return false;
#else
    if (!exists()) return false;
    struct stat info;
    int ret = stat(path, &info);
    if (ret == -1) sthrow(IOException, strerror(errno));
    return info.st_mode & S_IFREG;
#endif
}

bool File::isDirectory() const throw(IOException) {
#ifdef SYLPH_OS_WINDOWS
    SYLPH_STUB_FUNCTION;
    return false;
#else
    if (!exists()) return false;
    struct stat info;
    int ret = stat(path, &info);
    if (ret == -1) sthrow(IOException, strerror(errno));
    return info.st_mode & S_IFDIR;
#endif
}

bool File::chmod(suint mode, bool sylphmode) const throw(IOException) {
#ifdef SYLPH_OS_WINDOWS
    // windows doesn't support chmodding. ever.
    return false;
#else
    if (!sylphmode) {
        int ret = ::chmod(path, mode);
        if (ret == -1) sthrow(IOException, strerror(errno));
        else return true;
    } else {
        struct stat info;
        int ret = stat(path, &info);
        if (ret == -1) sthrow(IOException, strerror(errno));
        suint permnow = info.st_mode;
        suint newperm = 0;

        suint owner = mode & S_MOD_OWN;
        if (owner >= 0x800) {
            newperm |= (permnow & 0700);
        }
        if (mode & S_MOD_R * S_MOD_OWN) newperm |= 0400;
        if (mode & S_MOD_W * S_MOD_OWN) newperm |= 0200;
        if (mode & S_MOD_X * S_MOD_OWN) newperm |= 0100;

        // same for group and world

        suint group = mode & S_MOD_GRP;
        if (group >= 0x80) {
            newperm |= (permnow & 070);
        }
        if (mode & S_MOD_R * S_MOD_GRP) newperm |= 040;
        if (mode & S_MOD_W * S_MOD_GRP) newperm |= 020;
        if (mode & S_MOD_X * S_MOD_GRP) newperm |= 010;

        suint world = mode & S_MOD_OTH;
        if (world >= 0x8) {
            newperm |= (permnow & 07);
        }
        if (mode & S_MOD_R * S_MOD_OTH) newperm |= 04;
        if (mode & S_MOD_W * S_MOD_OTH) newperm |= 02;
        if (mode & S_MOD_X * S_MOD_OTH) newperm |= 01;

        int ret2 = ::chmod(path, newperm);
        if (ret2 == -1) sthrow(IOException, strerror(errno));
        else return true;
    }
#endif
}

Array<File> File::contents() const throw(IOException) {
    if (!isDirectory()) return Array<File > (0);
    DIR* dir;
    struct dirent* ent;

    if (!(dir = opendir(path))) {
        sthrow(IOException, strerror(errno));
    }

    Vector<File> toReturn;

    while ((ent = readdir(dir))) {
        String name = ent->d_name;
        if (name == "." || name == "..") continue;
        toReturn.add(*this / name);
    }

    return toReturn.toArray();
}

File File::workingDir() throw(IOException) {
    char buf[MAXPATHLEN];
    char* ret = getcwd(buf, MAXPATHLEN);
    if (ret == 0) {
        sthrow(IOException, strerror(errno));
    }
    return buf;
}

File& File::operator/=(const String rhs) {
    return append(rhs, false);
}

File& File::append(const String rhs, bool initial) {
    // is THIS path EMPTY?
    if (empty()) {
        // is OTHER path EMPTY?
        if (rhs == "") {
            // is this INITIAL?
            if (initial) {
                // set EMPTY
                path = "";
            } else {
                // set to '/'
                path = "/";
            }
            return *this;
        } else {
            // does OTHER start with ROOT?
            if (rhs.startsWith("/")) {
                // set THIS to OTHER
                path = rhs;
            } else {
                // is this INITIAL?
                if (initial) {
                    // set THIS to OTHER
                    path = rhs;
                } else {
                    // set THIS to '/' + OTHER
                    path = "/" + rhs;
                }
            }
        }
        // is THIS path ROOT?
    } else if (path == "/") {
        // does OTHER start with ROOT?
        if (rhs.startsWith("/")) {
            // set THIS to OTHER
            path = rhs;
        } else {
            // append OTHER to THIS
            path += rhs;
        }
    } else {
        // does THIS end on '/'?
        if (path.endsWith("/")) {
            // REMOVE extra '/'
            while (path.endsWith("/")) {
                path = path.substring(0, path.length() - 2);
            }
        }
        // does OTHER start with '/'?
        if (rhs.startsWith("/")) {
            path += rhs;
        } else {
            path += ("/" + rhs);
        }
    }

    if (path != "/") {
        // REMOVE extra '/' on end
        while (path.endsWith("/")) {
            path = path.substring(0, path.length() - 2);
        }
    }
    return *this;
}

// iterator

template<class C, class V>
File::S_ITERATOR<C,V>::S_ITERATOR(bool begin, C* obj) : super(begin) {
    file = obj;
    pos = begin ? 0 : file->path.length() - 1;
    if (begin) next();
}

template<class C, class V>
void File::S_ITERATOR<C,V>::next() {
    sidx_t start = 0;
    if (pos == 0) {
        start = 1;
    } else {
        start = file->path.indexOf(File::Separator, pos);
        if (start == -1) {
            pos = file->path.length();
            return;
        } else {
            ++start;
        }
    }

    sidx_t end = file->path.indexOf(File::Separator, start);
    if (end == -1) {
        end = file->path.length();
    }

    --end;

    cur = file->path.substring(start, end);
    pos = end;
}

template<class C, class V>
bool File::S_ITERATOR<C,V>::hasNext() const {
    return pos < file->path.length() - 1;
}

template<class C, class V>
bool File::S_ITERATOR<C,V>::hasPrevious() const {
    return pos != 0;
}

template<class C, class V>
void File::S_ITERATOR<C,V>::previous() {
    SYLPH_STUB;
}

SYLPH_END_NAMESPACE

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
