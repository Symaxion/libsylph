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
 * Created on 22 juli 2009, 17:01
 */

#ifndef FILEINPUTSTREAM_H_
#define	FILEINPUTSTREAM_H_

#include "InputStream.h"
#include "FileIO.h"
#include "../Core/File.h"

#include <cstdio>

SYLPH_BEGIN_NAMESPACE
class FileInputStream : public InputStream {
public:
    FileInputStream(File& f, IO::IOType t = IO::Normal) throw(IOException);
    virtual ~FileInputStream();

    fsize_t available() const;
    fssize_t read(Array<byte>& b, off_t offset = 0, size_t len = 0)
            throw(ArrayException, IOException);
    bool eof() const;
    bool markSupported() const { return true; }
    void mark(fsize_t);
    fsize_t skip(fsize_t);
    void reset();

    InputStream& operator>>(byte&);
private:
    FILE * fptr;
    fsize_t _mark;
    fsize_t _markExpires;
};
SYLPH_END_NAMESPACE

#endif	/* FILEINPUTSTREAM_H_ */

