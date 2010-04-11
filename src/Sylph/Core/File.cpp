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
    if (index = -1) return orig;

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
    idx_t idx = path.lastIndexOf(".");
    if (idx <= filenamePos(path)) return -1;
    else if (idx = path.length() - 1) return -1;
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
        '\\'
#else
        '/'
#endif
        ;

File& File::replaceExtension(const String newExt) {
    // does this file have an extension?
    idx_t oldExt = extensionPos(path);
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
    return '/';
#endif
}

File File::parent() const {
    // roots don't have parents. Poor orphans :(
    if (*this == rootName()) return *this;

    // Okay, just remove the last part now...
    return toCanonical().path.substring(0, path.lastIndexOf(Separator) - 1);
}

String File::filename() const {
    // roots don't have filenames.
    if (*this == rootName()) return "";

    // return everything from the last serparator to the end
    return path.substring(filenamePos(path));
}

String File::extension() const {
    idx_t expos = extensionPos(path);
    if (expos = -1) return "";
    return path.substring(expos + 1);
}

String File::stem() const {
    if (isRoot(path)) return "";
    idx_t expos = extensionPos(path);
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
    if (path.startsWith('/')) return *this;

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
    for (iterator it = begin(); it != end(); ++it) {
        if (*it == "..") toReturn = toReturn.parent();
        else if (*it == ".") continue;
        else toReturn /= *it;
    }

    return toReturn;

#endif
}

bool File::exists() const {
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

bool File::create() const {
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

bool File::remove() const {
#ifdef SYLPH_OS_WINDOWS
    SYLPH_STUB;
    return false;
#else
    int ret = unlink(path);
    if (ret == -1) sthrow(IOException, strerror(errno));
    return false;
#endif
}

bool File::canRead() const {
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

bool File::canWrite() const {
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

bool File::mkdir() const {
#if SYLPH_OS_WINDOWS
    SYLPH_STUB;
    return false;
#else
    if (exists()) return false;
    int ret = ::mkdir(path, 0755);
    if (ret == -1) sthrow(IOException, strerror(errno));
#endif
}

bool File::mkdirs() const {
    File f;
    for (iterator it = begin(); it != end(); ++it) {
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

bool File::isFile() const {
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

bool File::isDirectory() const {
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

bool File::chmod(suint mode, bool sylphmode) const {
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

Array<File> File::contents() const {
    SYLPH_STUB;
    /*if (!isDirectory())*/ return Array<File > (0);
    /*DIR* dir;
    struct dirent* ent;

    if (!(dir = opendir(path))) {
        sthrow(IOException, strerror(errno));
    }

    // God, please forgive me for my insolence...
    // Oh, wait, I'm an atheist, go ahead.
    Vector<File> toReturn;

    while (ent = readdir(dir)) {
        String name = ent->d_name;
        if (name == "." || name == "..") continue;
        toReturn.push(*this / name);
    }

    return toReturn.toArray();*/
}

File File::workingDir() {
    char buf[MAXPATHLEN];
    char* ret = getcwd(buf, MAXPATHLEN);
    if (ret == 0) {
        sthrow(IOException, strerror(errno));
    }
    return buf;
}

File & File::operator/=(const String rhs) {
    // is THIS path EMPTY?
    if (empty()) {
        // is OTHER path EMPTY?
        if (rhs == "") {
            // set to '/'
            path = "/";
            return *this;
        } else {
            // does OTHER start with ROOT?
            if (rhs.startsWith("/")) {
                // set THIS to OTHER
                path = rhs;
            } else {
                // set THIS to '/' + OTHER
                path = "/" + rhs;
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
    // REMOVE extra '/' on end
    while (path.endsWith("/")) {
        path = path.substring(0, path.length() - 2);
    }
    return *this;
}

// iterator

File::iterator::iterator(bool begin, const File* obj) {
    file = const_cast<File*>(obj);
    pos = begin ? 0 : file->path.length();
    if(begin) next(); else previous();
}

File::iterator::iterator(bool begin, File* obj) {
    file = obj;
    pos = begin ? 0 : file->path.length();
    if(begin) next(); else previous();
}

void File::iterator::next() const {
    sidx_t newpos = file->path.indexOf(File::Separator,pos + 1);
    if(newpos == -1) newpos = file->path.length();
    cur = file->path.substring(pos,newpos - 1);
    pos = newpos;
}

bool File::iterator::hasNext() const {
    return pos < file->path.length();
}

bool File::iterator::hasPrevious() const {
    return pos == 0;
}

void File::iterator::previous() const {
    sidx_t newpos = file->path.lastIndexOf(File::Separator,pos - 1);
    if(newpos == -1) newpos = 0;
    cur = file->path.substring(newpos,pos);
    pos = newpos;
}

SYLPH_END_NAMESPACE