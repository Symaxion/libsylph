/*
 * File:   VectorIterator.cpp
 * Author: frank
 *
 * Created on 6 maart 2009, 18:39
 */

#include "VectorIterator.h"
#include "Vector.h"

SYLPH_START_NAMESPACE(Core)

bool VectorIterator::hasNext() const {
    return idx < vt->size();
}

const T & VectorIterator::next() const {
    return last = *vt[idx++];
}

bool VectorIterator::hasPrevious() const {
    return idx > 0;
}

const T & VectorIterator::previous() const {
    return last = *vt[--idx];
}

std::size_t VectorIterator::nextIndex() const {
    return idx;
}

std::size_t VectorIterator::previousIndex() const {
    return idx-1;
}

void VectorMutableIterator::set(T & t) throw(Exception) {
    *last = t;
}

void VectorMutableIterator::insert(T & t) throw(Exception) {
    sthrow(UnsupportedOperationException, "Not yet implemented!");
}

void VectorMutableIterator::remove() throw(Exception) {
    vt.remove(*last)
}

SYLPH_END_NAMESPACE(Core)
