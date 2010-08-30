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

