/*
 * LibSylph Class Library
 * Copyright (C) 2010 Frank "SeySayux" Erens <seysayux@gmail.com>
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
 */

#include "String.h"
#include "Array.h"
#include "Hash.h"
#include "StringBuffer.h"
#include "Util.h"
#include "Vector.h"

#include <cctype>
#include <cstring>
#include <cmath>

using std::isinf;
using std::isnan;

#include <unicode/uchar.h>
#include <unicode/ustring.h>
#include <gc/gc.h>

SYLPH_BEGIN_NAMESPACE

bool startsWithHelper(idx_t from, const String& left, const String& right) {
    if (left.length() - from < right.length()) return false;
    suint count = 0;
    for (idx_t i = 0; i < right.length(); i++) {
        if (left.at(i + from) == right.at(i)) {
            count++;
            if(count == right.length()) return true;
        }
        else break;
    }
    return false;
}

bool endsWithHelper(idx_t from, const String& left, const String& right) {
    if (from < right.length() - 1) {
        return false;
    }
    suint count = 0;
    for (idx_t i = 0; i < right.length(); i++) {
        if (left.at(from - i) == right.at(-i-1)) {
            count++;
            if(count == right.length()) return true;
        } else break;
    }
    return false;
}

//////////////////////////////////////////////////////////////////////

String::String() {
    strdata = new Data(0);
}

String::String(const char * orig) {
    fromUtf8(orig);
}

String::String(const Array<uchar> orig) {
    strdata = new Data(0);
    strdata->data = orig.copy();
}

String::String(const std::string& orig) {
    // std::string's always ascii...
    fromAscii(orig.c_str());
}

String::String(const String& orig) {
    // refcounted
    this->strdata = orig.strdata;
    this->strdata->refcount++;
}

String::String(const uchar c) {
    strdata = new Data(1);
    strdata->data[0] = c;
}

String::String(const bool b) {
    fromAscii(b ? "true" : "false");
}

String::String(const sint i) {
    size_t tmplen = sizeof (i) * 5; // long enough, i presume?
    char * buf = new char[tmplen];
    sprintf(buf, "%"S_FMT_I, i);
    fromAscii(buf);
    delete[] buf;
}

String::String(const suint i) {
    size_t tmplen = sizeof (i) * 5; // long enough, i presume?
    char * buf = new char[tmplen];
    sprintf(buf, "%"S_FMT_UI, i);
    fromAscii(buf);
    delete[] buf;
}

String::String(const slong l) {
    size_t tmplen = sizeof (l) * 5; // long enough, i presume?
    char * buf = new char[tmplen];
    sprintf(buf, "%"S_FMT_L, l);
    fromAscii(buf);
    delete[] buf;
}

String::String(const sulong l) {
    size_t tmplen = sizeof (l) * 5; // long enough, i presume?
    char * buf = new char[tmplen];
    sprintf(buf, "%"S_FMT_UL, l);
    fromAscii(buf);
    delete[] buf;
}

String::String(const float f) {
    if (isinf(f)) {
        if (copysign(1.0, f) == -1.0) {
            fromAscii("-Infinity");
        } else {
            fromAscii("Infinity");
        }
    } else if (isnan(f)) {
        fromAscii("NaN");
    } else {
        char * buf = static_cast<char*>(GC_MALLOC_ATOMIC(20));
        sprintf(buf,"%.7g",f);
        fromAscii(buf);
    }
}

String::String(const double d) {
    if (isinf(d)) {
        if (copysign(1.0, d) == -1.0) {
            fromAscii("-Infinity");
        } else {
            fromAscii("Infinity");
        }
    } else if (isnan(d)) {
        fromAscii("NaN");
    } else {
        char * buf = static_cast<char*>(GC_MALLOC_ATOMIC(20));
        sprintf(buf,"%.16g",d);
        fromAscii(buf);
    }
}

String::~String() {
    strdata->refcount--;
    if (strdata->refcount == 0) {
        delete strdata;
        strdata = null;
    }
}

std::size_t String::length() const {
    return strdata->data.length;
}

const uchar String::at(sidx_t idx) const throw(ArrayException) {
    try {
        return strdata->data[idx];
    } straced;
}

const char * String::ascii() const {
    // all non-ascii chars will be converted to '?' literals.
    char * buf = (char*)GC_MALLOC_ATOMIC(length() + 1);
    for (idx_t i = 0; i < length(); i++) {
        if (at(i) > 0x7F) buf[i] = '?';
        else buf[i] = at(i);
    }
    return buf;
}

const char * String::utf8() const {
    // In the best case, the the buffer need to be length()+1. In the worst
    // case, it's 3 * length() + 1. Always prepare for the worst ;)
    char * buf = new char[3 * length() + 1];
    size_t buflen = 0;
    for (idx_t i = 0; i < length(); i++) {
        if (at(i) <= 0x7F) {
            // ascii
            buf[buflen] = at(i);
            buflen++;
        } else if (at(i) < 0x07FF) {
            // 2-byte
            buf[buflen] = 0xC0 | ((at(i) & 0x07C0) >> 6);
            buf[buflen + 1] = 0x80 | (at(i) & 0x3F);
            buflen += 2;
        } else {
            // 3-byte
            buf[buflen] = 0xE0 | ((at(i) & 0xF000) >> 12);
            buf[buflen + 1] = 0x80 | ((at(i) & 0x0FC0) >> 6);
            buf[buflen + 2] = 0x80 | (at(i) & 0x3F);
            buflen += 3;
        }
    }

    // now copy it to the final buffer...
    char * final = static_cast<char*>(GC_MALLOC_ATOMIC(buflen + 1));
    carraycopy(buf, 0, final, 0, buflen);
    final[buflen] = 0;
    delete[] buf;
    return final;
}

const Array<uchar> String::utf16() const {
    return strdata->data.copy();
}

String String::toLowerCase() const {
    Array<uchar> dest(length() << 1);
    UErrorCode error = U_ZERO_ERROR;
    size_t newlength = u_strToLower(dest.carray(), dest.length,
            strdata->data.carray(), length(), 0, &error);
    if(U_FAILURE(error)) {
        sthrow(Exception,u_errorName(error));
    }

    Array<uchar> toReturn(newlength);
    arraycopy(dest, 0, toReturn, 0, newlength);
    return toReturn;
}

String String::toUpperCase() const {
    Array<uchar> dest(length() << 1);
    UErrorCode error = U_ZERO_ERROR;
    size_t newlength = u_strToUpper(dest.carray(), dest.length,
            strdata->data.carray(), length(), 0, &error);

    if(U_FAILURE(error)) {
        sthrow(Exception,u_errorName(error));
    }

    Array<uchar> toReturn(newlength);
    arraycopy(dest, 0, toReturn, 0, newlength);
    return toReturn;
}

bool String::equalsIgnoreCase(const String other) const {
    return this->toLowerCase() == other.toLowerCase();
}

bool String::endsWith(const String other) const {
    return endsWithHelper(-1,*this,other);
}

bool String::startsWith(const String other) const {
    return startsWithHelper(0,*this, other);
}

bool String::contains(const String other) const {
    return indexOf(other) != -1;
}

String String::trim() const {
    size_t beginct = 0;
    size_t endct = length() - 1;
    for (idx_t i = 0; i < this->length(); i++) {
        if (isspace(this->at(i))) beginct++;
        else break;
    }
    for (idx_t i = (length() - 1); i > 0; i--) {
        if (isspace(this->at(i))) endct--;
        else break;
    }
    return substring(beginct, endct);
}

Array<String> String::split(Array<uchar> delimiters) const {
    Vector<String> toReturn;

    idx_t start = 0;
    idx_t end = 0;

    for(idx_t i = 0; i < length(); ++i) {
        for(idx_t j = 0; j < delimiters.length; ++j) {
            if(at(i) == delimiters[j]) {
                end = i;
                if(start != end) toReturn.add(substring(start,end-1));
                start = end + 1;
            }
        }
    }

    return toReturn.toArray();
}

String String::substring(idx_t begin) const throw(ArrayException) {
    return substring(begin, length()-1);
}

String String::substring(idx_t begin, idx_t end) const throw(ArrayException) {
    return String(strdata->data[range(begin, end)]);
}

sidx_t String::indexOf(const String substr, idx_t start) const
        throw(ArrayException) {
    if (this->length() - start < substr.length()) return -1;
    for (idx_t i = start; i < (this->length() - substr.length()); i++) {
        if(startsWithHelper(i,*this,substr)) {
            return i;
        }
    }
    return -1;
}

sidx_t String::lastIndexOf(const String substr) const {
    return lastIndexOf(substr, length() - 1);
}

sidx_t String::lastIndexOf(const String substr, idx_t start) const
        throw(ArrayException) {
    if (start < substr.length()) { 
        return -1;
    }
    for (sidx_t i = start; i >= sidx_t(substr.length() - 1); i--) {
        if(endsWithHelper(i,*this,substr)) {
            return i-substr.length() + 1;
        }
    }
    return -1;
}

String String::copy() const {
    return strdata->data.copy();
}

bool String::merge(String other) const {
    if (other != *this) return false;
    else {
        this->strdata->refcount += other.strdata->refcount;
        other.strdata->data = this->strdata->data;
        return true;
    }
}

String String::fromHex(int i, bool up) {
    size_t tmplen = sizeof (i) * 5; // long enough, i presume?
    char * buf = new char[tmplen];
    sprintf(buf, up ? "%#X" : "%#x", i);
    String toReturn;
    delete toReturn.strdata;
    toReturn.fromAscii(buf);
    delete[] buf;
    return toReturn;
}

String String::fromOct(int i) {
    size_t tmplen = sizeof (i) * 5; // long enough, i presume?
    char * buf = new char[tmplen];
    sprintf(buf, "%#o", i);
    String toReturn;
    delete toReturn.strdata;
    toReturn.fromAscii(buf);
    delete[] buf;
    return toReturn;
}

String String::fromSci(float f, bool up) {
    char * buf = static_cast<char*>(GC_MALLOC_ATOMIC(20));
    sprintf(buf, up?"%.6E" : "%6e", f);
    String toReturn;
    delete toReturn.strdata;
    toReturn.fromAscii(buf);
    delete[] buf;
    return toReturn;
}

String String::fromSci(double d, bool up) {
    char * buf = static_cast<char*>(GC_MALLOC_ATOMIC(20));
    sprintf(buf, up?"%.15E" : "%15e", d);
    String toReturn;
    delete toReturn.strdata;
    toReturn.fromAscii(buf);
    delete[] buf;
    return toReturn;
}

bool String::boolValue() const {
    String l = (*this & lc);
    return l == "true" || l == "1" || l == "yes" || l == "on";
}

sint String::intValue() const {
    sint i = 0;
    sscanf(this->ascii(), "%"S_FMT_I, &i);
    return i;
}

suint String::uintValue() const {
    suint i = 0;
    sscanf(this->ascii(), "%"S_FMT_UI, &i);
    return i;
}

slong String::longValue() const {
    slong l = 0;
    sscanf(this->ascii(), "%"S_FMT_L, &l);
    return l;
}

sulong String::ulongValue() const {
    sulong l = 0;
    sscanf(this->ascii(), "%"S_FMT_UL, &l);
    return l;
}

float String::floatValue() const {
    if (*this == "NaN") return 0.0f / 0.0f;
    else if (*this == "Infinity") return 1.0f / 0.0f;
    else if (*this == "-Infinity") return -1.0f / 0.0f;
    float f = 0;
    sscanf(this->ascii(), "%f", &f);
    return f;
}

double String::doubleValue() const {
    if (*this == "NaN") return 0.0 / 0.0;
    else if (*this == "Infinity") return 1.0 / 0.0;
    else if (*this == "-Infinity") return -1.0 / 0.0;
    double d = 0;
    sscanf(this->ascii(), "%lf", &d);
    return d;
}

const String& String::operator=(const char * orig) const {
    strdata->refcount--;
    if (strdata->refcount == 0) delete strdata;
    fromUtf8(orig);
    return *this;
}

const String& String::operator=(const std::string & orig) const {
    strdata->refcount--;
    if (strdata->refcount == 0) delete strdata;
    fromAscii(orig.c_str());
    return *this;
}

const String& String::operator=(const String orig) const {
    strdata->refcount--;
    if (strdata->refcount == 0) delete strdata;
    strdata = orig.strdata;
    strdata->refcount++;
    return *this;
}

String::operator const char *() const {
    return utf8();
}

String::operator std::string() const {
    return std::string(ascii());
}

void String::fromAscii(const char* ascii) const {
    // no conversion required. Just plain ol' copy.
    strdata = new Data(std::strlen(ascii));
    for (idx_t i = 0; i < std::strlen(ascii); i++) {
        strdata->data[i] = ascii[i];
    }
}

void String::fromUtf8(const char* unicode) const {
    size_t len = std::strlen(unicode);
    StringBuffer buf;
    uchar current = 0;
    byte bytecount = 0;
    for (idx_t i = 0; i < len; i++) {
        unsigned char univalue = static_cast<unsigned char> (unicode[i]);
        switch (bytecount) {
            case 0:
                if (univalue <= 0x7F) {
                    // ascii
                    buf << (char) univalue;
                } else if ((univalue | 0x1F) == 0xDF) {
                    // start of 2-byte char
                    bytecount = 1;
                    current = (univalue & 0x1F) << 6;
                } else if ((univalue | 0x0F) == 0xEF) {
                    // start of 3-byte char
                    bytecount = 2;
                    current = (univalue & 0x0F) << 12;
                } else if ((univalue | 0x07) == 0xF7) {
                    // start of 4-byte char, unsupported!
                    buf << (uchar)0xFFFD; // That's such a nice ? in a black diamond.
                    i += 3;
                } else {
                    // invalid!
                    buf << (uchar)0xFFFD;
                }
                break;
            case 1:
                if ((univalue | 0x3F) != 0xBF) {
                    // invalid followup
                    bytecount = 0;
                    buf << (uchar)0xFFFD;
                } else {
                    current += (univalue & 0x3F);
                    buf << (uchar)current;
                    bytecount = 0;
                }
                break;
            case 2: case 3:
                if ((univalue | 0x3F) != 0xBF) {
                    // invalid followup
                    i += bytecount - 1;
                    bytecount = 0;
                    buf << (uchar)0xFFFD;
                } else {
                    current += (univalue & 0x3F) << 6;
                    bytecount--;
                }
                break;
            default:
                // okaay... somehow, an error occured.
                // Todo: add a 'this is plainly impossible' statement.
                break;

        }
    }
    String tmp = buf.toString();
    strdata = tmp.strdata;
    strdata->refcount++;
}

bool operator==(const String lhs, const String rhs) {
    if (lhs.length() != rhs.length()) return false;
    for (idx_t i = 0; i < lhs.length(); i++) {
        if (lhs.at(i) != rhs.at(i)) return false;
    }
    return true;
}

bool operator<(const String lhs, const String rhs) {
    String l = lhs.length() < rhs.length() ? lhs : rhs;
    String r = lhs.length() < rhs.length() ? rhs : lhs;
    for (idx_t i = 0; i < l.length(); i++) {
        if (l.at(i) == r.at(i)) continue;
        else if (l.at(i) > l.at(i)) return false;
        else return true;
    }
    return true;
}

const String& String::operator+=(const String rhs) const {
    Data * newdata = new Data(length() + rhs.length());
    arraycopy(strdata->data, 0, newdata->data, 0, length());
    arraycopy(rhs.strdata->data, 0, newdata->data, length(), rhs.length());
    strdata->refcount--;
    if (strdata->refcount == 0) delete strdata;
    strdata = newdata;
    return *this;
}

String operator+(const String lhs, const String rhs) {
    return String(lhs) += rhs;
}

String operator&(const String lhs, String(*rhs)(const String)) {
    return rhs(lhs);
}

String operator&(String(*lhs)(const String), const String rhs) {
    return lhs(rhs);
}

String operator*(const String lhs, const std::size_t len) {
    StringBuffer buf;
    for (idx_t i = 0; i < len; i++) {
        buf << lhs;
    }
    return buf;
}

std::ostream & operator<<(std::ostream& lhs, const String rhs) {
    return lhs << rhs.utf8();
}

String lc(const String rhs) {
    return rhs.toLowerCase();
}

String uc(const String rhs) {
    return rhs.toUpperCase();
}

String t(const String rhs) {
    return rhs.trim();
}

SYLPH_END_NAMESPACE
