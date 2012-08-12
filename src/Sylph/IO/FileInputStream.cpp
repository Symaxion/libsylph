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

#include "FileInputStream.h"
#include "../Core/File.h"

SYLPH_BEGIN_NAMESPACE
FileInputStream::FileInputStream(File& f, IO::IOType t) throw(IOException) {
    fptr = fopen(f.toCanonicalName(), t & IO::Binary ? "rb" : "r");
    if (!fptr) sthrow(IOException,
            String("Unable to open file ") + f.toCanonicalName());
}

FileInputStream::~FileInputStream() {
    fclose(fptr);
}

fsize_t FileInputStream::available() const {
    fsize_t cur = ftell(fptr);
    fseek(fptr, 0, SEEK_END);
    fsize_t end = ftell(fptr);
    fseek(fptr, cur, SEEK_SET);
    return end - cur;
}

fssize_t FileInputStream::read(Array<byte>& b, off_t offset, size_t len)
        throw(ArrayException,IOException) {
    if (!len) len = b.length;
    if (offset + len > b.length) sthrow(ArrayException, "Index out of bounds");
    if (eof()) return -1;
    return fread(b.carray(), 1, b.length, fptr);
}

bool FileInputStream::eof() const {
    return feof(fptr);
}

void FileInputStream::mark(fsize_t f) {
    _mark = ftell(fptr);
    _markExpires = std::min(f, available());
}

fsize_t FileInputStream::skip(fsize_t f) {
    fsize_t cur = ftell(fptr);
    fseek(fptr, f, SEEK_CUR);
    fsize_t act = ftell(fptr);
    return act - cur;
}

void FileInputStream::reset() {
    fseek(fptr, _mark, SEEK_SET);
}

InputStream & FileInputStream::operator>>(byte& b) {
    fread(&b, 1, 1, fptr);
    return *this;
}
SYLPH_END_NAMESPACE

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
