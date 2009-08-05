/*
 * LibSylph Class Library
 * Copyright (C) 2009 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LibSylph Pulbic License as published
 * by the LibSylph Developers; either version 1.0 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LibSylph
 * Public License for more details.
 *
 * You should have received a copy of the LibSylph Public License
 * along with this Library, if not, contact the LibSylph Developers.
 *
 * Created on 7 maart 2009, 13:32
 */

#ifndef RANDOM_H_
#define	RANDOM_H_

#include "Object.h"
#include "String.h"
#include "Primitives.h"

SYLPH_BEGIN_NAMESPACE
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

