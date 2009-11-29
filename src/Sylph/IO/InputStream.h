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
 * Created on 27 april 2009, 17:39
 */

#ifndef INPUTSTREAM_H_
#define	INPUTSTREAM_H_


#include "../Core/Object.h"
#include "../Core/Primitives.h"
#include "../Core/Array.h"
#include "../Core/String.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

class InputStream : public virtual Object {
public:
    InputStream() : closed(false) {}
    virtual ~InputStream() {}

    virtual fsize_t available() const = 0;
    virtual void close() { closed = true; }
    virtual void read(byte& b) {
        operator>>(b);
    }
    virtual fssize_t read(Array<byte>& b, off_t offset = 0, size_t len = 0) {
        if(!len) len = b.length;
        if(offset + len > b.length) sthrow(ArrayException, "Index out of bounds");
        if(eof()) return -1;
        fssize_t actuallyRead = 0;
        for(idx_t i = offset; i < len; i++) {
            if(eof()) break;
            operator>>(b[i]);
            actuallyRead++;
        }
        return actuallyRead;
    }
    virtual bool eof() const = 0;
    virtual bool markSupported() const { return false; }
    virtual void mark(fsize_t) = 0;
    virtual fsize_t skip(fsize_t) = 0;
    virtual void reset() = 0;

    virtual InputStream& operator>>(byte&) = 0;
    virtual InputStream& operator>>(Array<byte>& b) {
        read(b);
        return *this;
    }
    bool toBool() const { return eof() && !closed; }
protected:
    bool closed;
};
SYLPH_END_NAMESPACE

#endif	/* INPUTSTREAM_H_ */
