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
 * Created on 25 april 2009, 15:59
 */

#ifndef BYTEBUFFER_H_
#define	BYTEBUFFER_H_

#include "Common.h"
#include "../IO/InputStream.h"
#include "../IO/OutputStream.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

/**
 * @todo Write documentation!
 */
class ByteBuffer : public InputStream, public OutputStream {
    friend OutputStream& operator<<(OutputStream&, ByteBuffer&);
    friend InputStream& operator>>(InputStream&, ByteBuffer&);
public:
    enum Traits {
        Closed = 0x00,
        Read = 0x01,
        Write = 0x02,
        ReadWrite = 0x03,
        RW = ReadWrite
    };
    ByteBuffer(Traits traits = RW, size_t bufsize = 16);
    ByteBuffer(const Array<byte> & ar);
    ByteBuffer(const ByteBuffer& orig);
    virtual ~ByteBuffer();

    // common methods
    
    fsize_t available() const;
    void close();
    bool eof() const;
    bool markSupported() const { return true; }
    void mark(fsize_t);
    fsize_t skip(fsize_t);
    void reset();
    size_t size() const;
    void clear();
    
    // traits modifiers
    
    void setTraits(Traits traits);

    // Read methods
    InputStream& operator>>(byte& b);

    // Write methods and operators
    OutputStream& operator<<(const byte b);

    ByteBuffer& fromString(const String s);

    // Operators:
    ByteBuffer& operator=(const ByteBuffer & rhs);

    // Convertors:
    
    Array<byte> toArray();
    const Array<byte> toArray() const;

    operator Array<byte>();
    operator const Array<byte>() const;
private:
    void ensureCapacity(size_t capacity);
    Array<byte> _array;
    idx_t _pos;
    size_t _size;
    Traits _traits;
    idx_t _mark;
    size_t _markExpires;
};

OutputStream& operator<<(OutputStream&, ByteBuffer&);
InputStream& operator>>(InputStream&, ByteBuffer&);

SYLPH_END_NAMESPACE

#endif	/* BYTEBUFFER_H_ */