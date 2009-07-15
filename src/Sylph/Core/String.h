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
#include "Primitives.h"
#include "Hashable.h"
#include "BoolConvertible.h"

#include <cstdint>
#include <string>

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

typedef std::uint16_t uchar;

static Array<uchar> spacechars = {' ','\n','\r','\f','\t','\013'};

class SYLPH_STRING_CLASS : public Hashable, 
        public BoolConvertible<SYLPH_STRING_CLASS> {
    friend bool operator==(const String lhs, const String rhs);
    friend bool operator<(const String lhs, const String rhs);
    friend String operator+(const String lhs, const String rhs);
    //friend String operator%(const String lhs, const String rhs);
    friend String operator&(const String lhs, const String(*rhs)(String));
    friend String operator&(const String(*lhs)(String), const String rhs);
    friend String operator*(const String lhs, const std::size_t len);
    friend String operator<<(std::ostream& lhs, const String rhs);

public:
    SYLPH_STRING_CLASS();
    SYLPH_STRING_CLASS(const char * orig);
    SYLPH_STRING_CLASS(const Array<char> orig);
    SYLPH_STRING_CLASS(const Array<uchar> orig);
    SYLPH_STRING_CLASS(const std::string & orig);
    SYLPH_STRING_CLASS(const QString & orig);
    SYLPH_STRING_CLASS(const String & orig);
    SYLPH_STRING_CLASS(const char c);
    SYLPH_STRING_CLASS(const bool b);
    SYLPH_STRING_CLASS(const sint i);
    SYLPH_STRING_CLASS(const suint i);
    SYLPH_STRING_CLASS(const slong l);
    SYLPH_STRING_CLASS(const sulong l);
    SYLPH_STRING_CLASS(const float f);
    SYLPH_STRING_CLASS(const double d);
    virtual ~SYLPH_STRING_CLASS();

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

    String fromHex(int,bool up);
    String fromOct(int, bool up);
    String fromSci(float, bool up);
    String fromSci(double, bool up);

    bool boolValue() const;
    sint intValue() const;
    suint uintValue() const;
    slong longValue() const;
    sulong ulongValue() const;
    float floatValue() const;
    double doubleValue() const;

    inline bool toBool() {
        return *this != "";
    }
    
    String& operator=(const char * orig) const;
    String& operator=(const std::string & orig) const;
    String& operator=(const String orig) const;

    String& operator+=(const String rhs) const;

    operator const char *() const;
    operator std::string() const;

private:
    void fromAscii(const char* ascii) const;
    void fromUtf8(const char* unicode) const;
    mutable struct Data {
        Data(size_t len) : data(len),refcount(1) {}
        Array<uchar> data;
        std::size_t refcount;
    } * strdata;

};

bool operator==(const String lhs, const String rhs);
bool operator<(const String lhs, const String rhs);
String operator+(const String lhs, const String rhs);
//String operator%(const String lhs, const String rhs);
String operator&(const String lhs, const String(*rhs)(String));
String operator&(const String(*lhs)(String), const String rhs);
String operator*(const String lhs, const std::size_t len);
std::ostream& operator<<(std::ostream& lhs, const String rhs);

String tr(String rhs);
String lc(String rhs);
String uc(String rhs);
String t(String rhs);

SYLPH_END_NAMESPACE

#endif /* STRING_H_ */
