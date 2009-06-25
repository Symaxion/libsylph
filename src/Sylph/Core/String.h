/*
 * String.h
 *
 *  Created on: 26-nov-2008
 *      Author: frank
 */

#ifndef STRING_H_
#define STRING_H_

#include "Object.h"
#include "Comparable.h"
#include "Hashable.h"

#include <string>

/*< rev Object-1
 *  rev Hashable-1
 *  rev String-1
 >*/

class QString;

SYLPH_BEGIN_NAMESPACE

template<class T> class Array;

#ifndef SYLPH_DOXYGEN
#define SYLPH_STRING_CLASS MutableString
class MutableString;
typedef const MutableString String;
#else
#define SYLPH_STRING_CLASS String
#endif

SYLPH_PUBLIC

class SYLPH_STRING_CLASS : public Hashable {
    friend bool operator==(const String lhs, const char * rhs);
    friend bool operator==(const String lhs, const std::string & rhs);
    friend bool operator==(const String lhs, const String rhs);
    friend bool operator==(const String lhs, const QString rhs);

    friend bool operator<(const String lhs, const char * rhs);
    friend bool operator<(const String lhs, const std::string & rhs);
    friend bool operator<(const String lhs, const String rhs);
    friend bool operator<(const String lhs, const QString rhs);

    friend String operator+=(const String lhs, const char * rhs);
    friend String operator+=(const String lhs, const std::string & rhs);
    friend String operator+=(const String lhs, const String rhs);
    friend String operator+=(const String lhs, const QString rhs);

    friend String operator+(const String lhs, const char * rhs);
    friend String operator+(const String lhs, const std::string & rhs);
    friend String operator+(const String lhs, const String rhs);
    friend String operator+(const String lhs, const QString rhs);

    friend String operator%(const String lhs, const String rhs);
    friend String operator&(const String lhs, const String(*rhs)(String));
    friend String operator&(const String(*lhs)(String), const String rhs);
    friend String operator*(const String lhs, const std::size_t len);

public:
    SYLPH_STRING_CLASS();
    SYLPH_STRING_CLASS(const char * orig);
    SYLPH_STRING_CLASS(const std::string & orig);
    SYLPH_STRING_CLASS(const QString orig);
    SYLPH_STRING_CLASS(const String & orig);
    virtual ~SYLPH_STRING_CLASS();

    std::size_t length() const;
    wchar_t at(std::size_t idx) const;
    const char * latin1() const;
    const char * ascii() const;
    const char * utf8() const;
    const wchar_t utf16() const;

    String toLowerCase() const;
    String toUpperCase() const;
    bool equalsIgnoreCase(const String other) const;

    bool endsWith(const String other) const;
    bool startsWith(const String other) const;

    String trim() const;
    String substring(std::size_t begin) const;
    String substring(std::size_t begin, std::size_t end) const;

    static String valueOf(bool b);
    static String valueOf(char c);
    static String valueOf(int i);
    static String valueOf(long l);
    static String valueOf(float f);
    static String valueOf(double d);

    String copy() const;
    int hashCode() const;
    
    String operator=(const char * orig);
    String operator=(const std::string & orig);
    String operator=(const QString orig);
    String operator=(const String orig);

    operator const char *() const;
    operator std::string() const;
    operator QString() const;

private:
    struct Data {
        Array<wchar_t> * data;
        std::size_t length;
        std::size_t refcount;
    } * strdata;

};

bool operator==(const String lhs, const char * rhs);
bool operator==(const String lhs, const std::string & rhs);
bool operator==(const String lhs, const String rhs);
bool operator==(const String lhs, const QString rhs);

bool operator<(const String lhs, const char * rhs);
bool operator<(const String lhs, const std::string & rhs);
bool operator<(const String lhs, const String rhs);
bool operator<(const String lhs, const QString rhs);

String operator+=(const String lhs, const char * rhs);
String operator+=(const String lhs, const std::string & rhs);
String operator+=(const String lhs, const String rhs);
String operator+=(const String lhs, const QString rhs);

String operator+(const String lhs, const char * rhs);
String operator+(const String lhs, const std::string & rhs);
String operator+(const String lhs, const String rhs);
String operator+(const String lhs, const QString rhs);

String operator%(const String lhs, const String rhs);
String operator&(const String lhs, const String(*rhs)(String));
String operator&(const String(*lhs)(String), const String rhs);
String operator*(const String lhs, const std::size_t len);

String tr(String rhs);

SYLPH_END_NAMESPACE

#endif /* STRING_H_ */
