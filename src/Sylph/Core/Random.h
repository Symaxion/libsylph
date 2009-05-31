/* 
 * File:   Random.h
 * Author: frank
 *
 * Created on 7 maart 2009, 13:32
 */

#ifndef RANDOM_H_
#define	RANDOM_H_

#include "Object.h"

SYLPH_BEGIN_NAMESPACE
class String;
typedef byte;
class ByteBuffer;
SYLPH_PUBLIC
class Random : public virtual Object {
public:
    Random();
    Random(long seed);
    Random(const Random& orig);
    virtual ~Random();

    byte nextByte();
    short nextShort();
    int nextInt();
    long nextLong();
    float nextFloat();
    double nextDouble();
    bool nextBool();
    String nextString(); //base64?
    ByteBuffer nextByteBuffer(std::size_t length);

private:
    long _next;
};
SYLPH_END_NAMESPACE

#endif	/* RANDOM_H_ */

