#include "ArrayIterator.h"
#include "Array.h"

SYLPH_START_NAMESPACE(Core)

bool ArrayIterator::hasNext() const {
    return idx < ar->length();
}

const T & ArrayIterator::next() const {
    return last = *ar[idx++];
}

bool ArrayIterator::hasPrevious() const {
    return idx > 0;
}

const T & ArrayIterator::previous() const {
    return last = *ar[--idx];
}

std::size_t ArrayIterator::nextIndex() const {
    return idx;
}

std::size_t ArrayIterator::previousIndex() const {
    return idx-1;
}

void ArrayMutableIterator::set(T & t) throw(Exception) {
    *last = t;
}

void ArrayMutableIterator::insert(T & t) throw(Exception) {
    sthrow(UnsupportedOperationException);
}

void ArrayMutableIterator::remove() throw(Exception) {
    sthrow(UnsupportedOperationException);
}

SYLPH_END_NAMESPACE(Core)
