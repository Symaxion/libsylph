/*
 * String.cpp
 *
 *  Created on: 26-nov-2008
 *      Author: SeySayux
 */

#include "String.h"
#include "Array.h"
#include "Hash.h"

#include <cctype>

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
    //2do
}

const char * ssc::utf8() const {
    //2do
}

const Array<uchar> ssc::utf16() const {
    return strdata->data;
}

String ssc::toLowerCase() const {
    //2do
}

String ssc::toUpperCase() const {
    //2do
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
    // 2do
}

SYLPH_END_NAMESPACE