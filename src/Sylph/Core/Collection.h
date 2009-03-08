/* 
 * File:   Collection.h
 * Author: frank
 *
 * Created on 19 december 2008, 14:29
 */

#ifndef _COLLECTION_H
#define	_COLLECTION_H

#include "Object.h"
#include "Iterable.h"
#include "Hashable.h"

SYLPH_START_NAMESPACE(Core)
SYLPH_PUBLIC
template<typename T>
interface Collection : public virtual Iterable<T>, public virtual Hashable {
    public:

    Collection() {
    }

    virtual ~Collection() {
    }

    virtual bool add(const T & t) = 0;
    virtual bool addAll(Collection<T> & c) = 0;
    virtual void clear() = 0;
    virtual bool contains(T & t) const = 0;
    virtual bool containsAll(Collection<T> & c) const = 0;
    virtual bool operator ==(Collection<T> & c) const = 0;

    virtual bool operator !=(Collection<T> & c) const {
        return !(*this == c);
    }
    virtual int hashCode() const = 0;
    virtual bool empty() const = 0;
    virtual bool remove(T & t) = 0;
    virtual bool removeAll(Collection<T> & c) = 0;
    virtual bool retainAll(Collection<T> & c) = 0;
    virtual std::size_t size() const = 0;
    virtual const Array<T> toArray() const = 0;

    virtual Iterator<T> iterator() const = 0;
    virtual MutableIterator<T> mutableIterator() = 0;

    operator Array<T>() const { return toArray(); }

};
SYLPH_END_NAMESPACE(Core)

#endif	/* _COLLECTION_H */

