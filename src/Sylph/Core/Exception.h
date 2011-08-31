/*
 * LibSylph Class Library
 * Copyright (C) 2011 Frank "SeySayux" Erens <seysayux@gmail.com>
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
 * Created on 14 november 2008, 8:07
 */

#ifndef EXCEPTION_H_
#define	EXCEPTION_H_

#include "Object.h"

#include <exception>
#include <cstdio>

#include "Primitives.h"
#include "CurrentFunction.h"

SYLPH_BEGIN_NAMESPACE

/**
 * This class provides a ready-to-use interface for exception handling. Several
 * macros are provided to make using this Exception class easier. An example is
 * the <code>sthrow()</code> macro, which is designed to replace the normal
 * <code>throw</code> keywoard.
 * <pre>void Foo::foobar(const Bar & bar) {
 *     if(bar.myint &lt; 0)
 *        sthrow(IllegalArgumentException,
 *           "Cannot foobar() when Bar::myint < 0");
 *     else {
 *       // ...
 *     }
 * }</pre>
 * <code>sthrow</code> adds certain debug information, i.e. file and line
 * numbers, if compilation with the debug flag (<code>-DSYLPH_DEBUG</code>) is
 * enabled. Therefore one should prefer <code>sthrow()</code> over <code>
 * throw</code><p>
 * To create your own Exception class, use the 
 * <code>S_CREATE_EXCEPTION(</code><i>Name</i><code>)</code> macro. This will
 * ensure that everything that is required is in your exception.  A new class
 * with name '<i>Name</i>' will be created in the current scope. It extends
 * Sylph::Exception, therefore you can catch all exceptions created with this
 * macro through <code>catch(const Exception& ex)</code>. <p>
 * Two other macros are defined as well, namely @c strace and @c straced. These
 * allow you to add trace information to an Exception (i.e. the name of the
 * current function). An example is given below:
 * <pre>
 * void foobar() {
 *     try {
 *        someDangerousFunction();
 *     } strace;
 * }
 * </pre>
 * <code>straced</code> works similar to <code>strace</code>, but only works
 * when debug mode (<code>-DSYLPH_DEBUG</code>) is enabled.<p>
 * Two other useful macros are defined, <code>if_nullptr()</code> and <code>
 * check_nullptr()</code>. <code>if_nullptr()</code> works similar to a normal
 * <code>if</code>, but the statements block is only executed when the pointer
 * passed is <code>null</code>. However, this macro is more optimized than a
 * normal if. <code>check_nullptr()</code> works similar, but instead of
 * executing a block of code, it will immeadiately throw an
 * NullPointerException.
 */
class Exception : public std::exception {
public:
    /**
     * Creates a new Exception. You should not use this directly, instead, use
     * <code>sthrow()</code>
     * @param r The reason why this Exception got thrown. This is the second
     * parameter to @c sthrow().
     * @param f The file this Exception got thrown in. This will automatically
     * be filled in by @c sthrow() if the macro @c SYLPH_DEBUG is defined, else
     * it defaults to the string "unknown".
     * @param l The line number on which this Exception got thrown. This will
     * automatically be filled in by @c sthrow() if the macro @c SYLPH_DEBUG is
     * defined, else it defaults to 0.
     */

    Exception(const char * r = "", const char * f = "unknown",
            const unsigned int l = 0)
    throw () : _reason(r), _file(f), _line(l), tracemsg(0) {
    }

    /**
     * Default destructor. Frees the memory used by the trace info. If this
     * Exception contains to trace info, this destructor does nothing.
     */
    virtual ~Exception() throw () {
        TraceMessage * current = tracemsg;
        while(current != null) {
            TraceMessage * tmp = current;
            current = tmp->next;
            delete tmp;
        }
    }

    /**
     * Returns the reason why this Exception was thrown, i.e.\ the second
     * parameter to <code>sthrow()</code>.
     * @return The reason why this Exception was thrown.
     */
    const char* what() const throw () {
        return _reason;
    }

    /**
     * Returns the class name of this Exception. If you used the <code>
     * S_CREATE_EXCEPTION(</code><i>name</i><code>)</code> macro, this will
     * be automatically filled in for you. Otherwise you'll have to put in
     * the name yourself. This is purely diagnostic information.
     * @return The name of the class of this Exception.
     */
    virtual const char* name() const throw() {
        return "Exception";
    }

    /**
     * This function adds a message to the trace information inside this
     * Exception. It can be useful to add the name of a function the Exception
     * passes through (i.e. what <code>strace</code> does), or any other
     * information you like to add to the Exception. This information is purely
     * diagnostic.
     * @param message The message to add in the traceinfo log.
     */
    void addTraceMessage(const char * message) const throw() {
        if(tracemsg == null) {
            tracemsg = new TraceMessage{message,null};
        } else {
            TraceMessage * current = tracemsg;
            while(current->next != null) {
                current = current->next;
            }
            current->next = new TraceMessage{message,null};
        }
    }

protected:
    const char * _reason;
public:
    const char * _file;
    const unsigned int _line;
    
    mutable struct TraceMessage {
        mutable const char * message;
        mutable TraceMessage * next;
    } * tracemsg;

};

#define S_CREATE_EXCEPTION(Class) \
class Class : public ::Sylph::Exception { \
public: \
    Class(const char * r = "", const char * f = "unknown", \
            const unsigned int l = 0) \
    throw () : ::Sylph::Exception(r,f,l) { \
    } \
    virtual const char* name() const throw() {\
        return #Class ; \
    }\
}

#define S_CREATE_EXCEPTION2(Class,Base) \
class Class : public Base { \
public: \
    Class(const char * r = "", const char * f = "unknown", \
            const unsigned int l = 0) \
    throw () : Base(r,f,l) { \
    } \
    virtual const char* name() const throw() {\
        return #Class ; \
    }\
}

/**
 * A generic Exception when an error occurs with an Array. Examples of such
 * errors are Array overflow or underflow, Array length too short or too long,
 * ...
 */
S_CREATE_EXCEPTION(ArrayException);
/**
 * A generic exception for an unexpected value supplied to a parser.
 */
S_CREATE_EXCEPTION(ParseException);
/**
 * This is a generic exception for I/O errors. It can get thrown for example
 * when a file doesn't exist, when a file can't be accessed, when an socket
 * connection is down, etc...
 */
S_CREATE_EXCEPTION(IOException);
/**
 * Generic exception to flag an argument with an illegal state was passed to an
 * function or method.
 */
S_CREATE_EXCEPTION(IllegalArgumentException);
/**
 * Generic exception to flag that a method is not supported in the current
 * state of the object it is invoked on.
 */
S_CREATE_EXCEPTION(IllegalStateException);
/**
 * This Exception gets thrown when a pointer to <code>null</code> is passed to
 * a function or method. It also gets automatically thrown by the <code>
 * check_nullptr()</code> macro.
 */
S_CREATE_EXCEPTION(NullPointerException);
/**
 * This Exception gets thrown if there is a problem with serializing or
 * deserializing an object.
 */
S_CREATE_EXCEPTION(SerializationException);

SYLPH_END_NAMESPACE


#ifdef SYLPH_DEBUG
#define sthrow(__x, __r) throw __x(__r, __FILE__, __LINE__)
#else
#define sthrow(__x, __r) throw __x(__r)
#endif

#define strace \
catch(::Sylph::Exception& ex) { \
    char buf[2048]; \
    sprintf(buf,"Function: `%s\'", S_CURRENT_FUNCTION); \
    ex.addTraceMessage(buf); \
    throw; \
} do{} while(0)
#ifdef SYLPH_DEBUG
#define straced strace
#else
#define straced \
catch(::Sylph::Exception& ex) { \
    throw; \
} do{} while(0)
#endif

#define if_nullptr(__x) if(SYLPH_UNLIKELY(__x == 0))
#define check_nullptr(__x) if_nullptr(__x) sthrow (NullPointerException, \
    "Dereferenced a null pointer")
        
#endif	/* EXCEPTION_H_ */

