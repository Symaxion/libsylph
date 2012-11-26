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
 * Created on 13 juli 2009, 19:21
 */

#ifndef SYLPH_CORE_POINTERMANAGER_H_
#define	SYLPH_CORE_POINTERMANAGER_H_

#include "Object.h"
SYLPH_BEGIN_NAMESPACE

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

#endif	/* SYLPH_CORE_POINTERMANAGER_H_ */

// vim: ts=4:sts=4:sw=4:sta:et:tw=80:nobk
