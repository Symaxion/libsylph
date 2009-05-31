/* 
 * File:   Hashable.h
 * Author: frank
 *
 * Created on 19 december 2008, 14:46
 */

#ifndef _HASHABLE_H
#define	_HASHABLE_H

#include "Object.h"
#include "Primitives.h"

/*< rev Object-1
 *  rev Hashable-1
 */

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC
class Hashable : public virtual Object {
public:
    virtual sint hashCode() const = 0;
};
SYLPH_END_NAMESPACE

#endif	/* _HASHABLE_H */

