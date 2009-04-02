#include "Array.h"
#include "ArrayIterator.h"
#include "Util.h"

#include <algorithm>

SYLPH_BEGIN_NAMESPACE

Array::Array(std::size_t len) : length(len) {
    _carray = (T*) calloc(len, sizeof(T));
}

Array::Array(std::initializer_list<T> il) : length(il.size()) {
    _carray = (T*) calloc(il.size(), sizeof(T));
    carraycopy(il.begin(), 0, _carray, 0, il.size());
}

Array::Array(T & array[]) : length(carraysize(array)) {
    _carray = (T*) calloc(length,sizeof(T));
    carraycopy(array, 0, _carray, 0, length);
}

Array::Array(Array<T> & ar) : length(ar.length) {
    _carray = (T*) calloc(length,sizeof(T));
    carraycopy(ar._carray, 0, _carray, 0, length);
}

Array::~Array() {
    free(_carray);
}

T * Array::carray() {
    return _carray;
}

const T * Array::carray() const {
    return _carray;
}

Iterator<T> Array::iterator() const {
    return ArrayIterator<T> (*this);
}

MutableIterator<T> Array::mutableIterator() const {
    return ArrayMutableIterator<T> (*this);
}

const T& Array::operator[](std::size_t idx) const throw (Exception) {
    if (idx < length) {
        return carray[idx];
    } else {
        sthrow(ArrayException, "Array overflow");
    }
}

template<class T>
inline bool operator==(const Array<T>& lhs, const Array<T>& rhs) {
    return lhs.length == rhs.length ?
            std::equal(lhs.carray[0], lhs.carray[lhs.length - 1], rhs[0]) : false;
}

template<class T>
inline bool operator<(const Array<T>& lhs, const Array<T>& rhs) {
    return lhs.length == rhs.length ?
            std::lexicographical_compare(lhs.carray[0], lhs.carray[lhs.length - 1],
            rhs[0], rhs[rhs.length - 1]) : false;
}
SYLPH_END_NAMESPACE
