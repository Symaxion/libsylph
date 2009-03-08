/*
 * File:   boostdefs.h
 * Author: frank
 *
 * Created on 21 november 2008, 8:12
 */

#ifndef _BOOSTDEFS_H
#define	_BOOSTDEFS_H

#ifndef _OBJECT_H
#error Do not include __FILE__ directly!
#endif

#ifndef SYLPH_PUBLIC
#define SYLPH_PUBLIC
#endif

SYLPH_PUBLIC
namespace boost {
    namespace filesystem {
    template<class String, class Traits> class basic_path;

    struct path_traits;
    typedef basic_path< std::string, path_traits > path;
    }
}

#endif	/* _BOOSTDEFS_H */

