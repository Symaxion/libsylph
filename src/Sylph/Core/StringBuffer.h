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
 * Created on 9 juli 2009, 16:19
 */

#ifndef STRINGBUFFER_H_
#define	STRINGBUFFER_H_

#include "Object.h"
#include "Array.h"
#include "Primitives.h"
#include "String.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC
typedef uint16_t uchar;

/**
 * @todo Write documentation!
 */
class StringBuffer : public virtual Object {
public:
    explicit StringBuffer(std::size_t len = 16) : buf(len), _length(0) {}
    StringBuffer(const String);
    virtual ~StringBuffer();

    size_t length() const;
    void deleteSubstring(idx_t start, idx_t end);
    void clear();
    const uchar& at(idx_t idx) const;
    uchar& at(idx_t idx);

    StringBuffer& operator<<(bool b);
    StringBuffer& operator<<(char c);
    StringBuffer& operator<<(Array<char> c);
    StringBuffer& operator<<(uchar c);
    StringBuffer& operator<<(Array<uchar> c);
    StringBuffer& operator<<(sint i);
    StringBuffer& operator<<(suint i);
    StringBuffer& operator<<(slong l);
    StringBuffer& operator<<(sulong l);
    StringBuffer& operator<<(float f);
    StringBuffer& operator<<(double d);
    StringBuffer& operator<<(String s);
    StringBuffer& operator<<(const char* s) {
        return operator<<(String(s));
    }

    template<class T>
    inline StringBuffer& operator+=(T t) {
        return operator<<(t);
    }

    String toString() const;
    operator String() const;
    
private:
    Array<uchar> buf;
    size_t _length;
    void ensureCapacity(std::size_t capacity);
};
SYLPH_END_NAMESPACE

#endif	/* STRINGBUFFER_H_ */

