/*
 * File:   file.cpp
 * Author: frank
 *
 * Created on 16 november 2008, 18:02
 */

#include "File.h"

#include <boost/filesystem.hpp>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace fs = boost::filesystem;

SYLPH_START_NAMESPACE(Core)

    bool File::exists() {
        return fs::exists(*__path);
    }

    bool File::isFile() {
        return exists() && !isDirectory();
    }

    bool File::isDirectory() {
        return fs::is_directory(*__path);
    }

    bool File::canRead() {
        if (!exists()) return getParent().canRead();
        int descr = open(_location.c_str(), O_RDONLY);
        bool toReturn;
        if(descr == -1 && errno == EACCES) toReturn=false; else toReturn = true;
        close(descr);
        return toReturn;
    }
    bool File::canWrite() {
        if(!exists()) return getParent().canWrite();
        int descr = open(_location.c_str(), O_WRONLY);
        bool toReturn;
        if(descr == -1 && errno == EACCES) toReturn=false; else toReturn = true;
        close(descr);
        return toReturn;
    }
    void File::setPerm(unsigned short perm) throw (Exception) {
        int res = chmod(_location.c_str(), perm);
        if(res == -1) sthrow(FileException,"Unable to chmod file "+_location);
    }

    void File::mkdir() throw (Exception) {
        bool b = fs::create_directory(*__path);
        if(!b) sthrow (FileException,"Error while creating directory "+_location);
    }
    void File::mkdirs() throw (Exception) {
        bool b = fs::create_directories(*__path);
        if(!b) sthrow (FileException,"Error while creating directories "+_location);
    }
    vector<File> File::getContents() throw (Exception) {
        if(!isDirectory()) sthrow (FileException,_location+" is not a directory!");
        if(!canRead()) sthrow (FileException,_location+" is not readable!");
        vector<File> toReturn;
        fs::directory_iterator end_iter;
         for ( fs::directory_iterator dir_itr(*__path );dir_itr != end_iter; ++dir_itr ) {
             File f(dir_itr->string());
             toReturn.push_back(f);
         }
        return toReturn;

    }
    vector<File> File::getContents(IO::FileFilter & filt) throw (Exception) {
        vector<File> allFiles = getContents();
        vector<File> toReturn;
        for(vector<File>::iterator itr = allFiles.begin(); itr != allFiles.end(); itr++) {
            if(filt.accept(*itr)) toReturn.push_back(*itr);
        }
        return toReturn;

    }
    vector<File> File::getContents(IO::FileNameFilter & filt) throw (Exception) {
        vector<File> allFiles = getContents();
        vector<File> toReturn;
        for(vector<File>::iterator itr = allFiles.begin(); itr != allFiles.end(); itr++) {
            if(filt.accept((*itr).getParent(), (*itr).__path->filename()))
                 toReturn.push_back(*itr);
        }
        return toReturn;
    }
    bool File::contains(const string & name) throw(Exception) {
        vector<File> temp = getContents();
         for(vector<File>::iterator itr = temp.begin(); itr != temp.end(); itr++) {
             if((*itr).getFilename() == name) return true;
        }
        return false;
    }

    const string File::getFilename() {
        return __path->filename();
    }

    File File::getParent() throw(Exception) {
    	return __path->parent_path().filename();
    }

    File::~File() {
        // *I* *HATE* *DESTRUCTORS* -- can't they just use GC?
        delete __path;
    }

    File & File::operator=(const File & other) {
        if(this!=&other) {
            _location=other._location;
        }
        return *this;
    }

    bool File::operator==(const File & other) const {
        // Just use boost's hard work.
        return __path == other.__path;
    }
    bool File::operator!=(const File & other) const {
        return !(*this==other);
    }

    const string & File::toAbsolutePath(const string & relativePath) {
        __path = new fs::path(fs::system_complete(relativePath));
        return __path->string();
    }
    const string & File::fromParent(const File & parent, const string & name) {
        __path = new fs::path(fs::system_complete(parent._location) / name);
        return __path->string();

SYLPH_END_NAMESPACE(Core)
}
