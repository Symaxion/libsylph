/*
 * File:   library.h
 * Author: frank
 *
 * Created on 23 november 2008, 15:23
 */

#ifndef _LIBRARY_H
#define	_LIBRARY_H

#include "Object.h"
#include "File.h"

namespace Sylph {
namespace Core {

	SYLPH_PUBLIC
    class Library : public Object {
    public:
    	Library();
        virtual ~Library();
        const string & location();
        const File getBundle();
        const File getResourceDir();
    private:
        string _location;

    };
}
}

#endif	/* _LIBRARY_H */

