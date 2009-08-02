/*
 * LibSylph Class Library
 * Copyright (C) 2009 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LibSylph Pulbic License as published
 * by the LibSylph Developers; either version 1.0 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LibSylph
 * Public License for more details.
 *
 * You should have received a copy of the LibSylph Public License
 * along with this Library, if not, contact the LibSylph Developers.
 * 
 * Created on 6 december 2008, 17:16
 */

#ifndef ITERATOR_H_
#define	ITERATOR_H_

#include "Object.h"
#include "Exception.h"
#include "Iterable.h"
#include <iterator>
//#include "Foreach.h" -- this line is at the bottom of the file ;)

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

enum itr_begin_t {
    itr_begin
};

enum itr_end_t {
    itr_end
};


#define S_FORWARD_ITERATOR(self,type,object) \
    typedef ForwardIterator<type,object> super; \
    self() : ::Sylph::ForwardIterator<type,object>(){ \
        construct(false,NULL); \
    } \
    self(itr_begin_t t, object* obj) : \
      ::Sylph::ForwardIterator<type,object>(t,obj) { \
        construct(true, obj); \
    } \
    self(itr_end_t t, object* obj) : \
      ::Sylph::ForwardIterator<type,object>(t,obj) { \
        construct(false, obj); \
    } \
    self(self& other) : \
     ::Sylph::ForwardIterator<type,object>(other) \
    { copyFrom(other); }

#define S_BIDIRECTIONAL_ITERATOR(self,type,object) \
    typedef BidirectionalIterator<type,object> super; \
    self() : ::Sylph::BidirectionalIterator<type,object>(){ \
        construct(false,NULL); \
    } \
    self(itr_begin_t t, object* obj) : \
      ::Sylph::BidirectionalIterator<type,object>(t,obj) { \
        construct(true, obj); \
    } \
    self(itr_end_t t, object* obj) : \
      ::Sylph::BidirectionalIterator<type,object>(t,obj) { \
        construct(false, obj); \
    } \
    self(self& other) : \
     ::Sylph::BidirectionalIterator<type,object>(other) \
    { copyFrom(other); }

#define S_RANDOM_ACCESS_ITERATOR(self,type,object) \
    typedef RandomAccessIterator<type,object> super; \
    self() : ::Sylph::RandomAccessIterator<type,object>(){ \
        construct(false,NULL); \
    } \
    self(itr_begin_t t, object* obj) : \
      ::Sylph::RandomAccessIterator<type,object>(t,obj) { \
        construct(true, obj); \
    } \
    self(itr_end_t t, object* obj) : \
      ::Sylph::RandomAccessIterator<type,object>(t,obj) { \
        construct(false, obj); \
    } \
    self(self& other) : \
     ::Sylph::RandomAccessIterator<type,object>(other) \
    { copyFrom(other); }

S_CREATE_EXCEPTION(IteratorException);

/**
 * Facade used to simplify usage of forward iterators. This class provides
 * several methods to override, which will be used to make a correct
 * implementation of a forward iterator.<p>
 * Note that this class already correctly implements the difference between
 * a const_iterator and a normal iterator, i.e. a const ForwardIterator conforms
 * as a const_iterator, and a non-const ForwardIterator conforms as a non-const
 * iterator. Therefore, when implementing this class, make sure that you
 * flag any fields that can be changed (such as indices or pointers to the
 * current item) as <code>mutable</code>. <p>
 * In order for your own types to be correctly identified as a ForwardIterator,
 * please use the <code>S_FORWARD_ITERATOR(</code><i>iterator-name, type-name,
 * object-to-iterate-over</i><code>)</code>
 */
template<class T, class I>
class ForwardIterator : public Object {
public:
    typedef std::forward_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
    typedef ForwardIterator<T, I> self_type;
public:
    // Implementation of the required functions in terms of the overridable
    // functions

    ForwardIterator() : _end_reached_(0) {
    }

    ForwardIterator(itr_begin_t, I* obj) : _end_reached_(0) {
    }

    ForwardIterator(itr_end_t, I* obj) : _end_reached_(2) {
    }

    ForwardIterator(ForwardIterator<T, I>& other) :
    _end_reached_(other._end_reached_) {
        copyFrom(other);
    }

    virtual ~ForwardIterator() {
    }

    reference operator*() {
        if (_end_reached_ == 2) sthrow(IteratorException,
                "Tried to derefrence an beyond-end iterator");
        return current();
    }

    const reference operator*() const {
        if (_end_reached_ == 2) sthrow(IteratorException,
                "Tried to derefrence an beyond-end iterator");
        return current();
    }

    reference operator->() {
        if (_end_reached_ == 2) sthrow(IteratorException,
                "Tried to derefrence an beyond-end iterator");
        return current();
    }

    const reference operator->() const {
        if (_end_reached_ == 2) sthrow(IteratorException,
                "Tried to derefrence an beyond-end iterator");
        return current();
    }

    const ForwardIterator<T, I> & operator++() const {
        if (_end_reached_ == 2) sthrow(IteratorException, "End of iterator");
        else if (_end_reached_ == 1) {
            _end_reached_ = 2;
            return *this;
        } else {
            next();
            if (!hasNext()) _end_reached_ = 1;
            return *this;
        }
    }

    ForwardIterator<T, I> & operator++() {
        if (_end_reached_ == 2) sthrow(IteratorException, "End of iterator");
        else if (_end_reached_ == 1) {
            _end_reached_ = 2;
            return *this;
        } else {
            next();
            if (!hasNext()) _end_reached_ = 1;
            return *this;
        }
    }

    const ForwardIterator<T, I> operator++(int) const {
        ForwardIterator<T, I> toReturn(*this);
        if (_end_reached_ == 2) sthrow(IteratorException, "End of iterator");
        else if (_end_reached_ == 1) {
            _end_reached_ = 2;
            return toReturn;
        } else {
            next();
            if (!hasNext()) _end_reached_ = 1;
            return *toReturn;
        }
    }

    ForwardIterator<T, I> operator++(int) {
        ForwardIterator<T, I> toReturn(*this);
        if (_end_reached_ == 2) sthrow(IteratorException, "End of iterator");
        else if (_end_reached_ == 1) {
            _end_reached_ = 2;
            return toReturn;
        } else {
            next();
            if (!hasNext()) _end_reached_ = 1;
            return *toReturn;
        }
    }

    ForwardIterator<T, I> & operator=
            (const ForwardIterator<T, I>& other) {
        copyFrom(other);
        _end_reached_ = other._end_reached_;
        return *this;
    }

    virtual bool operator==(const ForwardIterator<T, I>& other) const {
        return (_end_reached_ == other._end_reached_);
    }

    bool operator!=(const ForwardIterator<T, I>& other) const {
        return !(*this == other);
    }

public:
    // Overridable functions
    /**
     * <b>OVERRIDE THIS METHOD</b> Create the iterator object. A boolean is
     * passed to tell if this iterator pointed to the beginning or the end of
     * the class (such that internal data pointers can be properly set up), and
     * the object this iterator will be iterating over.
     * @param begin <i>true</i> if this iterator points to the begin of the
     * collection, <i>false</i> if it points to the end.
     * @param obj The object this iterator will iterate over.
     */
    virtual void construct(bool begin, I* obj) const = 0;
    /**
     * <b>OVERRIDE THIS METHOD</b> Returns a reference to the object the iterator
     * is currently pointing at. Note that no beyond-the-end checking needs
     * to be done, this is all done automagically for you.
     * @return The object this iterator is currently pointing at.
     */
    virtual reference current() const = 0;
    /**
     * <b>OVERRIDE THIS METHOD</b> Sets the iterator one place forward. Note
     * that no beyond-the-end checking needs to be done, this is all done
     * automagically for you.
     */
    virtual void next() const = 0;
    /**
     * <b>OVERRIDE THIS METHOD</b> Tells wheter there are any objects left
     * in the collection. This method should not take the past-the-end item into
     * account.
     * @return <i>true</i> true if there are any next items, <i>false<i> if
     * there are no more items left.
     */
    virtual bool hasNext() const = 0;
    /**
     * <b>OVERRIDE THIS METHOD</b> Copies this iterator's fields from an other
     * ForwardIterator over the same type of collection, such that
     * <code>this->equals(other)</code> is <i>true</i>
     * @param other An other Iterator to copy the current one from.
     */
    virtual void copyFrom(ForwardIterator<T, I>& other) const = 0;
    /**
     * Do not use or modify!
     */
    mutable unsigned char _end_reached_;
};

template<class T, class I>
class BidirectionalIterator : public ForwardIterator<T, I> {
public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef ForwardIterator<T, I> super;
    typedef BidirectionalIterator<T, I> self_type;
public:

    BidirectionalIterator() : ForwardIterator<T, I>() {
    }

    BidirectionalIterator(itr_begin_t, I* obj) :
            ForwardIterator<T,I>() {
    }

    BidirectionalIterator(itr_end_t, I* obj) :
            ForwardIterator<T,I>() {
    }

    BidirectionalIterator(BidirectionalIterator<T, I>& other) :
            ForwardIterator<T,I>() {
        copyFrom(other);
    }

    BidirectionalIterator<T, I> & operator--() {
        if (ForwardIterator<T,I>::_end_reached_ == 2) {
            ForwardIterator<T,I>::_end_reached_ = 1;
            return *this;
        } else if (!hasPrevious()) {
            sthrow(IteratorException, "Begin of iterator");
        } else {
            if (ForwardIterator<T,I>::_end_reached_ == 1)
                ForwardIterator<T,I>::_end_reached_ = 0;
            previous();
            return *this;
        }
    }

    const BidirectionalIterator<T, I> & operator--() const {
        if (ForwardIterator<T,I>::_end_reached_ == 2) {
            ForwardIterator<T,I>::_end_reached_ = 1;
            return *this;
        } else if (!hasPrevious()) {
            sthrow(IteratorException, "Begin of iterator");
        } else {
            if (ForwardIterator<T,I>::_end_reached_ == 1)
                ForwardIterator<T,I>::_end_reached_ = 0;
            previous();
            return *this;
        }
    }

    BidirectionalIterator<T, I> operator--(int) {
        BidirectionalIterator toReturn(*this);
        if (ForwardIterator<T,I>::_end_reached_ == 2) {
            ForwardIterator<T,I>::_end_reached_ = 1;
            return *toReturn;
        } else if (!hasPrevious()) {
            sthrow(IteratorException, "Begin of iterator");
        } else {
            if (ForwardIterator<T,I>::_end_reached_ == 1)
                ForwardIterator<T,I>::_end_reached_ = 0;
            previous();
            return *toReturn;
        }
    }

    const BidirectionalIterator<T, I> operator--(int) const {
        BidirectionalIterator toReturn(*this);
        if (ForwardIterator<T,I>::_end_reached_ == 2) {
            ForwardIterator<T,I>::_end_reached_ = 1;
            return *toReturn;
        } else if (!hasPrevious()) {
            sthrow(IteratorException, "Begin of iterator");
        } else {
            if (ForwardIterator<T,I>::_end_reached_ == 1)
                ForwardIterator<T,I>::_end_reached_ = 0;
            previous();
            return *toReturn;
        }
    }

    virtual bool operator==(const BidirectionalIterator<T, I>& other) const {
        return ((ForwardIterator<T,I>::_end_reached_ == other._end_reached_) ||
                (hasPrevious() == other.hasPrevious()));
    }
public:
    virtual bool hasPrevious() const = 0;
    virtual void previous() const = 0;
};

template<class T, class I>
class RandomAccessIterator : public BidirectionalIterator<T, I> {
public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef BidirectionalIterator<T, I> super;
    typedef RandomAccessIterator<T, I> self_type;
public:

    RandomAccessIterator() : super() {
    }

    RandomAccessIterator(itr_begin_t, I* obj) : super() {
    }

    RandomAccessIterator(itr_end_t, I* obj) : super() {
    }

    RandomAccessIterator(BidirectionalIterator<T, I>& other) :
            super() {
        copyFrom(other);
    }

    RandomAccessIterator<T, I> & operator+=(unsigned int i) {
        ptrdiff_t diff = i;
        if (i >= 0) while (diff--) ++(*this);
        else while (diff++) --(*this);
        return *this;
    }

    const RandomAccessIterator<T, I> & operator+=
            (unsigned int i) const {
        ptrdiff_t diff = i;
        if (i >= 0) while (diff--) ++(*this);
        else while (diff++) --(*this);
        return *this;
    }

    RandomAccessIterator<T, I> & operator-=(unsigned int i) {
        return *this += -i;
    }

    const RandomAccessIterator<T, I> & operator-=
            (unsigned int i) const {
        return *this += -i;
    }

    const RandomAccessIterator<T, I> operator+
            (unsigned int i) const {
        RandomAccessIterator<T, I> toReturn(*this);
        return toReturn += i;
    }

    RandomAccessIterator<T, I> operator-(unsigned int i) {
        return *this + -i;
    }

    ptrdiff_t operator-(const RandomAccessIterator<T, I>&
            other) const {
        if (*this > other) return this->currentIndex() - other.currentIndex();
        else return other.currentIndex() - this->currentIndex();
    }

    const typename super::reference operator[](unsigned int offset) const {
        return *(*this +offset);
    }

    typename super::reference operator[](unsigned int offset) {
        return *(*this +offset);
    }

    bool operator>(const RandomAccessIterator<T, I>&
            other) const {
        return this->currentIndex() > other.currentIndex();
    }

    bool operator<(const RandomAccessIterator<T, I>&
            other) const {
        return this->currentIndex() < other.currentIndex();
    }

    bool operator>=(const RandomAccessIterator<T, I>&
            other) const {
        return this->currentIndex() >= other.currentIndex();
    }

    bool operator<=(const RandomAccessIterator<T, I>&
            other) const {
        return this->currentIndex() <= other.currentIndex();
    }

public:
    virtual idx_t currentIndex() = 0;
    virtual size_t length() = 0;
};

template<class T, class I>
RandomAccessIterator<T, I> operator+
    (unsigned int i, const RandomAccessIterator<T, I> itr) {
    return itr+i;
}

/**
 * SylphIterator provides a easier-to-use wrapper around STL iterators. The
 * interface of a SylphIterator is similar to a Java-style iterator, but it is
 * backed by a STL iterator and can therefore be used for any class supporitng
 * STL iterators. <p>
 */
template<class Iter>
class SylphIterator : public virtual Object {
public:

    /**
     * Creates a new Iterator from an STL-iterator. An Iterator can either be
     * constructed explicitly with this constructor, in which case the correct
     * type of Iterator for the particular collection needs to be known, or
     * through Iterable::iterator() or Iterable::mutableIterator() .
     * @param it The iterable to iterate over.
     */
    inline SylphIterator(Iter & it) : itr(it) {
    }

    /**
     * Destructor. This destructor does nothing.
     */
    inline virtual ~SylphIterator() {
    }

    /**
     * Checks if this iterator has any more entries in forward direction.
     * @return <i>true</i> if there are more entries, <i>false</i> otherwise.
     */
    virtual bool hasNext() const {
        return itr.hasNext();
    }
    /**
     * Returns the next entry in the forward direction and moves the iterator
     * one place forward.
     * @throw Exception if there are no more entries.
     * @return The next entry
     */
    virtual const typename Iter::reference next() const {
        typename Iter::reference toReturn = *itr;
        ++itr;
        return toReturn;
    }
    /**
     * Checks if this iterator has any more entries in backward direction.
     * @return <i>true</i> if there are more entries, <i>false</i> otherwise.
     * @note This requires that the backing iterator is a bidirectional
     * iterator.
     */
    virtual bool hasPrevious() const {
        return itr.hasPrevious();
    }
    /**
     * Returns the next entry in the backward direction and moves the iterator
     * one place backward.
     * @throw Exception if there are no more entries.
     * @return The previous entry
     * @note This requires that the backing iterator is a bidirectional
     * iterator.
     */
    virtual const typename Iter::reference previous() const {
        --itr;
        return *itr;
    }

    /**
     * Moves the Iterator to the place "before" the first item, that is,
     * it gives the pointer in the iterator such a value that hasPrevious
     * returns false.
     * @note This requires that the backing iterator is a bidirectional
     * iterator.
     */
    virtual void front() const {
        while(itr.hasPrevious()) --itr;
    }

    /**
     * Moves the Iterator to the place "after" the last item, that is,
     * it gives the pointer in the iterator such a value that hasNext
     * returns false.
     * <p> This method is useful for backward iterating, i.e.
     * <pre>Iterator it = coll.getIterator(); // normal 'forward' iterator
     * it.back(); // ready for backward iteration </pre>
     */
    virtual void back() const {
        while(itr.hasNext()) ++itr;
    }

    /**
     * Returns the next index of the Iterable in the forward direction.
     * @throw Exception if there are no more entries.
     * @return The next index in the Iterable
     * @note This method requires the backing iterator to be a random-access
     * iterator.
     */
    virtual std::idx_t nextIndex() const {
        return itr.currentIndex();
    }

    /**
     * Returns the next index of the Iterable in the backward direction.
     * @throw Exception if there are no more entries.
     * @return The previous index in the Iterable
     * @note This method requires the backing iterator to be a random-access
     * iterator.
     */
    virtual std::idx_t previousIndex() const {
        return itr.currentIndex() - 1;
    }

    /**
     * Replaces the last item returned by next() or previous() with the given
     * item
     * @param t The item to replace the last returned item with.
     */
    virtual void set(typename Iter::reference t) {
        *itr = t;
    }

    /**
     * Synonymous for next()
     */
    const typename Iter::reference operator++() const {
        return next();
    }

    /**
     * Synonymous for previous()
     */
    const typename Iter::reference operator--() const {
        return previous();
    }

    /**
     * Synoynmous for next().
     * @note No copy of this iterator is made.
     */
    const typename Iter::reference operator++(int) const {
        return next();
    }

    /**
     * Synonymous for previous()
     * @note No copy is of this iterator is made.
     */
    const typename Iter::reference operator--(int) const {
        return previous();
    }
private:
    Iter itr;
};

template<class Collection>
const SylphIterator<typename Collection::const_iterator> SylphItr(
        const Collection& col) {
    return SylphIterator<typename Collection::const_iterator>(col.begin());
}

template<class Collection>
SylphIterator<typename Collection::iterator> SylphMitr(Collection & col) {
    return SylphIterator<typename Collection::iterator>(col.begin());
}


SYLPH_END_NAMESPACE

// Previously defined here, now defined elsewhere
#include "Foreach.h"

#endif	/* ITERATOR_H_ */

