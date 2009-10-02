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
 * Created on 19 december 2008, 14:46
 */

#ifndef HASHABLE_H_
#define	HASHABLE_H_

#include "Object.h"
#include "Primitives.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

/**
 * Interface to indicate this object provides its own @c hashCode function.
 * This interface is used by @c Sylph::Hash to determine when to use the builtin
 * hash generator or the one supplied by the class itself.
 */
class Hashable : public virtual Object {
public:
    /**
     * Calculates an unique hash code for this object. The returned value should
     * be indentical for equal classes. It is possible to have the same hash
     * code for non-equal classes, returning a constant number is a valid
     * implementation of this function. However, the hash code is used for
     * optimalisation in several collection classes, therefore, having this
     * function return a generally unique hash code (such that
     * <code>x != y</code> almost certainly guarantees <code>x.hashCode() !=
     * y.hashCode()</code> will make access times for those collection classes
     * much faster.
     * @return A generally unique hash value for this class.
     */
    virtual sint hashCode() const = 0;
};
SYLPH_END_NAMESPACE

#endif	/* HASHABLE_H_ */

