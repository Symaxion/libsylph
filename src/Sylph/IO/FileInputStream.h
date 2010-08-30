/*
 * LibSylph Class Library
 * Copyright (C) 2010 Frank "SeySayux" Erens <seysayux@gmail.com>
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

