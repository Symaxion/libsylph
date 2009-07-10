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
#include "Iterable.h"
#include <iterator>

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

enum itr_begin_t {
    itr_begin
};

enum itr_end_t {
    itr_end
};


#define S_FORWARD_ITERATOR(self,type,object) \
    self() : ::Sylph::ForwardIterator<type,object>(){ \
        construct(false,null); \
    } \
    self(itr_begin_t t, object* obj) : \
      ::Sylph::ForwardIterator<type,object>(t,obj) { \
        construct(true, obj); \
    } \
    self(itr_end_t t, object* obj) : \
      ::Sylph::ForwardIterator<type,object>(t,obj) { \
        construct(false, obj); \
    } \
    self(self<type,object>& other) : \
     ::Sylph::ForwardIterator<type,object>(other) \
    { copyFrom(other); }

#define S_BIDIRECTIONAL_ITERATOR(self,type,object) \
    self() : ::Sylph::BidirectionalIterator<type,object>(){ \
        construct(false,null); \
    } \
    self(itr_begin_t t, object* obj) : \
      ::Sylph::BidirectionalIterator<type,object>(t,obj) { \
        construct(true, obj); \
    } \
    self(itr_end_t t, object* obj) : \
      ::Sylph::BidirectionalIterator<type,object>(t,obj) { \
        construct(false, obj); \
    } \
    self(self<type,object>& other) : \
     ::Sylph::BidirectionalIterator<type,object>(other) \
    { copyFrom(other); }

#define S_RANDOM_ACCESS_ITERATOR(self,type,object) \
    self() : ::Sylph::RandomAccessIterator<type,object>(){ \
        construct(false,null); \
    } \
    self(itr_begin_t t, object* obj) : \
      ::Sylph::RandomAccessIterator<type,object>(t,obj) { \
        construct(true, obj); \
    } \
    self(itr_end_t t, object* obj) : \
      ::Sylph::RandomAccessIterator<type,object>(t,obj) { \
        construct(false, obj); \
    } \
    self(self<type,object>& other) : \
     ::Sylph::RandomAccessIterator<type,object>(other) \
    { copyFrom(other); }


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
template<class T, class IteratedObject>
class ForwardIterator : public Object {
public:
    typedef std::forward_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
public:
    // Implementation of the required functions in terms of the overridable
    // functions

    ForwardIterator() : _end_reached_(0) {
    }

    ForwardIterator(itr_begin_t, IteratedObject* obj) : _end_reached_(0) {
    }

    ForwardIterator(itr_end_t, IteratedObject* obj) : _end_reached_(2) {
    }

    ForwardIterator(ForwardIterator<T, IteratedObject>& other) :
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

    const ForwardIterator<T, IteratedObject> & operator++() const {
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

    ForwardIterator<T, IteratedObject> & operator++() {
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

    const ForwardIterator<T, IteratedObject> operator++(int) const {
        ForwardIterator<T, IteratedObject> toReturn(*this);
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

    ForwardIterator<T, IteratedObject> operator++(int) {
        ForwardIterator<T, IteratedObject> toReturn(*this);
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

    ForwardIterator<T, IteratedObject> & operator=
            (const ForwardIterator<T, IteratedObject>& other) {
        copyFrom(other);
        _end_reached_ = other._end_reached_;
        return *this;
    }

    virtual bool operator==(const ForwardIterator<T, IteratedObject>& other) const {
        return (_end_reached_ == other._end_reached_) && equals(other);
    }

    bool operator!=(const ForwardIterator<T, IteratedObject>& other) const {
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
    virtual void construct(bool begin, IteratedObject* obj) const = 0;
    /**
     * <b>OVERRIDE THIS METHOD</b> Returns a pointer to the object the iterator
     * is currnetly pointing at. Note that no beyond-the-end checking needs
     * to be done, this is all done automagically for you.
     * @return The object this iterator is currently pointing at.
     */
    virtual pointer current() const = 0;
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
     * <b>OVERRIDE THIS METHOD</b> Tells wheter this Iterator is equal to any
     * other Iterator over the same type of collection.
     * @param other An other ForwardIterator to compare this one against.
     * @return <i>true</i> iff the two iterators are completely equal (i.e.
     * they iteratate over the same collection and currently point to the same
     * object), false otherwise.
     */
    virtual bool equals(const ForwardIterator<T, IteratedObject>& other) const = 0;
    /**
     * <b>OVERRIDE THIS METHOD</b> Copies this iterator's fields from an other
     * ForwardIterator over the same type of collection, such that
     * <code>this->equals(other)</code> is <i>true</i>
     * @param other An other Iterator to copy the current one from.
     */
    virtual void copyFrom(ForwardIterator<T, IteratedObject>& other) const = 0;
    /**
     * Do not use or modify!
     */
    mutable unsigned char _end_reached_;
};

template<class T, class IteratedObject>
class BidirectionalIterator : public ForwardIterator<T, IteratedObject> {
public:
    typedef std::bidirectional_iterator_tag iterator_category;
public:

    BidirectionalIterator() : _end_reached_(0) {
    }

    BidirectionalIterator(itr_begin_t, IteratedObject* obj) : _end_reached_(0) {
    }

    BidirectionalIterator(itr_end_t, IteratedObject* obj) : _end_reached_(2) {
    }

    BidirectionalIterator(BidirectionalIterator<T, IteratedObject>& other) :
    _end_reached_(other._end_reached_) {
        copyFrom(other);
    }

    BidirectionalIterator<T, IteratedObject> & operator--() {
        if (_end_reached_ == 2) {
            _end_reached_ = 1;
            return *this;
        } else if (!hasPrevious()) {
            sthrow(IteratorException, "Begin of iterator");
        } else {
            if (_end_reached_ == 1) _end_reached_ = 0;
            previous();
            return *this;
        }
    }

    const BidirectionalIterator<T, IteratedObject> & operator--() const {
        if (_end_reached_ == 2) {
            _end_reached_ = 1;
            return *this;
        } else if (!hasPrevious()) {
            sthrow(IteratorException, "Begin of iterator");
        } else {
            if (_end_reached_ == 1) _end_reached_ = 0;
            previous();
            return *this;
        }
    }

    BidirectionalIterator<T, IteratedObject> operator--(int) {
        BidirectionalIterator toReturn(*this);
        if (_end_reached_ == 2) {
            _end_reached_ = 1;
            return *toReturn;
        } else if (!hasPrevious()) {
            sthrow(IteratorException, "Begin of iterator");
        } else {
            if (_end_reached_ == 1) _end_reached_ = 0;
            previous();
            return *toReturn;
        }
    }

    const BidirectionalIterator<T, IteratedObject> operator--(int) const {
        BidirectionalIterator toReturn(*this);
        if (_end_reached_ == 2) {
            _end_reached_ = 1;
            return *toReturn;
        } else if (!hasPrevious()) {
            sthrow(IteratorException, "Begin of iterator");
        } else {
            if (_end_reached_ == 1) _end_reached_ = 0;
            previous();
            return *toReturn;
        }
    }

    bool operator==(const BidirectionalIterator<T, IteratedObject>& other) const {
        return ((_end_reached_ == other._end_reached_) ||
                (hasPrevious() == other.hasPrevious())) && equals(other);
    }
public:
    virtual bool hasPrevious() const = 0;
    virtual void previous() const = 0;
};

template<class T, class IteratedObject>
class RandomAccessIterator : public BidirectionalIterator<T, IteratedObject> {
public:
    typedef std::random_access_iterator_tag iterator_category;
public:

    RandomAccessIterator() : _end_reached_(0) {
    }

    RandomAccessIterator(itr_begin_t, IteratedObject* obj) : _end_reached_(0) {
    }

    RandomAccessIterator(itr_end_t, IteratedObject* obj) : _end_reached_(2) {
    }

    RandomAccessIterator(BidirectionalIterator<T, IteratedObject>& other) :
    _end_reached_(other._end_reached_) {
        copyFrom(other);
    }

    RandomAccessIterator<T, IteratedObject> & operator+=(unsigned int i) {
        ptrdiff_t diff = i;
        if (i >= 0) while (diff--) ++(*this);
        else while (diff++) --(*this);
        return *this;
    }

    const RandomAccessIterator<T, IteratedObject> & operator+=
            (unsigned int i) const {
        ptrdiff_t diff = i;
        if (i >= 0) while (diff--) ++(*this);
        else while (diff++) --(*this);
        return *this;
    }

    RandomAccessIterator<T, IteratedObject> & operator-=(unsigned int i) {
        return *this += -i;
    }

    const RandomAccessIterator<T, IteratedObject> & operator-=
            (unsigned int i) const {
        return *this += -i;
    }

    const RandomAccessIterator<T, IteratedObject> operator+
    (unsigned int i) const {
        RandomAccessIterator<T, IteratedObject> toReturn(*this);
        return toReturn += i;
    }

    RandomAccessIterator<T, IteratedObject> operator-(unsigned int i) {
        return *this + -i;
    }

    ptrdiff_t operator-(const RandomAccessIterator<T, IteratedObject>&
            other) const {
        if (*this > other) return this->currentIndex() - other.currentIndex();
        else return other.currentIndex() - this->currentIndex();
    }

    const reference operator[](unsigned int offset) const {
        return *(*this +offset);
    }

    reference operator[](unsigned int offset) {
        return *(*this +offset);
    }

    bool operator>(const RandomAccessIterator<T, IteratedObject>&
            other) const {
        return this->currentIndex() > other.currentIndex();
    }

    bool operator<(const RandomAccessIterator<T, IteratedObject>&
            other) const {
        return this->currentIndex() < other.currentIndex();
    }

    bool operator>=(const RandomAccessIterator<T, IteratedObject>&
            other) const {
        return this->currentIndex() >= other.currentIndex();
    }

    bool operator<=(const RandomAccessIterator<T, IteratedObject>&
            other) const {
        return this->currentIndex() <= other.currentIndex();
    }

public:
    virtual idx_t currentIndex() = 0;
    virtual size_t length() = 0;
};

template<T, IteratedObject>
RandomAccessIterator<T, IteratedObject> operator+
    (unsigned int i, const RandomAccessIterator<T, IteratedObject> itr) {
    return itr+i;
}

/**
 * SylphIterator provides a easier-to-use wrapper around STL iterators. The
 * interface of a SylphIterator is similar to a Java-style iterator, but it is
 * backed by a STL iterator and can therefore be used for any class supporitng
 * STL iterators. <p>
 * To create a Sylph-style iterator for a certian class, use the <code>
 * S_CREATE_SYLPH_ITERATOR(</code><i>class-name</i><code>)</code> macro.
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
        Iter::reference toReturn = *itr;
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

#define S_CREATE_SYLPH_ITERATOR(Class) \
typedef SylphIterator< Class##::iterator > Class##Iterator; \
template<class T> \
const Class##Iterator Class##<T>::getIterator() { \
    return Class##Iterator(this->begin()); \
}\
template<class T>\
Class##Iterator Class##<T>::getMutableIterator() { \
    return Class##Iterator(this->begin()); \
}


SYLPH_END_NAMESPACE

// note : there is a reason why the name is so strange -- do not use directly!

struct s_foreach_container_base_7tQmTc4i {
};

template<class T>
class s_foreach_container_fjAk8tb1 : public s_foreach_container_base_7tQmTc4i {
public:

    inline s_foreach_container_fjAk8tb1(const T& t) : c(t), brk(0), i(c) {
    };
    const T c;
    mutable int brk;
    typename T::Iterator i;

    inline bool condition() const {
        return (!brk++ && i.hasNext());
    }
};

template<class T>
inline s_foreach_container_base_7tQmTc4i s_foreach_container_new(const T & t) {
    return s_foreach_container_fjAk8tb1<T > (t);
}

template<class T>
inline s_foreach_container_fjAk8tb1<T> * sf_cast(
const s_foreach_container_base_7tQmTc4i& bas, const T&) {
    return static_cast<s_foreach_container_fjAk8tb1<T> > (bas);
}

#define sforeach(variable,container) \
for (s_foreach_container_base_7tQmTc4i & _container_ = \
         s_foreach_container_new(container); \
         sf_cast(_container_,container)->condition(); )               \
        for (variable = sf_cast(_container_, container)->i++; \
         sf_cast(_container_, container)->brk; \
             --sf_cast(_container_, container)->brk)

#endif	/* _ITERATOR_H */

