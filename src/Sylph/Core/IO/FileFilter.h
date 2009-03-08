/*
 * File:   FileFilter.h
 * Author: frank
 *
 * Created on 17 november 2008, 18:50
 */

#ifndef _FILEFILTER_H
#define	_FILEFILTER_H

#include "../Object.h"

#include <string>

namespace Sylph {
namespace Core {
    class File;
    SYLPH_PUBLIC
    namespace IO {
        using namespace std;
        interface FileFilter : public Object {
        public:
            virtual ~FileFilter();
            virtual bool accept(File & pathname) = 0;
        protected:
            FileFilter() {}
        };

        interface FileNameFilter : public Object{
        public:
            virtual ~FileNameFilter();
            virtual bool accept (File parent, string name) = 0;
        protected:
            FileNameFilter() {}
        };


    }
}
}

#endif	/* _FILEFILTER_H */

