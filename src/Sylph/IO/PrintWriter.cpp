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

#include "PrintWriter.h"
#include <cstring>

SYLPH_BEGIN_NAMESPACE
OutputStream& PrintWriter::outputStream() {
    return out;
}

const OutputStream& PrintWriter::outputStream() const {
    return out;
}

bool PrintWriter::uppercase() const {
    return _uc;
}

void PrintWriter::setUppercase(bool uc) {
    _uc = uc;
}

bool PrintWriter::toBool() const {
    return out.toBool();
}

PrintWriter& PrintWriter::operator<<(bool b) {
    return operator<<(String(b));
}

PrintWriter& PrintWriter::operator<<(char c) {
    return operator<<(String(c));
}

PrintWriter& PrintWriter::operator<<(sint i) {
    switch (_nt) {
        case DEC:
            operator<<(String(i));
            break;
        case HEX:
            operator<<(String::fromHex(i, _uc));
            break;
        case OCT:
            operator<<(String::fromOct(i));
            break;
    }
    return *this;
}

PrintWriter& PrintWriter::operator<<(suint i) {
    switch (_nt) {
        case DEC:
            operator<<(String(i));
            break;
        case HEX:
            operator<<(String::fromHex(i, _uc));
            break;
        case OCT:
            operator<<(String::fromOct(i));
            break;
    }
    return *this;
}

PrintWriter& PrintWriter::operator<<(slong l) {
    switch (_nt) {
        case DEC:
            operator<<(String(l));
            break;
        case HEX:
            operator<<(String::fromHex(l, _uc));
            break;
        case OCT:
            operator<<(String::fromOct(l));
            break;
    }
    return *this;
}

PrintWriter& PrintWriter::operator<<(sulong l) {
    switch (_nt) {
        case DEC:
            operator<<(String(l));
            break;
        case HEX:
            operator<<(String::fromHex(l, _uc));
            break;
        case OCT:
            operator<<(String::fromOct(l));
            break;
    }
    return *this;
}

PrintWriter& PrintWriter::operator<<(float f) {
    return operator<<(String(f));
}

PrintWriter& PrintWriter::operator<<(String s) {
    const char * toWrite = s.utf8();
    for (idx_t i = 0; i <= std::strlen(toWrite); i++) {
        out << toWrite[i];
    }
    return *this;
}

PrintWriter& PrintWriter::operator<<(PrintWriter&(*f)(PrintWriter&)) {
    return f(*this);
}

PrintWriter& flush(PrintWriter& pw) {
    pw.outputStream() << flush;
    return pw;
}

PrintWriter& endl(PrintWriter& pw) {
    return pw << '\n' << flush;
}

PrintWriter& ends(PrintWriter& pw) {
    return pw << '\0' << flush;
}

PrintWriter& dec(PrintWriter& pw) {
    pw._nt = PrintWriter::DEC;
    return pw;
}

PrintWriter& hex(PrintWriter& pw) {
    pw._nt = PrintWriter::HEX;
    return pw;
}

PrintWriter& oct(PrintWriter& pw) {
    pw._nt = PrintWriter::OCT;
    return pw;
}

PrintWriter& uppercase(PrintWriter& pw) {
    pw.setUppercase(true);
    return pw;
}

PrintWriter& nouppercase(PrintWriter& pw) {
    pw.setUppercase(false);
    return pw;
}
SYLPH_END_NAMESPACE

// vim: ts=4:sts=4:sw=4:sta:et:tw=80:nobk
