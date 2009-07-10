/* 
 * File:   StringBuffer.h
 * Author: Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * Created on 9 juli 2009, 16:19
 */

#ifndef STRINGBUFFER_H_
#define	STRINGBUFFER_H_

#include "Object.h"
#include "Array.h"
#include "Primitives.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC
typedef uint16_t uchar;
class String;

class StringBuffer : public virtual Object {
public:
    explicit StringBuffer(std::size_t len = 16) : buf(len), _length(0) {}
    StringBuffer(const String);
    virtual ~StringBuffer();

    size_t length() const;
    void deleteSubstring(idx_t start, idx_t end);
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

    String toString() const;
    operator String() const;
private:
    Array<uchar> buf;
    size_t _length;
    void ensureCapacity(std::size_t capacity);
};
SYLPH_END_NAMESPACE

#endif	/* STRINGBUFFER_H_ */

