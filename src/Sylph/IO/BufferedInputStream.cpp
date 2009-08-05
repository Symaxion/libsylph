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
}

void BufferedInputStream::readNext() {
    used = orig.read(buffer);
    currentIdx = 0;
}
SYLPH_END_NAMESPACE
