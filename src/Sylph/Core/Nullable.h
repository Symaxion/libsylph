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

#ifndef SYLPH_CORE_NULLABLE_H_
#define SYLPH_CORE_NULLABLE_H_

#include "Object.h"
#include "Exception.h"
#include "Pointer.h"

SYLPH_BEGIN_NAMESPACE

template<class T>
class Nullable {
public:

    Nullable() : data(null) {}
    Nullable(const Nullable& n) : data(new Data(*n.data));
    Nullable(const T& t) : data(new T(t)) {}
    Nullable(const struct null&) : data(null) {}

#ifndef SYLPH_FTR_NO_NULLPTR
    Nullable(const nullptr_t&) : data(null) {}
#endif

#ifndef SYLPH_FTR_NO_RVALUES
    Nullable(T&& t) : data(new T(forward(t))) {}

    Nullable(Nullable&& o) : data(null) {
        swap(this->data, o.data);
    }
#endif

    ~Nullable() { delete data; }

    Nullable& operator=(const T& t) {
        delete data;
        data = new T(t);
    }

    Nullable& operator=(const struct null&) {
        delete data;
        data = null;
    } 

#ifndef SYLPH_FTR_NO_NULLPTR
    Nullable& operator=(const nullptr_t&) {
        delete data;
        data = null;
    } 
#endif 

#ifndef SYLPH_FTR_NO_RVALUES
    Nullable& operator=(T&& t) { 
        delete data;
        data = new T(forward(t));
    }

    Nullable& operator=(Nullable&& o) {
        this->data = null;
        swap(this->data, o.data);
    }
#endif

    bool operator==(const T& t) const {
        if(!data) return false;
        else return *data == t;

    }

    bool operator==(const struct null&) const {
        return !data;
    }

#ifndef SYLPH_FTR_NO_NULLPTR
    bool operator==(const nullptr_t&) const {
        return !data;
    }
#endif 

    bool operator!=(const T& t) const {
        return !(*this == t);
    }

    bool operator!=(const struct null&) const {
        return data;
    }

#ifndef SYLPH_FTR_NO_NULLPTR
    bool operator!=(const nullptr_t&) const {
        return data;
    }
#endif 

    operator T&() throw(NullPointerException) {
        check_nullptr(data);
        return *data;
    }
    
    operator const T&() const throw(NullPointerException) {
        check_nullptr(data);
        return *data;
    }

private:
    T* data;    
};


SYLPH_END_NAMESPACE

#endif /* SYLPH_CORE_NULLABLE_H_ */

// vim: ts=4:sts=4:sw=4:sta:et:tw=80:nobk

