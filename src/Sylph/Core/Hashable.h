/* 
 * File:   Hashable.h
 * Author: frank
 *
 * Created on 19 december 2008, 14:46
 */

#ifndef _HASHABLE_H
#define	_HASHABLE_H

#include "Object.h"

SYLPH_START_NAMESPACE(Core)
SYLPH_PUBLIC
class Hashable : public Object {
    virtual int hashCode() = 0;
};
SYLPH_END_NAMESPACE(Core)

#endif	/* _HASHABLE_H */

