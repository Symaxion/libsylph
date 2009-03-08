/*
 * File:   mylib.h
 * Author: frank
 *
 * Created on 23 november 2008, 15:29
 */

#ifndef _MYLIB_H
#define	_MYLIB_H

#include <Sylph/Core/Object.h>
#include <Sylph/Core/Library.h>

#ifndef SYLPH_MYLIB_FULL_NAMESPACE
#define SYLPH_MYLIB_FULL_NAMESPACE
#endif

#ifndef SYLPH_MYLIB_NAMESPACE_BEGIN
#define SYLPH_MYLIB_NAMESPACE_BEGIN
#endif

#ifndef SYLPH_MYLIB_NAMESPACE_END
#define SYLPH_MYLIB_NAMESPACE_END
#endif

#define thislib ::SYLPH_MYLIB_FULL_NAMESPACE::mylib::lib_self

SYLPH_MYLIB_NAMESPACE_BEGIN
class mylib : public ::sylph::object {
public:
    static ::sylph::Library * lib_self = new ::sylph::Library();

};
::sylph::Library mylib::lib_self;

SYLPH_MYLIB_NAMESPACE_END

#endif	/* _MYLIB_H */

