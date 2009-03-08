/* 
 * File:   Iterator.h
 * Author: frank
 *
 * Created on 6 december 2008, 17:16
 */

#ifndef _ITERATOR_H
#define	_ITERATOR_H

#include "Object.h"
#include "Exception.h"

SYLPH_START_NAMESPACE(Core)
SYLPH_PUBLIC
class Iterable;

template<class T>
class Iterator : public Object {
public:

    Iterator(Iterable it) {}

    virtual ~Iterator() {}
    virtual bool hasNext() const = 0;
    virtual const T & next() const = 0;
    virtual bool hasPrevious() const = 0;
    virtual const T & previous() const = 0;
    virtual std::size_t nextIndex() const = 0;
    virtual std::size_t previousIndex() const = 0;

    const T& operator++() const { next(); }
    const T& operator--() const { previous(); }
};

template<class T>
class MutableIterator : public virtual Iterator<T> {
public:

    MutableIterator(Iterable it) {}

    virtual ~Iterator() {}
    virtual bool hasNext() const = 0;
    virtual T & next() const = 0;
    virtual bool hasPrevious() const = 0;
    virtual T & previous() const = 0;
    virtual std::size_t nextIndex() const = 0;
    virtual std::size_t previousIndex() const = 0;
    virtual void set(T & t) throw(Exception) = 0;
    virtual void insert(T & t) throw(Exception) = 0;
    virtual void remove() throw(Exception) = 0;
};
SYLPH_END_NAMESPACE(Core)


// note : there is a reason why the name is so strange -- do not use directly!
template<class T>
class s_foreach_container_fjAk8tb1 {
    public:
    inline s_foreach_container_fjAk8tb1(const T& t): c(t), brk(0), i(c){};
    const T c;
    int brk;
    Sylph::Core::Iterator<T> i;
    inline bool condition() const { return (!brk++ && i.hasNext()); }

};
#define sforeach(variable,container)\
for (s_foreach_container_fjAk8tb1 &_container_ = \
         s_foreach_container_fjAk8tb1(container); \
         _container_.condition(); )               \
        for (variable = _container_.i++; _container_.brk; --_container_.brk)

#ifndef foreach
#define foreach sforeach
#endif

#endif	/* _ITERATOR_H */

