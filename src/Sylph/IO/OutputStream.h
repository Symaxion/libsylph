/*
 * LibSylph Class Library
 * Copyright (C) 2012 Frank "SeySayux" Erens <seysayux@gmail.com>
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
 * Created on 27 april 2009, 17:41
 */

#ifndef SYLPH_IO_OUTPUTSTREAM_H_
#define	SYLPH_IO_OUTPUTSTREAM_H_

#include "../Core/Exception.h"
#include "../Core/Array.h"

SYLPH_BEGIN_NAMESPACE

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
    virtual void write(const Array<byte> b, off_t off = 0, size_t len = 0)  {
        if(len == 0) len = b.length;
        if(off+len > b.length) sthrow(IndexException, "Array out of bounds");
        for(idx_t i = off; i < off+len; i++) {
            operator<<(b[i]);
        }
    }

    /** */
    virtual void write(const byte b) {
        operator<<(b);
    }

    /** */
    virtual OutputStream& operator<<(const byte b) = 0;
    OutputStream& operator<<(const Array<byte> b) {
        write(b);
        return *this;
    }

    /** */
    OutputStream & operator<<(OutputStream&(*f)(OutputStream&)) {
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
#endif	/* SYLPH_IO_OUTPUTSTREAM_H_ */


// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
