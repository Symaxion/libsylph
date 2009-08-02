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
 * Created on 12 juli 2009, 19:44
 */

#ifndef BOOLCONVERTIBLE_H_
#define	BOOLCONVERTIBLE_H_

#include "Object.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

class BoolConvertible_base : public virtual Object {
protected:
    typedef void (BoolConvertible_base::*bool_type)() const;

    void this_type_does_not_support_comparisons() const {
    }

    BoolConvertible_base() {
    }

    BoolConvertible_base(const BoolConvertible_base&) {
    }

    BoolConvertible_base & operator=(const BoolConvertible_base&) {
        return *this;
    }

    ~BoolConvertible_base() {
    }
};

template <typename T = void>
class BoolConvertible : public BoolConvertible_base {
public:

    operator bool_type() const {
        return (static_cast<const T*> (this))->toBool()
                ? &BoolConvertible::this_type_does_not_support_comparisons
                : 0;
    }
protected:

    ~BoolConvertible() {
    }
};

template<>
class BoolConvertible<void> : public BoolConvertible_base {
public:

    operator bool_type() const {
        return toBool() == true ?
                &BoolConvertible::this_type_does_not_support_comparisons : 0;
    }
protected:
    virtual bool toBool() const = 0;

    virtual ~BoolConvertible() {
    }
};

template <typename T, typename U>
void operator==(const BoolConvertible<T>& lhs, const BoolConvertible<U>& rhs) {
    lhs.this_type_does_not_support_comparisons();
    return false;
}

template <typename T, typename U>
void operator!=(const BoolConvertible<T>& lhs, const BoolConvertible<U>& rhs) {
    lhs.this_type_does_not_support_comparisons();
    return false;
}



SYLPH_END_NAMESPACE

#endif	/* BOOLCONVERTIBLE_H_ */

