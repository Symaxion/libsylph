#include "FileInputStream.h"
#include "../Core/File.h"

SYLPH_BEGIN_NAMESPACE
FileInputStream::FileInputStream(File& f, IO::IOType t) {
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

fssize_t FileInputStream::read(Array<byte>& b, off_t offset, size_t len) {
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
