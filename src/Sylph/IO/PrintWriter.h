/* 
 * File:   PrintWriter.h
 * Author: Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * Created on 30 juni 2009, 12:06
 */

#ifndef PRINTWRITER_H_
#define	PRINTWRITER_H_

#include "../Core/Object.h"
#include "../Core/Primitives.h"
#include "../Core/BoolConvertible.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC
#ifndef S_NEWLINE_CHAR
    #include "../OS/GuessOS.h"
    #ifdef SYLPH_OS_WINDOWS
        #define S_NEWLINE_CHAR "\r\n"
    #else
        #define S_NEWLINE_CHAR "\n"
    #endif
#endif
class OutputStream;

class PrintWriter : public BoolConvertible<PrintWriter> {
    friend PrintWriter& dec(PrintWriter&);
    friend PrintWriter& hex(PrintWriter&);
    friend PrintWriter& oct(PrintWriter&);
private:
    enum NumberType {
        DEC,
        HEX,
        OCT
    };
    
public:
    PrintWriter(OutputStream& _out) : out(_out), _uc(false), _nt(DEC) {}

    OutputStream& outputStream();
    const OutputStream& outputStream() const;

    bool uppercase() const;
    void setUppercase(bool);

    bool toBool() const;

    PrintWriter& operator<<(bool b);
    PrintWriter& operator<<(char c);
    PrintWriter& operator<<(sint i);
    PrintWriter& operator<<(suint i);
    PrintWriter& operator<<(slong l);
    PrintWriter& operator<<(sulong l);
    PrintWriter& operator<<(float f);
    PrintWriter& operator<<(String s);
    PrintWriter& operator<<(PrintWriter&(*f)(PrintWriter&));
private:
    OutputStream& out;
    bool _uc;
    NumberType _nt;
};

PrintWriter& flush(PrintWriter&);
PrintWriter& endl(PrintWriter&);
PrintWriter& ends(PrintWriter&);
PrintWriter& dec(PrintWriter&);
PrintWriter& hex(PrintWriter&);
PrintWriter& oct(PrintWriter&);
PrintWriter& uppercase(PrintWriter&);
PrintWriter& nouppercase(PrintWriter&);

SYLPH_END_NAMESPACE

#endif	/* PRINTWRITER_H_ */

