/* 
 * File:   BufferedOutputStream.h
 * Author: Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * Created on 30 juni 2009, 12:07
 */

#ifndef BUFFEREDOUTPUTSTREAM_H_
#define	BUFFEREDOUTPUTSTREAM_H_

#include "OutputStream.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC
class BufferedOutputStream : public OutputStream {
public:
    BufferedOutputStream(const OutputStream& _orig, size_t bufsize = 1024) :
        orig(_orig), buffer(bufsize) {}
    virtual ~BufferedOutputStream();
    void close();

    void flush();
    void write(const byte b);
private:
    OutputStream& orig;
    Array<byte> buffer;
};

SYLPH_END_NAMESPACE

#endif	/* BUFFEREDOUTPUTSTREAM_H_ */

