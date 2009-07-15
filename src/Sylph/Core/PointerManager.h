/* 
 * File:   PointerManager.h
 * Author: Frank "SeySayux" Erens <seysayux@gmail.com>
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
    typedef T::iterator itr;
public:
    PointerManagerImpl(const T& t) : coll(&t) {}
    virtual ~PointerManagerImpl() {
        for(itr::value_type t = coll.begin(); t != coll.end(); t++) {
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

