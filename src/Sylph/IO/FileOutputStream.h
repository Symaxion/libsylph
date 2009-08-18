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
 * Created on 6 augustus 2009, 17:26
 */

#ifndef FILEOUTPUTSTREAM_H_
#define	FILEOUTPUTSTREAM_H_

#include "OutputStream.h"
#include "../Core/File.h"
#include "FileIO.h"
#include <cstdio>

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

class FileOutputStream : public OutputStream {
public:

    FileOutputStream(File& f, IO::IOType t = IO::Normal);
    virtual ~FileOutputStream();

    void write(const Array<byte> b, off_t off = 0, size_t len = 0);
    void close();

    void flush();

    OutputStream & operator<<(const byte b);

private:
    FILE* fptr;
};
SYLPH_END_NAMESPACE

#endif	/* FILEOUTPUTSTREAM_H_ */

