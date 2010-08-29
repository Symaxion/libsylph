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

#ifndef BUFFEREDOUTPUTSTREAM_H_
#define	BUFFEREDOUTPUTSTREAM_H_

#include "OutputStream.h"

SYLPH_BEGIN_NAMESPACE
class BufferedOutputStream : public OutputStream {
public:
    BufferedOutputStream(OutputStream& _orig, size_t bufsize = 1024) :
        orig(_orig), buffer(bufsize), used(0) {}
    virtual ~BufferedOutputStream();
    void close();

    void flush();
    BufferedOutputStream& operator<<(const byte b);
private:
    OutputStream& orig;
    Array<byte> buffer;
    size_t used;
};

SYLPH_END_NAMESPACE

#endif	/* BUFFEREDOUTPUTSTREAM_H_ */

