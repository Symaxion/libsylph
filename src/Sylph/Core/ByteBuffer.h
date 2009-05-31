/* 
 * File:   ByteBuffer.h
 * Author: frank
 *
 * Created on 25 april 2009, 15:59
 */

#ifndef BYTEBUFFER_H_
#define	BYTEBUFFER_H_

#include "Common.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

class ByteBuffer : public virtual Object {
public:
    enum ByteBufferTraits {
        BB_CLOSED = 0x00,
        BB_READ = 0x01,
        BB_WRITE = 0x02
    };
    ByteBuffer(ByteBufferTraits traits);
    ByteBuffer(const Array<byte> & ar);
    ByteBuffer(const byte ar[]);
    ByteBuffer(const ByteBuffer& orig);
    virtual ~ByteBuffer();

    // common methods
    
    void reset();
    void clear();
    void skip(tidx_t i);
    void mark(idx_t i);
    size_t size();
    idx_t position();
    idx_t available();
    
    // traits modifiers
    
    void setTraits(ByteBufferTraits traits);
    
    ByteBuffer& operator>>(byte b);
    ByteBuffer& operator>>(sint i);
    ByteBuffer& operator>>(slong l);
    
    ByteBuffer& operator>>(Array<byte> & b);
    ByteBuffer& operator>>(Array<sint> & i);
    ByteBuffer& operator>>(Array<slong> & l);
    
    // write methods and operators

    ByteBuffer& fromString(const String s);

    ByteBuffer& operator<<(const byte b);
    ByteBuffer& operator<<(const sint i);
    ByteBuffer& operator<<(const slong l);

    ByteBuffer& operator<<(const byte b[]);
    ByteBuffer& operator<<(const sint i[]);
    ByteBuffer& operator<<(const slong l[]);

    ByteBuffer& operator<<(const Array<byte> & b);
    ByteBuffer& operator<<(const Array<sint> & i);
    ByteBuffer& operator<<(const Array<slong> & l);

    ByteBuffer& operator<<(const String s);
    ByteBuffer& operator<<(const ByteBuffer& buf);

    // Operators:
    ByteBuffer& operator=(const ByteBuffer & rhs);

    // 'friendly' operators:


    // Convertors:

    operator Array<byte>();
    operator const Array<byte>() const;
private:
    Array<byte> * _array;
    idx_t _pos;
    ByteBufferTraits _traits;
};

SYLPH_END_NAMESPACE

#endif	/* BYTEBUFFER_H_ */