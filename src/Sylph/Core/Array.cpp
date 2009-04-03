#include "Array.h"
#include "ArrayIterator.h"
#include "Util.h"

#include <algorithm>

SYLPH_BEGIN_NAMESPACE

template<class T>
Array<T>::Array(std::size_t len) : length(len) {
    _carray = (T*) calloc(len, sizeof(T));
}

template<class T>
Array<T>::Array(const std::initializer_list<T> & il) : length(il.size()) {
    _carray = (T*) calloc(il.size(), sizeof(T));
    carraycopy(il.begin(), 0, _carray, 0, il.size());
}

template<class T>
Array<T>::Array(const T array[]) : length(carraysize(array)) {
    _carray = (T*) calloc(length,sizeof(T));
    carraycopy(array, 0, _carray, 0, length);
}

template<class T>
Array<T>::Array(const Array<T> & ar) : length(ar.length) {
    _carray = (T*) calloc(length,sizeof(T));
    carraycopy(ar._carray, 0, _carray, 0, length);
}

template<class T>
Array<T>::~Array() {
    free(_carray);
}

template<class T>
T * Array<T>::carray() {
    return _carray;
}

template<class T>
const T * Array<T>::carray() const {
    return _carray;
}

template<class T>
Iterator<T> Array<T>::iterator() const {
    return ArrayIterator<T> (*this);
}

template<class T>
MutableIterator<T> Array<T>::mutableIterator() const {
    return ArrayMutableIterator<T> (*this);
}

template<class T>
const T& Array<T>::operator[](std::size_t idx) const throw (Exception) {
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
