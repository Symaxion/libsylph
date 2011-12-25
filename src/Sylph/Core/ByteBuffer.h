/*
 * LibSylph Class Library
 * Copyright (C) 2011 Frank "SeySayux" Erens <seysayux@gmail.com>
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
 * Created on 25 april 2009, 15:59
 */

#ifndef SYLPH_CORE_BYTEBUFFER_H_
#define	SYLPH_CORE_BYTEBUFFER_H_

#include "Array.h"
#include "../IO/InputStream.h"
#include "../IO/OutputStream.h"

SYLPH_BEGIN_NAMESPACE

/**
 * @todo Write documentation!
 */
class ByteBuffer : public InputStream, public OutputStream {
    friend OutputStream& operator<<(OutputStream&, ByteBuffer&);
    friend InputStream& operator>>(InputStream&, ByteBuffer&);
public:
    /**
     * Describes the I/O capabilities of the ByteBuffer. Attempting to use
     * a restricted capability will cause an IllegalStateException to be
     * thrown.
     */
    enum Traits {
        Closed = 0x00, /**< ByteBuffer is closed. No input or output is
                        * possible.  */
        Read = 0x01, /**< ByteBuffer is read-only. Only input from the
                      * %ByteBuffer is possible. */
        Write = 0x02, /**< ByteBuffer is write-only. Only output to the
                       %ByteBuffer is possible. */
        ReadWrite = 0x03, /**< ByteBuffer is read-write. This is the default.
                           The %ByteBuffer acts both as an InputStream and an
                           OutputStream. */
        RW = ReadWrite /**< Aiias for ReadWrite. */
    };

    /**
     * Creates a new, empty ByteBuffer.
     * @param traits The access traits this ByteBuffer is created with. By
     * default all ByteBuffers have full access, that is to say, read-write
     * access.
     * @param bufsize The initial capacity of the buffer. By default, this
     * is equal to 16. An internal array of this length has to be allocated.
     */
    ByteBuffer(Traits traits = RW, size_t bufsize = 16);

    /**
     * Creates a new ByteBuffer and fills it with the contents of a
     * pre-existing array. The traits will be set to RW, and the capacity of
     * the buffer will be double the length of the original array. The size
     * of the new ByteBuffer will be equal to the length of the array.
     * @param ar An array to copy the intial dat a from.
     */
    ByteBuffer(const Array<byte> & ar);
    ByteBuffer(const ByteBuffer& orig);
    /**
     * Default destructor.
     */
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
    InputStream& operator>>(byte& b) throw(IOException, IllegalStateException);

    // Write methods and operators
    OutputStream& operator<<(const byte b) throw(IllegalStateException);

    ByteBuffer& fromString(const String s) throw(IllegalStateException);

    // Operators:
    ByteBuffer& operator=(const ByteBuffer& rhs);

    // Convertors:
    
    Array<byte> toArray();
    const Array<byte> toArray() const;

    operator Array<byte>();
    operator const Array<byte>() const;
private:
    void ensureCapacity(size_t capacity);
    Traits _traits;
    Array<byte> _array;    
    idx_t _mark;
    idx_t _pos;
    size_t _size;
    size_t _markExpires;
};

OutputStream& operator<<(OutputStream&, ByteBuffer&);
InputStream& operator>>(InputStream&, ByteBuffer&);

SYLPH_END_NAMESPACE

#endif	/* SYLPH_CORE_BYTEBUFFER_H_ */
