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

#include "ByteBuffer.h"
#include "Array.h"
#include "String.h"
#include "Exception.h"
#include "Util.h"

#include <cmath>

SYLPH_BEGIN_NAMESPACE

ByteBuffer::ByteBuffer(Traits traits, size_t bufsize) : _traits(traits), 
        _array(bufsize), _mark(0), _pos(0),  _size(0) { }

ByteBuffer::ByteBuffer(const Array<byte> & ar) : _traits(RW), _array(ar.copy()),
        _mark(0), _pos(0), _size(ar.length) { }

ByteBuffer::ByteBuffer(const ByteBuffer& orig) : _traits(orig._traits), 
        _array(orig._array.copy()), _mark(orig._mark), _pos(orig._pos),
        _size(orig.size()) { }

ByteBuffer::~ByteBuffer() { }

// common methods

fsize_t ByteBuffer::available() const {

    return _size - _pos;
}

void ByteBuffer::close() {
    InputStream::closed = true;
    OutputStream::closed = true;
    _traits = Closed;
}

bool ByteBuffer::eof() const {
    return available() == 0;
}

void ByteBuffer::mark(fsize_t f) {

    _mark = _pos;
    _markExpires = std::min(_pos + available(), _pos + f);
}

fsize_t ByteBuffer::skip(fsize_t f) {
    fsize_t add = std::min(_pos + available(), _pos + f);
    _pos += add;
    return add;
}

void ByteBuffer::reset() {
    _pos = _mark;
}

size_t ByteBuffer::size() const {

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

InputStream& ByteBuffer::operator>>(byte& b) 
        throw(IllegalStateException, IOException) {
    if (!(_traits & Read))
        sthrow(IllegalStateException, "ByteBuffer in wrong state");
    if (!eof()) {
        b = _array[_pos];
        _pos++;
        if (_pos == _markExpires) {
            _mark = 0;
            _markExpires = 0;
        }
    } else {

        sthrow(IOException, "End of ByteBuffer reached!");
    }
    return *this;
}

// Write methods and operators

OutputStream& ByteBuffer::operator<<(const byte b)
        throw(IllegalStateException) {
    if (!(_traits & Write))
        sthrow(IllegalStateException, "ByteBuffer in wrong state");
    ensureCapacity(_size + 1);
    _array[_pos] = b;
    if (_pos == _markExpires) {
        _mark = 0;
        _markExpires = 0;
    }
    if(_pos == _size) ++_size;
    ++_pos;
    return *this;
}

ByteBuffer& ByteBuffer::fromString(const String s) 
          throw(IllegalStateException) {
    if (!(_traits & Write))
        sthrow(IllegalStateException, "ByteBuffer in wrong state");
    if (s.length() % 2) return *this;
    for (idx_t i = 0; i < s.length(); i += 2) {
        byte toPush = 0;
        if (0x30 <= s.at(i) && s.at(i) <= 0x39) {
            toPush = (s.at(i) - 0x30) << 4;
        } else if (0x41 <= s.at(i) && s.at(i) <= 0x46) {
            toPush = (s.at(i) - 0x37) << 4;
        } else if (0x61 <= s.at(i) && s.at(i) <= 0x66) {
            toPush = (s.at(i) - 0x57) << 4;
        }

        if (0x30 <= s.at(i + 1) && s.at(i + 1) <= 0x39) {
            toPush += (s.at(i + 1) - 0x30);
        } else if (0x41 <= s.at(i + 1) && s.at(i + 1) <= 0x46) {
            toPush += (s.at(i + 1) - 0x37);
        } else if (0x61 <= s.at(i + 1) && s.at(i + 1) <= 0x66) {
            toPush += (s.at(i + 1) - 0x57);
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
    Array<byte> toReturn = Array<byte>(_size);
    arraycopy(_array, 0, toReturn, 0, std::size_t(_size));

    return toReturn;
}

const Array<byte> ByteBuffer::toArray() const {
    Array<byte> toReturn = Array<byte> (_size);
    arraycopy(_array, 0, toReturn, 0, _size);

    return toReturn;
}

ByteBuffer::operator Array<byte>() {
    Array<byte> toReturn = Array<byte> (_size);
    arraycopy(_array, 0, toReturn, 0, _size);

    return toReturn;
}

ByteBuffer::operator const Array<byte>() const {
    Array<byte> toReturn = Array<byte> (_size);
    arraycopy(_array, 0, toReturn, 0, _size);

    return toReturn;
}

void ByteBuffer::ensureCapacity(size_t capacity) {

    if (capacity < _array.length) return;

    Array<byte> newArray(size_t(_array.length << 1));
    arraycopy(_array, 0, newArray, 0, _array.length);
    _array = newArray;
}

OutputStream & operator<<(OutputStream& out, ByteBuffer& buf) {
    while (buf.OutputStream::toBool()) {

        byte b;
        buf >> b;
        out << b;
    }
    return out;
}

InputStream & operator>>(InputStream& in, ByteBuffer& buf) {
    while (in.toBool()) {
        byte b;
        in >> b;
        buf << b;
    }
    return in;
}
SYLPH_END_NAMESPACE
