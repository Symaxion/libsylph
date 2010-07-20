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
 * Created on 27 april 2009, 17:41
 */

#ifndef OUTPUTSTREAM_H_
#define	OUTPUTSTREAM_H_

#include "../Core/Exception.h"
#include "../Core/Array.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

/** */
class OutputStream : public virtual Object {
public:

    /** */
    OutputStream() : closed(false) {
    }
    /** */
    virtual ~OutputStream() {

    }

    /** */
    virtual void close() {
        closed = true;
    }

    /** */
    virtual void flush() {}
    /** */
    virtual void write(const Array<byte> b, off_t off = 0, size_t len = 0)
            throw(ArrayException, IOException) {
        if(len == 0) len = b.length;
        if(off+len > b.length) sthrow(ArrayException, "Array out of bounds");
        for(idx_t i = off; i < off+len; i++) {
            operator<<(b[i]);
        }
    }

    /** */
    virtual void write(const byte b) throw(IOException) {
        operator<<(b);
    }

    /** */
    virtual OutputStream& operator<<(const byte b) = 0;
    OutputStream& operator<<(const Array<byte> b) throw(IOException) {
        write(b);
        return *this;
    }

    /** */
    OutputStream & operator<<(OutputStream&(*f)(OutputStream&)){
        return f(*this);
    }

    /** */
    bool toBool() const {
        return !closed;
    }
protected:
    bool closed;
};

inline OutputStream& flush(OutputStream& s) {
    s.flush();
    return s;
}


SYLPH_END_NAMESPACE
#endif	/* OUTPUTSTREAM_H_ */

