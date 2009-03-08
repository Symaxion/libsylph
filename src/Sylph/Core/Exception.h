/*
 * File:   exception.h
 * Author: frank
 *
 * Created on 14 november 2008, 8:07
 */

#ifndef EXCEPTION_H_
#define	EXCEPTION_H_

#include "Object.h"

#include <exception>
#include <string>

SYLPH_START_NAMESPACE(Core)
    class Exception : public Object, public std::exception {
    protected:
        typedef const std::string string_t;
        string_t name;
        string_t reason;
    public:
        string_t file;
        const unsigned int line;
        
    public:
        Exception(string_t & n, string_t & r = "", string_t & f = "unknown", const unsigned int l = 0)
                throw() : name(n), reason(r), file(f), line(l) {}
        
        virtual ~Exception() throw() {};
        virtual const char* what() const throw() {
            return reason.c_str();
        }
        virtual string_t & name() { return name; }

    };
    
#ifdef SYLPH_DEBUG
    #define sthrow(__x) throw Sylph::Core::Exception(# __x, "", __FILE__, __LINE__)
    #define sthrow(__x, __r) throw Sylph::Core::Exception(# __x, __r, __FILE__, __LINE__)
#else
    #define sthrow(__x) throw Sylph::Core::Exception(# __x, "")
    #define sthrow(__x, __r) throw Sylph::Core::Exception(# __x, __r)
#endif

#define if_nullptr(__x) if(__builtin_expect(!!(__x) == 0, 0))
#define check_nullptr(__x) if_nullptr(__x) sthrow (NullPointerException, "Dereferenced a null pointer")
SYLPH_END_NAMESPACE(Core)
#endif	/* EXCEPTION_H_ */

