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
 */

#include "BufferedInputStream.h"
#include <algorithm>

SYLPH_BEGIN_NAMESPACE

BufferedInputStream::BufferedInputStream(InputStream& _orig, size_t
        bufsize) : orig(_orig), buffer(bufsize), used(0), currentIdx(0) {
    readNext();
}
BufferedInputStream::~BufferedInputStream() {

}

fsize_t BufferedInputStream::available() const {
    return orig.available() + used;
}
bool BufferedInputStream::eof() const {
    return used == 0;
}

void BufferedInputStream::mark(fsize_t f) {
    markpos = currentIdx;
    marklen = std::min(int(f), int(buffer.length - currentIdx));
}
fsize_t BufferedInputStream::skip(fsize_t f) {
    byte b;
    fsize_t toReturn = 0;
    for(fsize_t i = 0; i < f; i++) {
        try {
            orig >> b;
            toReturn++;
        } catch(Exception& ex) {
            break;
        }
    }
    return toReturn;
}
void BufferedInputStream::reset()  {
    currentIdx = markpos;
    marklen = buffer.length - currentIdx;
}

InputStream & BufferedInputStream::operator>>(byte& b) {
    if(currentIdx == buffer.length) readNext();
    b = buffer[currentIdx];
    if(marklen > 0) marklen--;
    else if(marklen == 0) markpos = 0;
    return *this;
}

void BufferedInputStream::readNext() {
    used = orig.read(buffer);
    currentIdx = 0;
}
SYLPH_END_NAMESPACE

// vim: ts=4:sts=4:sw=4:sta:et:tw=80:nobk
