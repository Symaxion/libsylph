/*
 * LibSylph Class Library
 * Copyright (C) 2012 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not
 *   claim that you wrote the original software. If you use this software
 *   in a product, an acknowledgment in the product documentation would be
 *   appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not be
 *   misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any source
 *   distribution.
 * 
 * Created on 6 december 2008, 17:16
 */

#ifndef SYLPH_CORE_ITERATOR_H_
#define	SYLPH_CORE_ITERATOR_H_

#include "Object.h"
#include "Exception.h"
#include "Iterable.h"
#include <iterator>
#include <type_traits>
//#include "Foreach.h" -- this line is at the bottom of the file ;)

SYLPH_BEGIN_NAMESPACE

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
    typedef typename remove_const<T>::type* pointer;
    typedef typename add_const<T>::type* const_pointer;
    typedef typename remove_const<T>::type& reference;
    typedef typename add_const<T>::type& const_reference;
    typedef ForwardIterator<T, I> self_type;
public:
    // Implementation of the required functions in terms of the overridable
    // functions

    ForwardIterator(bool begin = false) : _end_reached_(!begin) {
    }

    ForwardIterator(const ForwardIterator<T, I>& other) :
    _end_reached_(other._end_reached_) {
    }

    virtual ~ForwardIterator() {
    }

    value_type& operator*() {
        if (_end_reached_) sthrow(IteratorException,
                "Tried to dereference an beyond-end iterator");
        return static_cast<I*>(this)->current();
    }

    const_reference operator*() const {
        if (_end_reached_) sthrow(IteratorException,
                "Tried to dereference an beyond-end iterator");
        return static_cast<I*>(this)->current();
    }

    value_type* operator->() {
        if (_end_reached_) sthrow(IteratorException,
                "Tried to dereference an beyond-end iterator");
        return &static_cast<I*>(this)->current();
    }

    const_pointer operator->() const {
        if (_end_reached_) sthrow(IteratorException,
                "Tried to dereference an beyond-end iterator");
        return &static_cast<I*>(this)->current();
    }

    const I & operator++() const {
        if (_end_reached_) sthrow(IteratorException, "End of iterator");
        else if (!hasNext()) {
            _end_reached_ = true;
            return *static_cast<const I*> (this);
        } else {
            next();
            return *static_cast<const I*> (this);
        }
    }

    I & operator++() {
        if (_end_reached_) sthrow(IteratorException, "End of iterator");
        else if (!hasNext()) {
            _end_reached_ = true;
            return *static_cast<I*> (this);
        } else {
            next();
            return *static_cast<I*> (this);
        }
    }

    const I operator++(int) const {
        I toReturn(*static_cast<const I*> (this));
        if (_end_reached_) sthrow(IteratorException, "End of iterator");
        else if (!hasNext()) {
            _end_reached_ = true;
            return toReturn;
        } else {
            next();
            return toReturn;
        }
    }

    I operator++(int) {
        I toReturn(*static_cast<I*> (this));
        if (_end_reached_) sthrow(IteratorException, "End of iterator");
        else if (!hasNext()) {
            _end_reached_ = true;
            return toReturn;
        } else {
            next();
            return toReturn;
        }
    }

    virtual bool operator==(const I& other) const {
        return (_end_reached_ == other._end_reached_)
                && static_cast<const I*>(this)->equals(other);
    }

    bool operator!=(const I& other) const {
        return !(*this == other);
    }
    void construct(bool begin, void* obj) {
        construct(begin,obj);
    }

public:
    // Overridable functions
    /**
     * <b>OVERRIDE THIS METHOD</b> Returns a reference to the object the iterator
     * is currently pointing at. Note that no beyond-the-end checking needs
     * to be done, this is all done automagically for you.
     * @return The object this iterator is currently pointing at.
     */
    //virtual reference current() = 0;
    /**
     * <b>OVERRIDE THIS METHOD</b> Returns a reference to the object the iterator
     * is currently pointing at. Note that no beyond-the-end checking needs
     * to be done, this is all done automagically for you.
     * @return The object this iterator is currently pointing at.
     */
    //virtual const_reference current() const = 0;
    /**
     * <b>OVERRIDE THIS METHOD</b> Sets the iterator one place forward. Note
     * that no beyond-the-end checking needs to be done, this is all done
     * automagically for you.
     */
    virtual void next() = 0;
    /**
     * <b>OVERRIDE THIS METHOD</b> Tells wheter there are any objects left
     * in the collection. This method should not take the past-the-end item into
     * account.
     * @return <i>true</i> true if there are any next items, <i>false</i> if
     * there are no more items left.
     */
    virtual bool hasNext() const = 0;
    /**
     * <b>OVERRIDE THIS METHOD</b> Tells wheter this Iterator is equal to any
     * other Iterator over the same type of collection.
     * @param other An other ForwardIterator to compare this one against.
     * @return <i>true</i> iff the two iterators are completely equal (i.e.
     * they iteratate over the same collection and currently point to the same
     * object), false otherwise.
     */
    //virtual bool equals(const I& other) const = 0;
    /**
     * Do not use or modify!
     */
    mutable bool _end_reached_;
};

/**
 * @todo Write documentation!
 */
template<class T, class I>
class BidirectionalIterator : public ForwardIterator<T, I> {
public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef ForwardIterator<T, I> super;
    typedef BidirectionalIterator<T, I> self_type;
public:

    BidirectionalIterator(bool begin = false) : super(begin) {
    }

    BidirectionalIterator(const BidirectionalIterator<T, I>& other) :
    ForwardIterator<T, I>(other) {
    }

    I & operator--() {
        if (super::_end_reached_) {
            super::_end_reached_ = false;
            return *static_cast<I*> (this);
        } else if (!hasPrevious()) {
            sthrow(IteratorException, "Begin of iterator");
        } else {
            previous();
            return *static_cast<I*> (this);
        }
    }

    const I & operator--() const {
        if (super::_end_reached_) {
            super::_end_reached_ = false;
            return *static_cast<const I*> (this);
        } else if (!hasPrevious()) {
            sthrow(IteratorException, "Begin of iterator");
        } else {
            previous();
            return *static_cast<const I*> (this);
        }
    }

    I operator--(int) {
        I toReturn(*static_cast<I*> (this));
        if (super::_end_reached_) {
            super::_end_reached_ = false;
            return toReturn;
        } else if (!hasPrevious()) {
            sthrow(IteratorException, "Begin of iterator");
        } else {
            previous();
            return toReturn;
        }
    }

    const I operator--(int) const {
        I toReturn(*static_cast<const I*> (this));
        if (super::_end_reached_) {
            super::_end_reached_ = false;
            return toReturn;
        } else if (!hasPrevious()) {
            sthrow(IteratorException, "Begin of iterator");
        } else {
            previous();
            return toReturn;
        }
    }

    virtual bool operator==(const I& other) const {
        return ((super::_end_reached_ == other._end_reached_) ||
                (hasPrevious() == other.hasPrevious()))
                && super::operator==(other);
    }
public:
    virtual bool hasPrevious() const = 0;
    virtual void previous() = 0;
};

/**
 * @todo Write documentation!
 */
template<class T, class I>
class RandomAccessIterator : public BidirectionalIterator<T, I> {
public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef BidirectionalIterator<T, I> super;
    typedef RandomAccessIterator<T, I> self_type;
public:

    RandomAccessIterator(bool begin = false) : super(begin) {}

    RandomAccessIterator(const self_type& other) :
		super(other) {
    }

    I & operator+=(int i) {
        ptrdiff_t diff = i;
        if (i >= 0) while (diff--) ++(*this);
        else while (diff++) --(*this);
        return *static_cast<I*>(this);
    }

    const I & operator+=(int i) const {
        ptrdiff_t diff = i;
        if (i >= 0) while (diff--) ++(*this);
        else while (diff++) --(*this);
        return *static_cast<const I*>(this);
    }

    I & operator-=(unsigned int i) {
        return *static_cast<I*>(&(*this += -i));
    }

    const I & operator-=(unsigned int i) const {
        return &*static_cast<const I*>(&(*this += -i));
    }

    const I operator+(unsigned int i) const {
        I toReturn(*static_cast<const I*>(this));
        return toReturn += i;
    }

    I operator-(unsigned int i) {
        return *static_cast<I*>(&(*this + -i));
    }

    ptrdiff_t operator-(const I& other) const {
        if (*this > other) return this->currentIndex() - other.currentIndex();
        else return other.currentIndex() - this->currentIndex();
    }

    const typename super::reference operator[](unsigned int offset) const {
        return *(*this +offset);
    }

    typename super::reference operator[](unsigned int offset) {
        return *(*this +offset);
    }

    bool operator>(const I& other) const {
        return this->currentIndex() > other.currentIndex();
    }

    bool operator<(const I& other) const {
        return this->currentIndex() < other.currentIndex();
    }

    bool operator>=(const I& other) const {

        return this->currentIndex() >= other.currentIndex();
    }

    bool operator<=(const I& other) const {
        return this->currentIndex() <= other.currentIndex();
    }

public:
    virtual idx_t currentIndex() const = 0;
    virtual size_t length() const = 0;
};

template<class T, class I>
I operator+(unsigned int i, const I itr) {
    return itr + i;
}

SYLPH_END_NAMESPACE

// Previously defined here, now defined elsewhere
#include "Foreach.h"

#endif	/* SYLPH_CORE_ITERATOR_H_ */


// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
