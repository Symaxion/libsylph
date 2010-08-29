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
 * Created on 30 juni 2009, 12:07
 */

#ifndef BUFFEREDINPUTSTREAM_H_
#define	BUFFEREDINPUTSTREAM_H_

#include "InputStream.h"
#include "../Core/Primitives.h"

SYLPH_BEGIN_NAMESPACE
class BufferedInputStream : public InputStream {
public:
    BufferedInputStream(InputStream& _orig, size_t bufsize = 1024);
    virtual ~BufferedInputStream();

    fsize_t available() const;
    bool eof() const;
    bool markSupported() const { return true; }
    void mark(fsize_t);
    fsize_t skip(fsize_t);
    void reset();

    InputStream& operator>>(byte&);

private:
    void readNext();
    InputStream& orig;
    Array<byte> buffer;
    size_t used;
    idx_t currentIdx;
    idx_t markpos;
    idx_t marklen;
};
SYLPH_END_NAMESPACE

#endif	/* BUFFEREDINPUTSTREAM_H_ */

