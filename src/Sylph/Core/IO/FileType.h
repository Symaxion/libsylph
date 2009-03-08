/*
 * File:   FileType.h
 * Author: frank
 *
 * Created on 19 november 2008, 8:14
 */

#ifndef _FILETYPE_H
#define	_FILETYPE_H

#include "../Object.h"
#include <string>

namespace Sylph {
namespace Core {
    namespace IO {

        using namespace std;

        class FileType : public Object {
        public:
            FileType(const string & name) : name(name) {}
            virtual ~FileType() {}
            const string name;
        private:


        };

    }
}
}

#endif	/* _FILETYPE_H */

