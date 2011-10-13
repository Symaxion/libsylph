/*
 * LibSylph Class Library
 * Copyright (C) 2011 Frank "SeySayux" Erens <seysayux@gmail.com>
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
 * Created on 6 augustus 2009, 17:26
 */

#ifndef SYLPH_IO_FILEOUTPUTSTREAM_H_
#define	SYLPH_IO_FILEOUTPUTSTREAM_H_

#include "OutputStream.h"
#include "../Core/File.h"
#include "FileIO.h"
#include <cstdio>

SYLPH_BEGIN_NAMESPACE

class FileOutputStream : public OutputStream {
public:

    FileOutputStream(File& f, IO::IOType t = IO::Normal) throw(IOException);
    virtual ~FileOutputStream();

    void write(const Array<byte> b, off_t off = 0, size_t len = 0)
        throw(IOException,IndexException);
    void close();

    void flush();

    OutputStream & operator<<(const byte b) throw(IOException);

private:
    FILE* fptr;
};
SYLPH_END_NAMESPACE

#endif	/* SYLPH_IO_FILEOUTPUTSTREAM_H_ */

