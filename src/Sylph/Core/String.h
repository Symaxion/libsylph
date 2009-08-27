/*
 * LibSylph Class Library
 * Copyright (C) 2009 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LibSylph Pulbic License as published
 * by the LibSylph Developers; either version 1.0 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LibSylph
 * Public License for more details.
 *
 * You should have received a copy of the LibSylph Public License
 * along with this Library, if not, contact the LibSylph Developers.
 *
 * Created on: 26 november 2008
 */

#ifndef STRING_H_
#define STRING_H_

#include "Object.h"
#include "Comparable.h"
#include "Primitives.h"
#include "Hashable.h"
#include "BoolConvertible.h"
#include "Array.h"

// for convenience
#include "I18N.h"

#include <cstdint>
#include <string>

SYLPH_BEGIN_NAMESPACE

SYLPH_PUBLIC

/**
 * A integral type for storing an UTF-16 character
 */
typedef std::uint16_t uchar;

/**
 * This array contains the characters that are considered to be whitespace
 * characters by default. The following shows the contents of this list:
 * <ul>
 * <li> space (Unicode U+0020, character literal ' ') </li>
 * <li> newline (Unicode U+000A, character literal '\n')</li>
 * <li> carriage return (Unicode U+000D, character literal '\r')</li>
 * <li> form feed (Unicode U+000C, character literal '\f')</li>
 * <li> horizontal tab (Unicode U+0009, character literal '\t')</li>
 * <li> vertical tab (Unicode U+000B, character literal '\v' or '\013')</li>
 * </ul><p>
 * Certain functions, such as String::trim() and String::split() use this array
 * to determine a default set of characters to look after.
 */
static Array<uchar> spacechars = {' ', '\n', '\r', '\f', '\t', '\013'};

/**
 * The String class represents character strings. All strings used in LibSylph
 * are instances of this class. <p>
 * Strings are constant, their value can not be changed after they are created.
 * StringBuffer implements a mutable string. The copy constructor only copies
 * a pointer to the actual internal data, making Strings trivial to copy,
 * they should therefore be treated as built-in types, such as ints and floats.
 * <p>The class String includes methods for examining individual characters of
 * the sequence, for comparing strings, for searching strings, for extracting
 * substrings, and for creating a copy of a string with all characters
 * translated to uppercase or to lowercase. Case mapping relies heavily on the
 * information provided by the Unicode Consortium's Unicode 2.0 specification.
 * The specification's UnicodeData.txt and SpecialCasing.txt files are used
 * extensively to provide case mapping. For specific details, please refer
 * to the ICU library documentation.<p>
 * Strings are encoded internally in UTF-16, but only the Basic Multilinguar
 * Plane (up to U+FFFF) is supported. Future versions may add support for the
 * other planes (up to U+10FFFF). In this case, UTF-32 will be used instead.
 */
class String : public Hashable, public BoolConvertible<String> {
    friend bool operator==(const String lhs, const String rhs);
    friend bool operator<(const String lhs, const String rhs);
    friend String operator+(const String lhs, const String rhs);
    //friend String operator%(const String lhs, const String rhs);
    friend String operator&(const String lhs, const String(*rhs)(const String));
    friend String operator&(const String(*lhs)(String), const String rhs);
    friend String operator*(const String lhs, const std::size_t len);
    friend std::ostream & operator<<(std::ostream& lhs, const String rhs);

public:
    /**
     * Creates an empty String. An empty String has a length of 0 and does not
     * contain any internal data. All empty Strings are equal to each other.
     * <p>Since Strings are immutable, the main use of this constructor is to
     * compare against the empty string, or to supply a dummy value to a
     * function.
     */
    String();
    /**
     * Creates a String from a C-style string. The pointer passed must be a
     * pointer to a null ('\0') terminated character array. The length is
     * of the character array is deduced from the place of the null character.
     * Passing anything else than a null-terminated character array to this
     * constructor may result in undefined behaviour. <p>
     * The character array passed is expected to be encoded in UTF-8. Any other
     * encodings, or invalid UTF-8, may result in Unicode replacement
     * characters ('�', U+FFFD) to be inserted into the character sequence.<p>
     * The characters in the original string will be converted to UTF-16.
     * The original string will not be modified.<p>
     * An example:
     * <pre>String foo = "abc";
     * String bar("def");</pre>
     * @param orig A c-style null terminated string encoded in UTF-8
     */
    String(const char * orig);

    String(const Array<uchar> orig);
    String(const std::string & orig);
    String(const String & orig);
    String(const char c);
    String(const bool b);
    String(const sint i);
    String(const suint i);
    String(const slong l);
    String(const sulong l);
    String(const float f);
    String(const double d);
    virtual ~String();

    std::size_t length() const;
    const uchar at(std::size_t idx) const;
    const char * ascii() const;
    const char * utf8() const;
    const Array<uchar> utf16() const;

    String toLowerCase() const;
    String toUpperCase() const;
    bool equalsIgnoreCase(const String other) const;

    bool endsWith(const String other) const;
    bool startsWith(const String other) const;
    bool contains(const String other) const;

    String trim() const;
    String substring(std::idx_t begin) const;
    String substring(std::idx_t begin, std::idx_t end) const;

    sidx_t indexOf(const String substr, idx_t start = 0) const;
    sidx_t lastIndexOf(const String substr) const;
    sidx_t lastIndexOf(const String substr, idx_t start) const;

    String copy() const;
    bool merge(String other) const;
    int hashCode() const;

    static String fromHex(int, bool up);
    static String fromOct(int, bool up);
    static String fromSci(float, bool up);
    static String fromSci(double, bool up);

    bool boolValue() const;
    sint intValue() const;
    suint uintValue() const;
    slong longValue() const;
    sulong ulongValue() const;
    float floatValue() const;
    double doubleValue() const;

    inline bool toBool() const {
        return *this != "";
    }

    const String & operator=(const char * orig) const;
    const String & operator=(const std::string & orig) const;
    const String & operator=(const String orig) const;

    const String & operator+=(const String rhs) const;

    operator const char *() const;
    operator std::string() const;

    //private:
    void fromAscii(const char* ascii) const;
    void fromUtf8(const char* unicode) const;

    struct Data {

        Data(size_t len) : data(len), refcount(1) {
        }

        virtual ~Data() {
        }
        Array<uchar> data;
        mutable std::size_t refcount;
    };
    mutable Data * strdata;

};

bool operator==(const String lhs, const String rhs);

inline bool operator==(const String lhs, const char* rhs) {
    return operator==(lhs, String(rhs));
}

inline bool operator==(const char* rhs, const String lhs) {
    return operator==(String(rhs), lhs);
}
bool operator<(const String lhs, const String rhs);
String operator+(const String lhs, const String rhs);
//String operator%(const String lhs, const String rhs);
String operator&(const String lhs, String(*rhs)(const String));
String operator&(String(*lhs)(const String), const String rhs);
String operator*(const String lhs, const std::size_t len);
std::ostream & operator<<(std::ostream& lhs, const String rhs);

String lc(const String rhs);
String uc(const String rhs);
String t(const String rhs);

SYLPH_END_NAMESPACE

#endif /* STRING_H_ */
