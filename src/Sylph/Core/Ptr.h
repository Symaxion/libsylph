/* 
 * File:   Ptr.h
 * Author: frank
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

