/*
 * String.cpp
 *
 *  Created on: 26-nov-2008
 *      Author: SeySayux
 */

#include "String.h"
#include "Array.h"
#include "Hash.h"
#include "StringBuffer.h"

#include <cctype>

#include <unicode/uchar.h>

SYLPH_BEGIN_NAMESPACE
#define ssc SYLPH_STRING_CLASS

ssc::ssc() {
    strdata = new Data(0);
}

ssc::ssc(const char * orig) {
    fromUtf8(Array<char*>::fromPointer(strlen(orig) + 1, orig));
}

ssc::ssc(const Array<char> orig) {
    fromUtf8(orig);
}

ssc::ssc(const Array<uchar> orig) {
    strdata = new Data(0);
    delete strdata->data;
    strdata->data = orig.copy();
}

ssc::ssc(const std::string& orig) {
    // std::string's always ascii...
    fromAscii(orig.c_str());
}

ssc::ssc(const String& orig) {
    // refcounted
    this->strdata = orig.strdata;
    this->strdata->refcount++;
}

ssc::ssc(const char c) {
    fromAscii(c);
}

ssc::ssc(const bool b) {
    fromAscii(b ? "true" : "false");
}

ssc::ssc(const sint i) {
    size_t tmplen = sizeof (i) * 5; // long enough, i presume?
    char * buf = new char[tmplen];
    sprintf(buf, "%"S_FMT_I, i);
    fromAscii(buf);
    delete[] buf;
}

ssc::ssc(const suint i) {
    size_t tmplen = sizeof (i) * 5; // long enough, i presume?
    char * buf = new char[tmplen];
    sprintf(buf, "%"S_FMT_UI, i);
    fromAscii(buf);
    delete[] buf;
}

ssc::ssc(const slong l) {
    size_t tmplen = sizeof (l) * 5; // long enough, i presume?
    char * buf = new char[tmplen];
    sprintf(buf, "%"S_FMT_L, l);
    fromAscii(buf);
    delete[] buf;
}

ssc::ssc(const sulong l) {
    size_t tmplen = sizeof (l) * 5; // long enough, i presume?
    char * buf = new char[tmplen];
    sprintf(buf, "%"S_FMT_UL, l);
    fromAscii(buf);
    delete[] buf;
}

ssc::ssc(const float f) {
    size_t tmplen = sizeof (f) * 10; // long enough, i presume?
    char * buf = new char[tmplen];
    sprintf(buf, "%f", f);
    fromAscii(buf);
    delete[] buf;
}

ssc::ssc(const double d) {
    size_t tmplen = sizeof (d) * 10; // long enough, i presume?
    char * buf = new char[tmplen];
    sprintf(buf, "%f", d);
    fromAscii(buf);
    delete[] buf;
}

ssc::ssc() {
    strdata->refcount--;
    if (strdata->refcount == 0) delete strdata;
}

std::size_t ssc::length() const {
    return strdata->data->length;
}

uchar ssc::at(std::size_t idx) const {
    return strdata->data[idx];
}

const char * ssc::ascii() const {
    // all non-ascii chars will be converted to '?' literals.
    char * buf = new char[length()+1];
    for(idx_t i = 0; i < length(); i++) {
        if(at(i) > 0x7F) buf[i] = '?';
        else buf[i] = at(i);
    }
    return buf;
}

const char * ssc::utf8() const {
    // In the best case, the the buffer need to be length()+1. In the worst
    // case, it's 3 * length() + 1. Always prepare for the worst ;)
    char * buf = new char[3*length()+1];
    size_t buflen = 0;
    for(idx_t i = 0; i < length(); i++) {
        if(at(i) < 0x7F) {
            // ascii
            buf[buflen] = at(i);
            buflen++;
        } else if(at(i) < 0x07FF) {
            // 2-byte
            buf[buflen] = 0xC0 | ((at(i) & 0x07C0) >> 6);
            buf[buflen+1] = 0x80 | (at(i) & 0x3F);
            buflen += 2;
        } else {
            // 3-byte
            buf[buflen] = 0xE0 | ((at(i) & 0xF000) >> 12);
            buf[buflen+1] = 0x80 | ((at(i) & 0x0FC0) >> 6);
            buf[buflen+2] = 0x80 | (at(i) & 0x3F);
            buflen += 3;
        }
    }

    // now copy it to the final buffer...
    char * final = new char[buflen+1];
    carraycopy(buf,0,final,0,buflen);
    return final;
}

const Array<uchar> ssc::utf16() const {
    return strdata->data;
}

String ssc::toLowerCase() const {
    StringBuffer buf;
    for(idx_t i = 0; i < length(); i++) {
        buf << u_tolower(at(i));
    }
    return buf;
}

String ssc::toUpperCase() const {
    StringBuffer buf;
    for(idx_t i = 0; i < length(); i++) {
        buf << u_toupper(at(i));
    }
    return buf;
}

bool ssc::equalsIgnoreCase(const String other) {
    return this->toLowerCase() == other.toLowerCase();
}

bool ssc::endsWith(const String other) const {
    if (this->length() < other.length()) return false;
    suint count = 0;
    for (idx_t i = this->length() - 1; i > this->length() - other.length(); i--) {
        if (this->at(i) == other.at(i)) count++;
        else break;
    }
    return count == other.length();
}

bool ssc::startsWith(const String other) const {
    if (this->length() < other.length()) return false;
    suint count = 0;
    for (idx_t i = 0; i < other.length(); i++) {
        if (this->at(i) == other.at(i)) count++;
        else break;
    }
    return count == other.length();
}

bool ssc::contains(const String other) const {
    return indexOf(other) != -1;
}

String ssc::trim() const {
    size_t beginct = 0;
    size_t endct = length() - 1;
    for (idx_t i = 0; i < this->length(); i++) {
        if (isspace(this->at(i))) beginct++;
    }
    for (idx_t i = length() - 1; i >= 0; i--) {
        if (isspace(this->at(i))) endct--;
    }
    return substring(beginct, endct);
}

String ssc::substring(idx_t begin) const {
    return substring(begin, length());
}

String ssc::substring(idx_t begin, idx_t end) const {
    return String(strdata->data[range(begin, end)]);
}

sidx_t ssc::indexOf(const String substr, idx_t start) const {
    if (this->length() - start < substr.length()) return -1;
    suint currentidx = 0;
    suint idxexport = 0;
    for (idx_t i = start; i < substr.length(); i++) {
        if (this->at(i) == substr.at(currentidx)) {
            currentidx++;
        } else {
            currentidx = 0;
        }
        if (currentidx == substr.length()) {
            idxexport = i;
            break;
        }
    }
    return currentidx == substr.length() ?
            this->length() - idxexport - substr.length() : -1;
}

sidx_t ssc::lastIndexOf(const String substr) {
    return lastIndexOf(substr, length() - 1);
}

sidx_t ssc::lastIndexOf(const String substr, idx_t start) const {
    if (start < substr.length()) return -1;
    suint currentidx = substr.length() - 1;
    suint idxexport = 0;
    for (idx_t i = start; i >= 0; i--) {
        if (this->at(i) == substr.at(currentidx)) {
            currentidx--;
        } else {
            currentidx = substr.length() - 1;
        }
        if (currentidx == 0) {
            idxexport = i;
            break;
        }
    }
    return currentidx == 0 ? idxexport : -1;
}

String ssc::copy() const {
    return strdata->data.copy();
}

bool ssc::merge(String other) const {
    if (other != *this) return false;
    else {
        this->strdata->refcount += other.strdata->refcount;
        delete other.strdata;
        other.strdata = this->strdata;
        return true;
    }
}

sint ssc::hashCode() const {
    sint result = 1;
    for (idx_t i = 0; i < length(); i++) {
        result = 31 * result + Hash(this->at(i));
    }
}

String ssc::fromHex(int i, bool up) {
    size_t tmplen = sizeof (i) * 5; // long enough, i presume?
    char * buf = new char[tmplen];
    sprintf(buf, up ? "%#X" : "%#x", i);
    fromAscii(buf);
    delete[] buf;
}

String ssc::fromOct(int i, bool up) {
    size_t tmplen = sizeof (i) * 5; // long enough, i presume?
    char * buf = new char[tmplen];
    sprintf(buf, up ? "%#O" : "%#o", i);
    fromAscii(buf);
    delete[] buf;
}

String ssc::fromSci(float f, bool up) {
    size_t tmplen = sizeof (f) * 10; // long enough, i presume?
    char * buf = new char[tmplen];
    sprintf(buf, up ? "%#E" : "%#e", f);
    fromAscii(buf);
    delete[] buf;
}

String ssc::fromSci(double d, bool up) {
    size_t tmplen = sizeof (d) * 10; // long enough, i presume?
    char * buf = new char[tmplen];
    sprintf(buf, up ? "%#E" : "%#e", d);
    fromAscii(buf);
    delete[] buf;
}

bool ssc::boolValue() const {
    return *this&lc == "true";
}

sint ssc::intValue() const {
    sint i = 0;
    sscanf(this->ascii(), "%"S_FMT_I, &i);
    return i;
}

suint ssc::uintValue() const {
    suint i = 0;
    sscanf(this->ascii(), "%"S_FMT_UI, &i);
    return i;
}

slong ssc::longValue() const {
    slong l = 0;
    sscanf(this->ascii(), "%"S_FMT_L, &l);
    return l;
}

sulong ssc::ulongValue() const {
    sulong l = 0;
    sscanf(this->ascii(), "%"S_FMT_UL, &l);
    return l;
}

float ssc::floatValue() const {
    float f = 0;
    sscanf(this->ascii(), "%f", &f);
    return f;
}

double ssc::doubleValue() const {
    double d = 0;
    sscanf(this->ascii(), "%lf", &d);
    return d;
}

String ssc::operator=(const char * orig) const {
    strdata->refcount--;
    if (strdata->refcount == 0) delete strdata;
    fromUtf8(orig);
}

String ssc::operator=(const std::string & orig) const {
    strdata->refcount--;
    if (strdata->refcount == 0) delete strdata;
    fromAscii(orig.c_str());
}

String ssc::operator=(const String orig) const {
    strdata->refcount--;
    if (strdata->refcount == 0) delete strdata;
    strdata = orig.strdata;
    strdata->refcount++;
}

ssc::operator const char *() const {
    return utf8();
}

ssc::operator std::string() const {
    return std::string(ascii());
}

void ssc::fromAscii(const char* ascii) const {
    // no conversion required. Just plain ol' copy.
    strdata = new Data(strlen(ascii));
    for (idx_t i = 0; i < strlen(ascii); i++) {
        strdata->data[i] = ascii[i];
    }
}

void ssc::fromUtf8(const char* unicode) const {
    size_t len = strlen(unicode);
    StringBuffer buf;
    uchar current;
    byte bytecount = 0;
    for (idx_t i = 0; i < len; i++) {
        switch (bytecount) {
            case 0:
                if (unicode[i] || 0x7F == 0x7F) {
                    // ascii
                    buf << unicode[i];
                } else if ((unicode[i] | 0x1F) == 0xDF) {
                    // start of 2-byte char
                    bytecount = 1;
                    uchar = (unicode[i] & 0x1F) << 6;
                } else if ((unicode[i] | 0x0F) == 0xEF) {
                    // start of 3-byte char
                    bytecount = 2;
                    uchar = (unicode[i] & 0x0F) << 12;
                } else if ((unicode[i] | 0x07) == 0xF7) {
                    // start of 4-byte char, unsupported!
                    buf << 0xFFFD; // That's such a nice ? in a black diamond.
                    i+=3;
                } else {
                    // invalid!
                    buf << 0xFFFD;
                }
                break;
            case 1:
                if((unicode[i] | 0x3F) != 0xBF) {
                    // invalid followup
                    bytecount = 0;
                    buf << 0xFFFD;
                } else {
                    uchar +=(unicode[i] & 0xBF);
                    buf << uchar;
                    bytecount = 0;
                }
                break;
            case 2: case 3:
                if((unicode[i] | 0x3F) != 0xBF) {
                    // invalid followup
                    i += bytecount -1;
                    bytecount = 0;
                    buf << 0xFFFD;
                } else {
                    uchar +=(unicode[i] & 0xBF) << 6;
                    bytecount--;
                }
                break;
            default:
                // okaay... somehow, an error occured.
                // Todo: add a 'this is plainly impossible' statement.
                break;

        }
    }
    *this = buf.toString();
}

bool operator==(const String lhs, const String rhs) {
    if (lhs.length() != rhs.length()) return false;
    for (idx_t i = 0; i < lhs.length; i++) {
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

String ssc::operator+=(const String rhs) const {
    Data * newdata = new Data(length() + rhs.length());
    arraycopy(strdata, 0, newdata, 0, length());
    arraycopy(rhs.strdata, 0, newdata, length(), rhs.length());
    strdata.refcount--;
    if (strdata.refcount == 0) delete strdata;
    strdata = newdata;
    return *this;
}

String operator+(const String lhs, const String rhs) {
    return String(lhs) += rhs;
}

String operator&(const String lhs, const String(*rhs)(String)) {
    return rhs(lhs);
}

String operator&(const String(*lhs)(String), const String rhs) {
    return lhs(rhs);
}

String operator*(const String lhs, const std::size_t len) {
    StringBuffer buf;
    for (int i = 0; i < len; i++) {
        buf << lhs;
    }
    return buf;
}

std::ostream & operator<<(std::ostream& lhs, const String rhs) {
    return lhs << rhs.utf8();
}

String tr(String rhs) {
    //2do
}

String lc(String rhs) {
    return rhs.toLowerCase();
}

String uc(String rhs) {
    return rhs.toUpperCase();
}

String t(String rhs) {
    return rhs.trim();
}

SYLPH_END_NAMESPACE