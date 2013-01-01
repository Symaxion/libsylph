/*
 * LibSylph Class Library
 * Copyright (C) 2013 Frank "SeySayux" Erens <seysayux@gmail.com>
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

#include "FileOutputStream.h"

SYLPH_BEGIN_NAMESPACE
FileOutputStream::FileOutputStream(File& f, IO::IOType t) throw(IOException) {
    fptr = fopen(f.toCanonicalName().utf8(), t & IO::Append ? (t & IO::Binary ?
            "ab" : "a") : (t & IO::Binary ? "w" : "wb"));
    if (fptr == null) {
        sthrow(IOException, (String("Unable to open file ") +
                f.toCanonicalName()).utf8());
    }
}
FileOutputStream::~FileOutputStream() {
    flush();
    close();
}

void FileOutputStream::write(const Array<byte> b, off_t off, size_t len)
        throw(IOException,ArrayException) {
    if (closed) sthrow(IOException, "Tried to write to a closed OutputStream!");
    if (len == 0) len = b.length;
    if (off + len > b.length) sthrow(ArrayException, "Array out of bounds");
    unsigned i = fwrite(b.carray(), 1, b.length, fptr);
    if(i != b.length) sthrow(IOException, "Unable to write to file");
}
void FileOutputStream::close() {
    OutputStream::close();
    fclose(fptr);
}

void FileOutputStream::flush() {
    fflush(fptr);
}

OutputStream & FileOutputStream::operator<<(const byte b)
        throw(IOException) {
    if (closed) sthrow(IOException, "Tried to write to a closed OutputStream!");
    int i = fwrite(&b, 1, 1, fptr);
    if(i != 1) sthrow(IOException, "Unable to write to file");
    return *this;
}
SYLPH_END_NAMESPACE

// vim: ts=4:sts=4:sw=4:sta:et:tw=80:nobk
