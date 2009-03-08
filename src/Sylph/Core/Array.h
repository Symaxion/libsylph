/* 
 * File:   Array.h
 * Author: frank
 *
 * Created on 8 februari 2009, 14:18
 */

#ifndef _ARRAY_H
#define	_ARRAY_H

#include "Iterable.h"
#include "Comparable.h"
#include "Exception.h"
#include <initializer_list>

SYLPH_START_NAMESPACE(Core)

SYLPH_PUBLIC
template <class T, std::size_t N>
class Array : public virtual Iterable<T> {

    friend bool operator==(const Array<T>& lhs, const Array<T>& rhs);
    friend bool operator<(const Array<T>& lhs, const Array<T>& rhs);

public:
    typedef T Type;
    const int length;

private:
    T carray[];

public:
    explicit Array(std::size_t len);
    Array(std::initializer_list<T> il);
    Array(T & array[]);
    Array(Array<T> & ar);
    virtual ~Array();

    Iterator<T> iterator() const;
    MutableIterator<T> mutableIterator() const;

    T * carray();
    const T * carray() const;

    template<class V> Array & operator=(const Array<V, N> & other);

    T & operator[](std::size_t idx) throw (Exception);
    const T & operator[](std::size_t idx) const throw (Exception);

};
template<class T>
inline bool operator==(const Array<T>& lhs, const Array<T>& rhs);
template<class T>
inline bool operator<(const Array<T>& lhs, const Array<T>& rhs);

SYLPH_END_NAMESPACE(Core)

#endif	/* _ARRAY_H */

