/*
 * LibSylph Class Library
 * Copyright (C) 2013 Frank "SeySayux" Erens <seysayux@gmail.com>
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
 * Created on 27 april 2009, 17:39
 */

#ifndef SYLPH_IO_INPUTSTREAM_H_
#define	SYLPH_IO_INPUTSTREAM_H_


#include "../Core/Object.h"
#include "../Core/Primitives.h"
#include "../Core/Array.h"
#include "../Core/String.h"

SYLPH_BEGIN_NAMESPACE

/** */
class InputStream : public virtual Object {
public:
    /** */
    InputStream() : closed(false) {}
    /** */
    virtual ~InputStream() {}

    /** */
    virtual fsize_t available() const = 0;
    /** */
    virtual void close() { closed = true; }
    /** */
    virtual void read(byte& b) {
        operator>>(b);
    }

    /** */
    virtual fssize_t read(Array<byte>& b, off_t offset = 0, size_t len = 0) {
        if(!len) len = b.length;
        if(offset + len > b.length)
            sthrow(ArrayException, "Index out of bounds");
        if(eof()) return -1;
        fssize_t actuallyRead = 0;
        for(idx_t i = offset; i < len; i++) {
            if(eof()) break;
            operator>>(b[i]);
            actuallyRead++;
        }
        return actuallyRead;
    }

    /** */
    virtual bool eof() const = 0;

    /** */
    virtual bool markSupported() const { return false; }

    /** */
    virtual void mark(fsize_t) = 0;

    /** */
    virtual fsize_t skip(fsize_t) = 0;

    /** */
    virtual void reset() = 0;

    /** */
    virtual InputStream& operator>>(byte&) = 0;

    /** */
    virtual InputStream& operator>>(Array<byte>& b) {
        read(b);
        return *this;
    }

    /** */
    bool toBool() const { return eof() && !closed; }
protected:
    bool closed;
};
SYLPH_END_NAMESPACE

#endif	/* SYLPH_IO_INPUTSTREAM_H_ */

// vim: ts=4:sts=4:sw=4:sta:et:tw=80:nobk
