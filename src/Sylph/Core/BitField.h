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

/**
 * Class containing a bitfield of size size_t * N
 */
template<size_t N>
class BitField {
public:

    /**
     * Proxy class used to be able to assign a binary value using an indexing
     * operator on a BitField.
     */
    class BitProxy {
    public:

        /**
         * Constructor taking a pointer to a BitField and the index of the bit
         * it is proxying.
         * @param b The BitField it is proxying for.
         * @param idx Index of the bit to proxy.
         */
        BitProxy(BitField<N>* b, idx_t idx) : mBf(b), mIdx(idx) {}
        
        /**
         * Bit to bool conversion operator.
         */
        operator bool() const {
            return mBf->get(mIdx);
        }
        
        /**
         * Assignment operator, sets bit to the value given.
         * @param b The value the bit will be set to.
         */
        BitProxy& operator=(bool b) {
            b ? mBf->set(mIdx) : mBf->reset(mIdx);
            return *this;
        }

        /**
         * Compound XOR operator, allowing you to toggle a bit.
         * @param b Boolean deciding whether to toggle or not.
         */
        BitProxy& operator^=(bool b) {
            if(b)
                mBf->toggle(mIdx);
            return *this;
        }

    private:

        /**
         * The bitfield to proxy for.
         */
        BitField<N>* mBf;

        /**
         * Index of the bit to proxy for.
         */
        idx_t mIdx;
    };

    /**
     * The index of the MSB.
     */
    const static idx_t MSB;

    /**
     * The index of the LSB, always 0.
     */
    const static idx_t LSB;

public:

    /**
     * Ctor to init the bitfield to 0.
     */
    BitField() : mBf{0} {}

    /**
     * Set the bit at index i high.
     * @param i The bit to set.
     */
    void set(idx_t i) {
        if(i > MSB)
            sthrow(ArrayException, "Index out of bounds.");
        idx_t q = i / CHAR_BIT;
        idx_t r = i % CHAR_BIT;

        mBf[q] |= 1 << r;
    }

    /**
     * Set the bits in range r to high.
     * @param r The bits to set.
     */
    void set(irange r) {
        if(r.first > MSB || r.last > MSB)
            sthrow(ArrayException, "Index out of bounds.");

        for(idx_t i = r.first; i <= r.last; ++i)
            set(i);
    }

    /**
     * Reset the bit at index i to low.
     * @param i The bit to reset.
     */
    void reset(idx_t i) {
        if(i > MSB)
            sthrow(ArrayException, "Index out of bounds.");
        idx_t q = i / CHAR_BIT;
        idx_t r = i % CHAR_BIT;

        mBf[q] &= ~(1 << r);
    }

    /**
     * Reset the bits in range r to low.
     * @param r The bits to reset.
     */
    void reset(irange r) {
        if(r.first > MSB || r.last > MSB)
            sthrow(ArrayException, "Index out of bounds.");

        for(idx_t i = r.first; i <= r.last; ++i)
            reset(i);
    }

    /**
     * Toggle the bit at index i.
     * @param i The bit to toggle.
     */
    void toggle(idx_t i) {
        if(i > MSB)
            sthrow(ArrayException, "Index out of bounds.");
        idx_t q = i / CHAR_BIT;
        idx_t r = i % CHAR_BIT;

        mBf[q] ^= 1 << r;
    }

    /**
     * Toggle the bits in range r.
     * @param r The bits to toggle.
     */
    void toggle(irange r) {
        if(r.first > MSB || r.last > MSB)
            sthrow(ArrayException, "Index out of bounds.");

        for(idx_t i = r.first; i <= r.last; ++i)
            toggle(i);
    }

    /**
     * Get the bit at index i.
     * @param i The bit to get.
     * @return The requested bit.
     */
    bool get(idx_t i) {
        if(i > MSB)
            sthrow(ArrayException, "Index out of bounds.");
        idx_t q = i / CHAR_BIT;
        idx_t r = i % CHAR_BIT;

        return mBf[q] & (1 << r);
    }
        
    /**
     * Overloaded indexing operator, returns a BitProxy for the bit at index i,
     * a BitProxy is assignable and togglable.
     * @param i The bit to get a proxy for.
     * @return A proxy for the requested bit.
     */
    BitProxy operator[](idx_t i) {
        return BitProxy(this, i);
    }

    /**
     * Overloaded indexing operator, returns a BitProxy for the bit at index i,
     * a BitProxy is assignable and togglable.
     * @param i The bit to get a proxy for.
     * @return A proxy for the requested bit.
     */
    const BitProxy operator[](idx_t i) const {
        return BitProxy(this, i);
    }

private:
    /**
     * The internal representation of the BitField.
     */
    byte mBf[N];
};

template<size_t N> const idx_t BitField<N>::MSB = N * CHAR_BIT - 1;
template<size_t N> const idx_t BitField<N>::LSB = 0;

SYLPH_END_NAMESPACE

#endif /* SYLPH_CORE_BITFIELD_H_ */

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
