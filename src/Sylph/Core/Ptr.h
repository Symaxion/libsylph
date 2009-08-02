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
 * Created on 13 juni 2009, 17:07
 */

#ifndef PTR_H_
#define	PTR_H_

#include "Object.h" //macros
#include "Comparable.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC
template<class T>
class Ptr {
public:
    Ptr() : pointee(NULL) {}
    Ptr(T * t) : pointee(t) {}
    Ptr(const Ptr& orig) : pointee(orig.pointee) {}
    virtual ~Ptr() {
        delete pointee;
    }
    T& operator*() { return *pointee; }
    const T& operator*() const { return *pointee; }
    T& operator->() { return *pointee; }
    const T& operator->() const { return *pointee; }

    bool operator==(const Ptr<T> & p) const {return p.pointee == pointee; }
    bool operator==(const T * t) const { return pointee == t; }
private:
    T * pointee;
};
SYLPH_END_NAMESPACE

#endif	/* PTR_H_ */

