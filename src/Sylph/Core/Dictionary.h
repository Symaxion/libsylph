/*
 * LibSylph Class Library
 * Copyright (C) 2012 Frank "SeySayux" Erens <seysayux@gmail.com>
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
 * Created on 8 februari 2009, 14:19
 */

#ifndef SYLPH_CORE_DICTIONARY_H
#define	SYLPH_CORE_DICTIONARY_H

#include "HashMap.h"
#include "String.h"
#include "Any.h"

SYLPH_BEGIN_NAMESPACE
/**
 * A Dictionary is a HashMap that maps Strings to Anys. This typedef is provided
 * because this is the most commonly used instance of a HashMap -- that is,
 * String to T with Any a generic wrapper for any T. It is provided solely for
 * convenience and currently does not have any special properties above a
 * HashMap.
 */
typedef HashMap<String, Any> Dictionary;
SYLPH_END_NAMESPACE

#endif	/* SYLPH_CORE_DICTIONARY_H */

// vim: ts=4:sts=4:sw=4:sta:et:tw=80:nobk
