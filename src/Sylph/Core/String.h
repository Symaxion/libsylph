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

class QString;

SYLPH_START_NAMESPACE(Core)
SYLPH_PUBLIC

class String : public Object, public virtual Hashable {
    friend bool operator==(const String lhs, const char * rhs);
    friend bool operator==(const String lhs, const std::string & rhs);
    friend bool operator==(const String lhs, const String rhs);
    friend bool operator==(String lhs, QString rhs);

    friend bool operator<(String lhs, const char * rhs);
    friend bool operator<(String lhs, const std::string & rhs);
    friend bool operator<(String lhs, const String rhs);
    friend bool operator<(String lhs, const QString rhs);

    friend String operator+=(const String lhs, const char * rhs);
    friend String operator+=(const String lhs, const std::string & rhs);
    friend String operator+=(const String lhs, const String rhs);
    friend String operator+=(const String lhs, const QString rhs);

    friend String operator+(const String lhs, const char * rhs);
    friend String operator+(const String lhs, const std::string & rhs);
    friend String operator+(const String lhs, const String rhs);
    friend String operator+(const String lhs, const QString rhs);

public:
    String();
    String(const char * orig);
    String(const std::string & orig);
    String(const QString orig);
    String(const String orig);
    virtual ~String();

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
    String substring(std::size_t begin, std::size_t end = length());

    static String valueOf(bool b);
    static String valueOf(char c);
    static String valueOf(int i);
    static String valueOf(long l);
    static String valueOf(float f);
    static String valueOf(double d);

    String copy() const;
    int hashCode();
    
    String operator=(const char * orig);
    String operator=(const std::string & orig);
    String operator=(const QString orig);
    String operator=(const String orig);

    operator const char *() const;
    operator std::string() const;
    operator QString() const;

private:
    struct Data {
        Array<wchar_t> * data = NULL;
        std::size_t length;
        std::size_t refcount = 0;
    } * strdata;

};

bool operator==(const String lhs, const char * rhs);
bool operator==(const String lhs, const std::string & rhs);
bool operator==(const String lhs, const String rhs);
bool operator==(String lhs, QString rhs);

bool operator<(String lhs, const char * rhs);
bool operator<(String lhs, const std::string & rhs);
bool operator<(String lhs, const String rhs);
bool operator<(String lhs, const QString rhs);

String operator+=(const String lhs, const char * rhs);
String operator+=(const String lhs, const std::string & rhs);
String operator+=(const String lhs, const String rhs);
String operator+=(const String lhs, const QString rhs);

String operator+(const String lhs, const char * rhs);
String operator+(const String lhs, const std::string & rhs);
String operator+(const String lhs, const String rhs);
String operator+(const String lhs, const QString rhs);
SYLPH_END_NAMESPACE(Core)

#endif /* STRING_H_ */
