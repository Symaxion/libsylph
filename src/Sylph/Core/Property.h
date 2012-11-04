/*
 * LibSylph Class Library
 * Copyright (c) 2012 Frank "SeySayux" Erens <seysayux@gmail.com>
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
 */

#ifndef SYLPH_CORE_PROPERTY_H_
#define SYLPH_CORE_PROPERTY_H_

#include "Object.h"
#include "Function.h"

SYLPH_BEGIN_NAMESPACE

// Weak properties
// read-write weak property
template<class T, bool B = false>
class WeakProperty : public WeakProperty<T, true> {
public:
    virtual void set(const T& t) = 0;

    T& operator*() { return get(); }
    T& operator->() { return get(); }

    template<class U>
    WeakProperty<T,B>& operator=(const U& u) { set(u); return *this; }

};

// read-only weak property
template<class T>
class WeakProperty<T, true> {
    typedef WeakProperty<T, true> Self;

    virtual T& get() { return const_cast<T&>(constify(*this).get()); }
    virtual const T& get() const = 0;

    const T& operator*() const { return get(); }
    const T& operator->() const { return get(); }

    template<class U>
    auto operator+(const U& u) -> decltype(get() + u) {
        return get() + u;
    }
    template<class U>
    auto operator-(const U& u) -> decltype(get() - u) {
        return get() - u;
    }
    template<class U>
    auto operator*(const U& u) -> decltype(get() * u) {
        return get() * u;
    }
    template<class U>
    auto operator/(const U& u) -> decltype(get() / u) {
        return get() / u;
    }
    template<class U>
    auto operator%(const U& u) -> decltype(get() % u) {
        return get() % u;
    }
};

// Strong properties
template<class T, bool B = false>
class Property {
};

// read-write property
template<class T>
class Property<T, false> : public WeakProperty<T, false> {
public:
    Property() : value(T()) {}
    Property(const T& t) : value(t) {}
    virtual ~Property() {}

    virtual void set(const T& t) { value = t; }
    virtual const T& get() const { return value; }
private:
    T value;
};

// read-only property
template<class T>
class Property<T, true> : public WeakProperty<T, true> {
public:
    Property() : value(T()) {}
    Property(const T& t) : value(t) {}
    virtual ~Property() {}

    virtual const T& get() const { return value; }
protected:
    T value;
};

#define weak_property struct : public ::Sylph::WeakProperty
#define property struct : public ::Sylph::Property

SYLPH_END_NAMESPACE

#endif /* SYLPH_CORE_PROPERTY_H_ */

// vim: ts=4:sts=4:sw=4:sta:et:tw=80:nobk
