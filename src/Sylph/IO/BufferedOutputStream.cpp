#include "BufferedOutputStream.h"
#include "../Core/Array.h"

SYLPH_BEGIN_NAMESPACE
BufferedOutputStream::~BufferedOutputStream() {
}

void BufferedOutputStream::close() {
    orig.close();
}

void BufferedOutputStream::flush() {
    for(idx_t i = 0; i < used; i++) {
        orig.write(buffer[i]);
    }
    used = 0;
    orig.flush();
}

BufferedOutputStream& BufferedOutputStream::operator<<(const byte b) {
    if(used == buffer.length) flush();
    buffer[used] = b;
    used++;
    return *this;
}
SYLPH_END_NAMESPACE