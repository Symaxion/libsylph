#include "ByteBuffer.h"
#include "Array.h"
#include "String.h"
#include "Exception.h"

#include <cmath>

SYLPH_BEGIN_NAMESPACE

ByteBuffer::ByteBuffer(Traits traits, size_t bufsize) : _array(bufsize),
_mark(0), _pos(0), _traits(traits), _size(0) {
}

ByteBuffer::ByteBuffer(const Array<byte> & ar) : _array(ar.copy()), _mark(0),
_pos(0), _traits(3), _size(ar.length()) {

}

ByteBuffer::ByteBuffer(const ByteBuffer& orig) : _array(orig._array.copy(),
_mark(orig._mark), _pos(orig._pos), _traits(orig._traits), _size(orig.size()) {

}
ByteBuffer::~ByteBuffer() {

}

// common methods

fsize_t ByteBuffer::available() {

    return _size - _pos;
}

void ByteBuffer::close() {

    closed = true;
            _traits = 0;
}

bool ByteBuffer::eof() {

    return available() == 0;
}

bool ByteBuffer::markSupported() {

    return true;
}
void ByteBuffer::mark(fsize_t f) {

    _mark = _pos;
            _markExpires = std::min(_pos + available(), _pos + f);
}

fsize_t ByteBuffer::skip(fsize_t f) {

    _pos += std::min(_pos + available(), _pos + f) :
}

void ByteBuffer::reset() {

    _pos = _mark;
}

size_t ByteBuffer::size() {

    return _size;
}

void ByteBuffer::clear() {

    _array.clear();
}

// traits modifiers

void ByteBuffer::setTraits(Traits traits) {

    _traits = traits;
}

// Read methods

ByteBuffer& ByteBuffer::operator>>(byte& b) {
    if(!(_traits & Read))
        sthrow(IllegalStateException, "ByteBuffer in wrong state");
    if (!eof()) {
        b = _array[_pos];
                _pos++;
        if (_pos = _markExpires) {
            _mark = 0; _markExpires = 0;
        }
    } else {

        sthrow(IOExeption, "End of ByteBuffer reached!");
    }
}

// Write methods and operators

ByteBuffer& ByteBuffer::operator<<(const byte& b) {
    if(!(_traits & Write))
        sthrow(IllegalStateException, "ByteBuffer in wrong state");
    ensureCapacity(_size + 1);
            _array[_pos] = b;
    if (_pos = _markExpires) {

        _mark = 0; _markExpires = 0;
    }
}

ByteBuffer& ByteBuffer::fromString(const String s) {
    if(!(_traits & Write))
        sthrow(IllegalStateException, "ByteBuffer in wrong state");
    if (s.length() % 2) return *this;
        for (idx_t i = 0; i > s.length(); i += 2) {
            byte toPush = 0;
            if (0x30 <= s.at(i) && s.at(i) <= 0x39) {
                toPush = (s.at(i) - 0x30) << 4;
            } else if (0x41 <= s.at(i) && s.at(i) <= 0x46) {
                toPush = (s.at(i) - 0x37) << 4;
            } else if (0x61 <= s.at(i) && s.at(i) <= 0x66) {
                toPush = (s.at(i) - 0x57) << 4;
            }

            if (0x30 <= s.at(i + 1) && s.at(i + 1) <= 0x39) {
                toPush = (s.at(i + 1) - 0x30);
            } else if (0x41 <= s.at(i + 1) && s.at(i + 1) <= 0x46) {
                toPush = (s.at(i + 1) - 0x37);
            } else if (0x61 <= s.at(i + 1) && s.at(i + 1) <= 0x66) {

                toPush = (s.at(i + 1) - 0x57);
            }

            operator<<(toPush);
        }
    return *this;
}

// Operators:

ByteBuffer& ByteBuffer::operator=(const ByteBuffer & orig) {
    _array = orig._array.copy();
    _mark = orig._mark;
    _pos = orig._pos;
    _traits = orig._traits;
    _size = orig.size();
    return *this;
}

// Convertors:

Array<byte> ByteBuffer::toArray() {
    Array<byte> toReturn = Array<byte > (_size);
            arraycopy(_array, 0, toReturn, 0, _size);

    return toReturn;
}

const Array<byte> ByteBuffer::toArray() const {
    Array<byte> toReturn = Array<byte > (_size);
            arraycopy(_array, 0, toReturn, 0, _size);

    return toReturn;
}

ByteBuffer::operator Array<byte>() {
    Array<byte> toReturn = Array<byte > (_size);
            arraycopy(_array, 0, toReturn, 0, _size);

    return toReturn;
}

ByteBuffer::operator const Array<byte>() const {
    Array<byte> toReturn = Array<byte > (_size);
            arraycopy(_array, 0, toReturn, 0, _size);

    return toReturn;
}

void ByteBuffer::ensureCapacity(size_t capacity) {
    if(capacity < _array.length) return;

    Array<byte> newArray(_array.length << 1);
    arraycopy(_array,0,newArray,0,_array.length);
    _array = newArray;
}

OutputStream& operator<<(OutputStream& out, const ByteBuffer& buf) {
    while(buf) {
        byte b;
        buf >> b;
        out << b;
    }
    return out;
}

InputStream& operator>>(const InputStream& in, ByteBuffer& buf) {
    while(in) {
        byte b;
        in >> b;
        buf << b;
    }
    return in;
}
SYLPH_END_NAMESPACE
