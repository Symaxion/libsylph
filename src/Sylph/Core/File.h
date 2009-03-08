/*
 * File:   file.h
 * Author: frank
 *
 * Created on 16 november 2008, 18:02
 */

#ifndef FILE_H_
#define	FILE_H_

#include "Object.h"
#include "Exception.h"
#include "IO/FileFilter.h"
#include "IO/FileType.h"
#include "Boostdefs.h"

#include <string>
#include <vector>

SYLPH_START_NAMESPACE(Core)

        class Application;
        class Library;

        using namespace std;

        SYLPH_PUBLIC
        class File : public Object {
            friend class Application;
            friend class Library;
        public:

            File(const string & location) : _location(toAbsolutePath(location)) {
            }

            File(const File& orig) : _location(orig._location), __path(orig.__path) {
            }

            File(const File& parent, const string & name) :
            _location(fromParent(parent, name)) {
            }
            bool exists();
            bool isFile();
            bool isDirectory();
            bool isBundle();

            bool canRead();
            bool canWrite();
            void setPerm(unsigned short perm) throw (Exception);

            void mkdir() throw (Exception);
            void mkdirs() throw (Exception);
            vector<File> getContents() throw (Exception);
            vector<File> getContents(IO::FileFilter & filt) throw (Exception);
            vector<File> getContents(IO::FileNameFilter & filt) throw (Exception);
            bool contains(const string & name) throw (Exception);

            const string getFilename();

            File getParent() throw (Exception);
            const string getExtension();
            const string getBasename();
            const IO::FileType getFileType();

            virtual ~File();

            const string & location() {
                return _location;
            }

            File & operator=(const File & other);
            bool operator==(const File & other) const;
            bool operator!=(const File & other) const;
        private:
            string _location;
            /**
             * Helper Methods
             */
            const string & toAbsolutePath(const string & relativePath);
            const string & fromParent(const File & parent, const string & name);
            const ::boost::filesystem::path * __path;
        };
SYLPH_END_NAMESPACE(Core)

#endif	/* FILE_H_ */
