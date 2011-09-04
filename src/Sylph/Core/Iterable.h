/*
 * LibSylph Class Library
 * Copyright (C) 2011 Frank "SeySayux" Erens <seysayux@gmail.com>
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
 * Created on 6 december 2008, 17:15
 */

#ifndef SYLPH_CORE_ITERABLE_H_
#define	SYLPH_CORE_ITERABLE_H_

#include "Object.h"
#include "Iterator.h"

SYLPH_BEGIN_NAMESPACE

SYLPH_END_NAMESPACE

#define S_ITERABLE(type) \
public: \
typedef type Type; \
typedef const iterator const_iterator; \
\
    virtual iterator begin() { return iterator(true, this); }\
    virtual iterator end() { return iterator(false, this); }\
\
    virtual const_iterator begin() const { return iterator(true, this); }\
    virtual const_iterator end() const { return iterator(false, this); }


#endif	/* SYLPH_CORE_ITERABLE_H_ */

