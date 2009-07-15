/* 
 * File:   BufferedInputStream.h
 * Author: Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * Created on 30 juni 2009, 12:07
 */

#ifndef BUFFEREDINPUTSTREAM_H_
#define	BUFFEREDINPUTSTREAM_H_

#include "InputStream.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC
class BufferedInputStream : public InputStream {
public:
    BufferedInputStream(const InputStream& _orig, size_t bufsize = 1024) :
        orig(_orig), buffer(bufsize) {}
    virtual ~BufferedOutputStream();

private:
    InputStream& orig;
    Array<byte> buffer;
};
SYLPH_END_NAMESPACE

#endif	/* BUFFEREDINPUTSTREAM_H_ */

