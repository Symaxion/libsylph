/* 
 * File:   BoolConvertible.h
 * Author: Frank "SeySayux" Erens <seysayux@gmail.com>
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

template <typename T = void> class BoolConvertible : public BoolConvertible_base {
public:

    operator bool_type() const {
        return (static_cast<const T*> (this))->toBool()
                ? &BoolConvertible_base::this_type_does_not_support_comparisons : 0;
    }
protected:

    ~BoolConvertible() {
    }
};

template<> class BoolConvertible<void> : public BoolConvertible_base {
public:

    operator bool_type() const {
        return toBool() == true ?
                &BoolConvertible_base::this_type_does_not_support_comparisons : 0;
    }
protected:
    virtual bool toBool() const = 0;

    virtual ~safe_bool() {
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

