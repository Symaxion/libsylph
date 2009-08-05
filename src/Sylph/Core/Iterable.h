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
 * Created on 6 december 2008, 17:15
 */

#ifndef ITERABLE_H_
#define	ITERABLE_H_

#include "Object.h"
#include "Iterator.h"

SYLPH_BEGIN_NAMESPACE

SYLPH_PUBLIC
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


#endif	/* ITERABLE_H_ */

