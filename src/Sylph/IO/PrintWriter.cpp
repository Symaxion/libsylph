#include "PrintWriter.h"
#include "Sylph/Core/String.h"

SYLPH_BEGIN_NAMESPACE
OutputStream& PrintWriter::outputStream() {
    return out;
}

const OutputStream& PrintWriter::outputStream() const {
    return out;
}

bool PrintWriter::uppercase() {
    return _uc;
}

void PrintWriter::setUppercase(bool uc) {
    _uc = uc;
}

bool PrintWriter::toBool() const {
    return out;
}

PrintWriter& PrintWriter::operator<<(bool b) {
    return operator<<(String(b));
}

PrintWriter& PrintWriter::operator<<(char c) {
    return operator<<(String(c))
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
            operator<<(String::fromOct(i, _uc));
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
            operator<<(String::fromOct(i, _uc));
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
            operator<<(String::fromOct(l, _uc));
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
            operator<<(String::fromOct(l, _uc));
            break;
    }
    return *this;
}

PrintWriter& PrintWriter::operator<<(float f) {
    return operator<<(String(f));
}

PrintWriter& PrintWriter::operator<<(String s) {
    char * toWrite = s.utf8();
    for (idx_t i = 0; i <= strlen(toWrite); i++) {
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
