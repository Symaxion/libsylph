/* 
 * File:   Dictionary.h
 * Author: frank
 *
 * Created on 8 februari 2009, 14:19
 */

#ifndef _DICTIONARY_H
#define	_DICTIONARY_H

#include "HashMap.h"
#include "String.h"
#include "Any.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC
typedef HashMap<String,Any> Dictionary;
SYLPH_END_NAMESPACE

#endif	/* _DICTIONARY_H */

