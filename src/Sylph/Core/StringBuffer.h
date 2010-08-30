/*
 * LibSylph Class Library
 * Copyright (C) 2010 Frank "SeySayux" Erens <seysayux@gmail.com>
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
 * Created on 9 juli 2009, 16:19
 */

#ifndef STRINGBUFFER_H_
#define	STRINGBUFFER_H_

#include "Object.h"
#include "Array.h"
#include "Primitives.h"
#include "String.h"

SYLPH_BEGIN_NAMESPACE
typedef uint16_t uchar;

/**
 * @todo Write documentation!
 */
class StringBuffer : public virtual Object {
public:
    /** */
    explicit StringBuffer(std::size_t len = 16) : buf(len), _length(0) {}
    /** */
    StringBuffer(const String);
    /** */
    virtual ~StringBuffer();

    /** */
    size_t length() const;
    /** */
    void deleteSubstring(idx_t start, idx_t end);
    /** */
    void clear();
    /** */
    const uchar& at(idx_t idx) const;
    /** */
    uchar& at(idx_t idx);

    /** */
    StringBuffer& operator<<(bool b);
    /** */
    StringBuffer& operator<<(char c);
    /** */
    StringBuffer& operator<<(Array<char> c);
    /** */
    StringBuffer& operator<<(uchar c);
    /** */
    StringBuffer& operator<<(Array<uchar> c);
    /** */
    StringBuffer& operator<<(sint i);
    /** */
    StringBuffer& operator<<(suint i);
    /** */
    StringBuffer& operator<<(slong l);
    /** */
    StringBuffer& operator<<(sulong l);
    /** */
    StringBuffer& operator<<(float f);
    /** */
    StringBuffer& operator<<(double d);
    /** */
    StringBuffer& operator<<(String s);
    /** */
    StringBuffer& operator<<(const char* s) {
        return operator<<(String(s));
    }

    /** */
    template<class T>
    inline StringBuffer& operator+=(T t) {
        return operator<<(t);
    }

    /** */
    String toString() const;
    /** */
    operator String() const;
    
private:
    Array<uchar> buf;
    size_t _length;
    void ensureCapacity(std::size_t capacity);
};
SYLPH_END_NAMESPACE

#endif	/* STRINGBUFFER_H_ */

