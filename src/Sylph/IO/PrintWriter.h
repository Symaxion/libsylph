/*
 * LibSylph Class Library
 * Copyright (C) 2011 Frank "SeySayux" Erens <seysayux@gmail.com>
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
 * Created on 30 juni 2009, 12:06
 */

#ifndef PRINTWRITER_H_
#define	PRINTWRITER_H_

#include "../Core/Primitives.h"
#include "../Core/String.h"
#include "OutputStream.h"

SYLPH_BEGIN_NAMESPACE

class PrintWriter : public virtual Object {
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

