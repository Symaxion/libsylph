/* 
 * File:   InputStream.h
 * Author: frank
 *
 * Created on 27 april 2009, 17:39
 */

#ifndef INPUTSTREAM_H_
#define	INPUTSTREAM_H_


#include "../Core/Object.h"
#include "../Core/Primitives.h"
#include "../Core/Array.h"

SYLPH_BEGIN_NAMESPACE
class ByteBuffer;
class String;
SYLPH_PUBLIC

class InputStream : public virtual Object {
public:
    InputStream() : closed(false) {}

    virtual fsize_t available() = 0;
    virtual void close() { closed = false }
    virtual bool eof() = 0;
    virtual void flush() = 0;
    virtual bool markSupported() { return false; }
    virtual void mark(sidx_t) = 0;
    virtual sidx_t skip(sidx_t) = 0;
    virtual void reset() = 0;

    virtual InputStream& operator>>(byte&) = 0;
    virtual InputStream& operator>>(Array<byte>& b) {
        for(idx_t i = 0; i < b.length; i++) {
            *this >> b[i];
        }
    }
    virtual InputStream& operator>>(ByteBuffer& buf);
    virtual InputStream& operator>>(String&) = 0;
    operator bool() { return eof() && !closed; }
protected:
    bool closed;
};
SYLPH_END_NAMESPACE

#endif	/* INPUTSTREAM_H_ */
