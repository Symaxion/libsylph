/* 
 * File:   vector.cpp
 * Author: frank
 * 
 * Created on 6 december 2008, 12:07
 */

#include "Vector.h"
#include "Util.h"
#include "Equals.h"
#include "VectorIterator.h"

SYLPH_BEGIN_NAMESPACE

Vector::Vector(std::size_t initialCount, std::size_t increase) {
    elements = new Array<T> (initialCount);
    capacity = initialCount;
    capacityIncrease = increase;
    elementCount = 0;
}

Vector::Vector(const std::vector<T> & orig) {
    // TODO.
    sthrow(UnsupportedOperationException, "sorry, can't initalize from stl vector for now...")
}

Vector::Vector(const Array<T> & orig) {
    elements = new Array<T > (orig.length * 2);
    arraycopy(orig, 0, elements, 0, orig.length);
    elementCount = orig.length;
    capacityIncrease = 0;
    capacity = orig.length * 2;
}

Vector::Vector(const Vector<T> & orig) {
    elements = new Array<T > (orig.elements->length);
    capacity = orig.capacity;
    capacityIncrease = orig.capacityIncrease;
    elementCount = orig.elementCount;
    arraycopy(orig.elements, 0, elements, 0, orig.elements->length);
}

Vector::Vector(const std::initializer_list<T> & orig) {
    elements = new Array<T > (orig.size()*2);
    capacity = elements->length;
    capacityIncrease = 0;
    elementCount = 0;
    for (T * t = orig.begin(); t < orig.end(); t++) {
        this->push(&t);
    }
}

Vector::~Vector() {
    delete elements;
}

void Vector::push(const T & t) {
    add(t);
}

T Vector::pop() {
    T toReturn = *elements[elementCount - 1];
    elementCount--;
    return toReturn;
}

T & Vector::get(std::size_t idx) {
    if (idx >= elementCount) sthrow(ArrayException, "Vector out of bounds");
    else {
        return *elements[idx];
    }
}

const T & Vector::get(std::size_t idx) const {
    if (idx >= elementCount) sthrow(ArrayException, "Vector out of bounds");
    else {
        return *elements[idx];
    }
}

void Vector::set(std::size_t idx, const T & t) {
    if (idx >= elementCount) sthrow(ArrayException, "Vector out of bounds");
    else {
        *elements[idx] = t;
    }
}

void Vector::trim() {
    Array<T> * oldElements = elements;
    elements = new Array<T > (elementCount);
    arraycopy(*oldElements, 0, *elements, 0, elementCount);
    delete oldElements;
}

bool Vector::add(const T & t) {
    ensureCapacity(elementCount + 1);
    *elements[elementCount] = t;
    elementCount++;
    return true;
}

bool Vector::addAll(Collection<T> & c) {

    sforeach(T & t, c) {
        this->add(t);
    }
    return true;
}

void Vector::clear() {
    Array<T> * oldElements = elements;
    elements = new Array<T > (oldElements->length);
    delete oldElements;
    elementCount = 0;
}

bool Vector::contains(T & t) const {
    return indexOf(t) != -1;
}

bool Vector::containsAll(Collection<T> & c) const {
    std::size_t amount = 0;

    sforeach(T t, c) {
        if (this->contains(t)) amount++;
    }
    return amount == c.size();
}

bool Vector::operator==(Collection<T> & c) const {
    Vector * v = dynamic_cast<Vector> (c);
    if (v == NULL) return false;
    else if (this->size() != c.size()) return false;
    else {
        for (std::size_t x = 0; x < c.size(); x++) {
            if (*this[x] != c[x]) return false;
        }
        return true;
    }
}

int Vector::hashCode() const {
    // TODO
    return 0;
}

bool Vector::empty() const {
    return elementCount == 0;
}

void Vector::remove(T & t) {
    return removeAt(indexOf(t));
}
void Vector::removeAt(std::size_t idx) {
    if(idx > size()) sthrow(ArrayException,"Vector out of bounds");
    elementCount--;
    if (idx < elementCount)
      arraycopy(*elements, idx + 1, *elements, idx,
                       elementCount - idx);
}

bool Vector::removeAll(Collection<T> & c) {
    std::size_t i;
    std::size_t j;
    for (i = 0; i < elementCount; i++) {
        if (c.contains(*elements[i])) break;
    }
    if (i == elementCount) return false;

    for (j = i++; i < elementCount; i++) {
        if (!c.contains(*elements[i])) *elements[j++] = *elements[i];
    }
    elementCount -= i - j;
    return true;
}

bool Vector::retainAll(Collection<T> & c) {
    std::size_t i;
    std::size_t j;
    for (i = 0; i < elementCount; i++) {
        if (!c.contains(*elements[i])) break;
    }
    if (i == elementCount) return false;

    for (j = i++; i < elementCount; i++) {
        if (c.contains(*elements[i])) *elements[j++] = *elements[i];
    }
    elementCount -= i - j;
    return true;
}

std::size_t Vector::size() const {
    return elementCount;
}

const Array<T> Vector::toArray() const {
    return elements;
}

Iterator<T> Vector::iterator() const {
    return VectorIterator<T>(*this);
}

MutableIterator<T> Vector::mutableIterator() {
    return VectorMutableIterator<T>(*this);
}

void Vector::ensureCapacity(std::size_t capacity) {
    if (capacity <= this->capacity) return;
    std::size_t newsize;
    if (capacityIncrease == 0) newsize = capacity * 2;
    else newsize = capacity + capacityIncrease;
    Array<T> * oldElements = elements;
    elements = new Array<T > (newsize);
    arraycopy(*oldElements, 0, *elements, 0, oldElements->length);
    capacity = newsize;
    delete oldElements;
}

T & Vector::front() {
    return *elements[0];
}

T & Vector::back() {
    return *elements[elementCount - 1];
}

int Vector::indexOf(T & t, std::size_t idx) {
    for (std::size_t i = idx; i < size(); i++) {
        if (Equals(*this[i],t)) {
            return i;
        }
    }
    return -1;
}

int Vector::lastIndexOf(T & t, std::size_t idx) {
    if(idx > size()) sthrow(ArrayException,"Vector out of bounds");
    for (std::size_t i = idx; i >= 0; i--) {
        if (Equals(*this[i],t)) {
            return i;
        }
    }
    return -1;
}

Vector & Vector::operator=(const Vector & rhs) const {

}
SYLPH_END_NAMESPACE