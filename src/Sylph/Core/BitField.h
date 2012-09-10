/*
 * LibSylph Class Library
 * Copyright (C) 2012 Randy "Villadelfia" Thiemann <uselinuxnow@gmail.com>
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

#ifndef SYLPH_CORE_BITFIELD_H_
#define SYLPH_CORE_BITFIELD_H_

#include "Object.h"
#include "Primitives.h"
#include "Range.h"
#include "Exception.h"

#include <climits>

SYLPH_BEGIN_NAMESPACE

template<size_t N>
class BitField {
public:
    class BitProxy {
    public:
        BitProxy(BitField<N>* b, idx_t idx) : mBf(b), mIdx(idx) {}
        
        operator bool() const {
            return mBf->get(mIdx);
        }
        
        BitProxy& operator=(bool b) {
            b ? mBf->set(mIdx) : mBf->reset(mIdx);
            return *this;
        }

        BitProxy& operator^=(bool b) {
            if(b)
                mBf->toggle(mIdx);
            return *this;
        }

    private:
        BitField<N>* mBf;
        idx_t mIdx;
    };

    const static idx_t MSB;
    const static idx_t LSB;

public:
    BitField() : mBf({0}) {}

    void set(idx_t i) {
        if(i > MSB)
            sthrow(ArrayException, "Index out of bounds.");
        idx_t q = i / CHAR_BIT;
        idx_t r = i % CHAR_BIT;

        mBf[q] |= 1 << r;
    }

    void set(irange r) {
        if(r.first > MSB || r.last > MSB)
            sthrow(ArrayException, "Index out of bounds.");

        for(idx_t i = r.first; i <= r.last; ++i)
            set(i);
    }

    void reset(idx_t i) {
        if(i > MSB)
            sthrow(ArrayException, "Index out of bounds.");
        idx_t q = i / CHAR_BIT;
        idx_t r = i % CHAR_BIT;

        mBf[q] &= ~(1 << r);
    }

    void reset(irange r) {
        if(r.first > MSB || r.last > MSB)
            sthrow(ArrayException, "Index out of bounds.");

        for(idx_t i = r.first; i <= r.last; ++i)
            reset(i);
    }

    void toggle(idx_t i) {
        if(i > MSB)
            sthrow(ArrayException, "Index out of bounds.");
        idx_t q = i / CHAR_BIT;
        idx_t r = i % CHAR_BIT;

        mBf[q] ^= 1 << r;
    }

    void toggle(irange r) {
        if(r.first > MSB || r.last > MSB)
            sthrow(ArrayException, "Index out of bounds.");

        for(idx_t i = r.first; i <= r.last; ++i)
            toggle(i);
    }

    bool get(idx_t i) {
        if(i > MSB)
            sthrow(ArrayException, "Index out of bounds.");
        idx_t q = i / CHAR_BIT;
        idx_t r = i % CHAR_BIT;

        return mBf[q] & (1 << r);
    }
        
    BitProxy operator[](idx_t i) {
        return BitProxy(this, i);
    }

    const BitProxy operator[](idx_t i) const {
        return BitProxy(this, i);
    }

private:
    byte mBf[N];
};

template<size_t N> const idx_t BitField<N>::MSB = N * CHAR_BIT - 1;
template<size_t N> const idx_t BitField<N>::LSB = 0;


SYLPH_END_NAMESPACE

#endif /* SYLPH_CORE_BITFIELD_H_ */

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
