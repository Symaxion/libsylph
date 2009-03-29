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
#include "String.h"

SYLPH_START_NAMESPACE(Core)

/**
 * This class provides a ready-to-use interface for exception handling. Unlike
 * most exception classes, you should not extend this class. Instead, use
 * the <code>sthrow</code> keyword to throw an Exception, like this:
 * <pre>void Foo::foobar(const Bar & bar) {
 *     if(bar.myint &lt; 0)
 *        sthrow(IllegalArgumentException,
 *           "Cannot foobar() when Bar::myint < 0");
 *     else {
 *       // ...
 *     }
 * }</pre>
 * <code>sthrow</code> will ensure that a Sylph::Core::Exception is thrown, even
 * when it is not in scope.
 * <code>sthrow</code> also adds certain debug information, i.e. file and line
 * numbers, if compilation with the debug flag (<code>-DSYLPH_DEBUG</code>) is
 * enabled. <p>
 * Note that in the example above, no class named
 * <code>IllegalArgumentException</code> actually exists. Instead, the name of
 * the Exception is stored in a String inside this class. Therefore, there are
 * no fixed Exception types, however, the following are recommended:
 * <ul>
 * <li> <code>ArrayException</code> -- A generic Exception thrown when trying
 * to access an item outside the bounds of an @c Array.</li>
 * <li> <code>FileException</code> -- A generic Exception thrown when a file is
 * is not of the supported type, e.g. a directory instead of a regular file.
 * When writing or reading from a file, throw an <code>IOException</code>
 * instead </li>
 * <li> <code>IllegalArgumentException</code> -- Similar to the
 * <code>IllegalStateException</code>, however, this Exception is meant
 * especially for arguments that do not conform to a given set of criteria,
 * where an <code>IllegalStateException</code> can also be thrown when certain
 * conditions, apart from arguments, are not met.</li>
 * <li> <code>IllegalStateException</code> -- The object on which to perform
 * the action is not in the right state, i.e. a variable does not have the right
 * value to perform te action.</li>
 * <li> <code>IOException</code> -- This Exception is thrown whenever an I/O
 * operation, such as a read or a write to a file, or establishing a network
 * connection, failed. </li>
 * <li> <code>NullPointerException</code> -- This Exception is thrown by the
 * <code>check_nullptr()</code> macro. Like it name says, it denotes the
 * dereference of a null (0) pointer. </li>
 * <li> <code>SerialisationException</code> -- This Exception is thrown by
 * @c Serializer s and @c Deserializer s when the type of the serialised object
 * and the destination don't match, or when the object could not be serialised
 * due to another Exception, such as an I/O error. </li>
 * <li> <code>TodoException</code> -- similar to the
 * UnsupportedOperationException, however, this Exception type denotes that the
 * operation itself is supported, but not yet implemented by the programmer.
 * </li>
 * <li> <code>UnsupportedOperationException</code> -- this Exception is usually
 * thrown by classes that are derived from classes with only pure virtual
 * fucntions. This exception denotes that a particular action just doesn't make
 * sense in the case of the implementing class.</li>
 * </ul>
 */
class Exception : public Object, public std::exception {
public:
    /**
     * Creates a new Exception. You should not use this directly, instead, use
     * <code>sthrow()</code>
     */
    Exception(String n, String r = "", String f = "unknown", const unsigned int l = 0)
    throw () : _name(n), _reason(r), _file(f), _line(l) {
    }

    /**
     * Default destructor.
     */
    ~Exception() throw () {
    };

    /**
     * Returns the reason why this Exception was thrown, i.e.\ the second
     * parameter to <code>sthrow()</code>
     * @return The reason why this Exception was thrown.
     */
    const char* what() const throw () {
        return _reason.ascii();
    }

    /**
     * Returns the name of this Exception. The name denotes the unique type of
     * this Exception, and is used instead of subclassing. It is the first
     * parameter to <code>sthrow()</code>
     * @return The name of this Exception, as defined by <code>sthrow()</code>
     */
    String name() const throw () {
        return _name;
    }
private:
    const String _name;
    const String _reason;
public:
#ifndef SYLPH_DOXYGEN
    const String _file;
    const unsigned int _line;
#endif
};

#ifdef SYLPH_DEBUG
#define sthrow(__x, __r) throw Sylph::Core::Exception(# __x, __r, __FILE__, __LINE__)
#else
#define sthrow(__x, __r) throw Sylph::Core::Exception(# __x, __r)
#endif

#define if_nullptr(__x) if(__builtin_expect(!!(__x) == 0, 0))
#define check_nullptr(__x) if_nullptr(__x) sthrow (NullPointerException, "Dereferenced a null pointer")
SYLPH_END_NAMESPACE(Core)
#endif	/* EXCEPTION_H_ */

