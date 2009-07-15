/* 
 * File:   OutputStream.h
 * Author: frank
 *
 * Created on 27 april 2009, 17:41
 */

#ifndef OUTPUTSTREAM_H_
#define	OUTPUTSTREAM_H_


#include "../Core/BoolConvertible.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

class OutputStream : public virtual BoolConvertible<OutputStream> {
public:

    OutputStream() : closed(false) {
    }
    virtual ~OutputStream() {

    }
    virtual void close() {
        closed = true;
    }

    virtual void flush() {}
    virtual void write(const Array<byte> b, off_t off = 0, size_t len = 0) {
        if(len = 0) len = b.length;
        if(off+len > b.length) sthrow(ArrayException, "Array out of bounds");
        for(idx_t i = off; i < off+len; i++) {
            operator<<(b[i]);
        }
    }
    virtual void write(const byte b) {
        operator<<(b);
    }

    virtual OutputStream& operator<<(const byte b) = 0;
    OutputStream& operator<<(const Array<byte> b);

    OutputStream & operator<<(OutputStream&(*f)(OutputStream&)) {
        return f(*this);
    }

    bool toBool() const {
        return !closed;
    }
protected:
    bool closed;
};

OutputStream& flush(OutputStream& s);


SYLPH_END_NAMESPACE
#endif	/* OUTPUTSTREAM_H_ */

