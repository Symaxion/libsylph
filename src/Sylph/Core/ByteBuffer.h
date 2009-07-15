/* 
 * File:   ByteBuffer.h
 * Author: frank
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

class ByteBuffer : public InputStream, public OutputStream {
    friend OutputStream& operator<<(const ByteBuffer&);
    friend InputStream& operator>>(const ByteBuffer&);
public:
    enum Traits {
        Closed = 0x00,
        Read = 0x01,
        Write = 0x02,
        ReadWrite = 0x03,
        RW = ReadWrite
    };
    ByteBuffer(Traits traits = 0x03, size_t bufsize = 16);
    ByteBuffer(const Array<byte> & ar);
    ByteBuffer(const ByteBuffer& orig);
    virtual ~ByteBuffer();

    // common methods
    
    fsize_t available();
    void close();
    bool eof();
    bool markSupported() { return true; }
    void mark(fsize_t);
    fsize_t skip(fsize_t);
    void reset();
    size_t size();
    void clear();
    
    // traits modifiers
    
    void setTraits(Traits traits);

    // Read methods
    ByteBuffer& operator>>(byte& b);

    // Write methods and operators
    ByteBuffer& operator<<(const byte& b);

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
    Array<byte> * _array;
    idx_t _pos;
    size_t _size;
    Traits _traits;
    idx_t _mark;
    size_t _markExpires;
};

OutputStream& operator<<(OutputStream&, const ByteBuffer&);
InputStream& operator>>(const InputStream&, ByteBuffer&);

SYLPH_END_NAMESPACE

#endif	/* BYTEBUFFER_H_ */