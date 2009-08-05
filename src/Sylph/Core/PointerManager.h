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
 * Created on 13 juli 2009, 19:21
 */

#ifndef POINTERMANAGER_H_
#define	POINTERMANAGER_H_

#include "Object.h"
SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC
class PointerManager : public virtual Object {
public:
    PointerManager() {}
    virtual ~PointerManager() {}
};

template<class T>
class PointerManagerImpl : public PointerManager {
    typedef typename T::iterator itr;
public:
    PointerManagerImpl(const T& t) : coll(&t) {}
    virtual ~PointerManagerImpl() {
        for(typename itr::value_type t = coll.begin(); t != coll.end(); t++) {
            delete t;
        }
    }
private:
    T * coll;
};

template<class T>
PointerManager manage(const T& t) {
    return PointerManagerImpl<T>(t);
}

SYLPH_END_NAMESPACE

#endif	/* POINTERMANAGER_H_ */

