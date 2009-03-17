#include "Array.h"
#include "ArrayIterator.h"
#include "Util.h"

#include <algorithm>

SYLPH_START_NAMESPACE(Core)

Array::Array(std::size_t len) : length(len){
    carray = new T[length];
}

Array::Array(std::initializer_list<T> il) : length(il.size()) {
    carray = new T[il.size()];
    carraycopy(il.begin(),0,carray,0,il.size());
}

Array::Array(T & array[]) : length(carraysize(array)) {
    carray = new T[length];
    carraycopy(array,0,carray,0,length;
}

Array::Array(Array<T> & ar) : length(ar.length) {
    carray = new T[length];
    carraycopy(ar.carray,0,carray,0,length);
}

Array::~Array() {
    delete[] carray;
}

T * Array::carray() {
    return carray;
}

const T * Array::carray() const {
    return carray;
}

Iterator<T> Array::iterator() const {
    return ArrayIterator<T> (*this);
}

MutableIterator<T> Array::mutableIterator() const {
    return ArrayMutableIterator<T> (*this);
}

template<class T> Array& Array::operator=(const Array<T> & other) {
    for (std::size_t idx = 0; idx < other.length(); idx++) {
        carray[idx] = other.carray[idx];
    }
    return * this;
};

T& Array::operator[](std::size_t idx) throw (Exception) {
    if (idx < length) {
        return carray[idx];
    } else {
        sthrow(ArrayException);
    }
}

const T& Array::operator[](std::size_t idx) const throw (Exception) {
    if (idx < length) {
        return carray[idx];
    } else {
        sthrow(ArrayException);
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
SYLPH_END_NAMESPACE(Core)
