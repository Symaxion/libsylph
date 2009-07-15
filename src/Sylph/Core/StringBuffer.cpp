#include "StringBuffer.h"
#include "String.h"
#include "Util.h"

SYLPH_BEGIN_NAMESPACE
StringBuffer::StringBuffer(const String s) : _length(s.length()),
        buf(s.length()+16) {
}

StringBuffer::~StringBuffer() {

}

size_t StringBuffer::length() const {
    return length;
}

void StringBuffer::deleteSubstring(idx_t start, idx_t end) {
    if(start > _length || end > _length || start > end)
        sthrow(ArrayException, "StringBuffer out of bounds!");
    if(start == end) return;

    arraycopy(buf,end,buf,start,end-start);
    _length -= (end-start);
}

void StringBuffer::clear() {
    buf = Array<uchar>(16);
    _length(0);
}

const uchar& StringBuffer::at(idx_t idx) const {
    return buf[idx];
}

uchar& StringBuffer::at(idx_t idx) {
    return buf[idx];
}

StringBuffer& StringBuffer::operator<<(bool b) {
    return *this<<(String(b));
}

StringBuffer& StringBuffer::operator<<(char c) {
    ensureCapacity(_length+1);
    buf[_length] = c;
    _length++;
    return *this;
}

StringBuffer& StringBuffer::operator<<(Array<char> c) {
    ensureCapacity(_length+c.length);
    for(idx_t i = 0; i < c.length; i++) {
        operator<<(c[i]);
    }
    return *this;
}

StringBuffer& StringBuffer::operator<<(uchar c) {
    ensureCapacity(_length+1);
    buf[_length] = c;
    _length++;
    return *this;
}

StringBuffer& StringBuffer::operator<<(Array<uchar> c) {
    ensureCapacity(_length+c.length);
    for(idx_t i = 0; i < c.length; i++) {
        operator<<(c[i]);
    }
    return *this;
}

StringBuffer& StringBuffer::operator<<(sint i) {
    return *this<<(String(i));
}

StringBuffer& StringBuffer::operator<<(suint i) {
    return *this<<(String(i));
}

StringBuffer& StringBuffer::operator<<(slong l) {
    return *this<<(String(l));
}

StringBuffer& StringBuffer::operator<<(sulong l) {
    return *this<<(String(l));
}

StringBuffer& StringBuffer::operator<<(float f) {
    return *this<<(String(f));
}

StringBuffer& StringBuffer::operator<<(double d) {
    return *this<<(String(d));
}

StringBuffer& StringBuffer::operator<<(String s) {
    ensureCapacity(_length + s.length());
    for(idx_t i = 0; i < s.length(); i++) {
        operator<<(s.at(i));
    }
    return *this;
}

String StringBuffer::toString() const {
    Array<uchar> toReturn(_length);
    arraycopy(buf,0,toReturn,0,_length);
    return String(toReturn);
}

StringBuffer::operator String() const {
    return toString();
}

void StringBuffer::ensureCapacity(std::size_t capacity) {
    if(buf.length > capacity) return;

    size_t newsize = buf.length;
    while(newsize < capacity) newsize << 1;
    Array<uchar> newbuf(newsize);
    arraycopy(buf,0,newbuf,0,buf.length);
    buf = newbuf;
}
SYLPH_END_NAMESPACE
