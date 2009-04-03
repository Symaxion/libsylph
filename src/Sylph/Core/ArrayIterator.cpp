#include "ArrayIterator.h"
#include "Array.h"

SYLPH_BEGIN_NAMESPACE

template<class T>
bool ArrayIterator<T>::hasNext() {
    return idx < ar->length();
}

template<class T>
const T & ArrayIterator<T>::next() {
    return last = *ar[idx++];
}

template<class T>
bool ArrayIterator<T>::hasPrevious() {
    return idx > 0;
}

template<class T>
const T & ArrayIterator<T>::previous() {
    return last = *ar[--idx];
}

template<class T>
std::size_t ArrayIterator<T>::nextIndex() {
    return idx;
}

template<class T>
std::size_t ArrayIterator<T>::previousIndex() {
    return idx-1;
}

template<class T>
void ArrayMutableIterator<T>::set(T & t) throw(Exception) {
    *ArrayIterator<T>::last = t;
}

template<class T>
void ArrayMutableIterator<T>::insert(T & t) throw(Exception) {
    sthrow(UnsupportedOperationException,"insert() not supported on arrays");
}

template<class T>
void ArrayMutableIterator<T>::remove() throw(Exception) {
    sthrow(UnsupportedOperationException,"remove() not supported on arrays");
}

SYLPH_END_NAMESPACE
