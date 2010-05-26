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

class PointerManagerImplBase {
public:
    virtual ~PointerManagerImplBase() {}
};

template<class T>
class PointerManagerImpl : public PointerManagerImplBase {
    typedef typename T::iterator itr;
public:
    PointerManagerImpl(T& t) : coll(&t) {}
    virtual ~PointerManagerImpl() {
        for(itr t = coll->begin(); t != coll->end(); ++t) {
            delete *t;
        }
    }
private:
    T * coll;
};

template<class T>
inline PointerManagerImpl<T>* manage(T& t) {
    return new PointerManagerImpl<T>(t);
}

/**
 * @todo Write documentation!
 */
class PointerManager : public virtual Object {
public:
    PointerManager() : impl(0) {}
    template<class T>
    PointerManager(PointerManagerImpl<T>* rhs) {
        operator=(rhs);
    }
    virtual ~PointerManager() {
        delete impl;
    }

    template<class T>
    PointerManager& operator=(PointerManagerImpl<T>* rhs) {
        impl = rhs;
        return *this;
    }

private:
    PointerManagerImplBase * impl;
};
SYLPH_END_NAMESPACE

#endif	/* POINTERMANAGER_H_ */

