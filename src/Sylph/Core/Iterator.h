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


template<class T, class IteratedObject>
class ForwardIterator {
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
    virtual void construct(bool begin, IteratedObject* obj) const = 0;
    virtual pointer current() const = 0;
    virtual void next() const = 0;
    virtual bool hasNext() const = 0;
    virtual bool equals() const = 0;
    virtual void copyFrom(ForwardIterator<T, IteratedObject>&) const = 0;
    virtual const IteratedObject* iteratedObject() const = 0;
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
 * Iterator provides a transparant interface for iterating over collections.
 * Each @c Iterable should have a specific implementation of this class. It is
 * not required to implement all methods of this class.
 * <p>
 * A <code>const</code> @c Iterator should allow <code>const</code> access to
 * items in the collection, but must not allow modification of those items.
 * A non-<code>const</code> @c Iterator should allow both access and
 * modification of the items. In order to comply to this behavior, it may
 * be necessary to declare one or more fields as <code>mutable</code>.
 * <p>
 * This class is used implicitly by @c sforeach(), and therefore an
 * implementation of this class is required for each @c Iterable that needs
 * to be able to being iterated over by @c sforeach() .
 */
template<class Iter>
class SylphIterator : public virtual Object {
public:

    /**
     * Creates a new Iterator from an Iterable. An Iterator can either be
     * constructed explicitly with this constructor, in which case the correct
     * type of Iterator for the particular collection needs to be known, or
     * through Iterable::iterator() or Iterable::mutableIterator() .
     * <p>The default implementation does nothing.
     * @param it The iterable to iterate over.
     */
    inline SylphIterator(Iter & it) : itr(it) {
    }

    inline virtual ~SylphIterator() {
    }

    /**
     * Checks if this iterator has any more entries in forward direction.
     * @return <i>true</i> if there are more entries, <i>false</i> otherwise.
     * @note You are not required to override this method if this Iterator
     * cannot iterate forward.
     */
    virtual bool hasNext() const {
        return itr.hasNext();
    }
    /**
     * Returns the next entry in the forward direction and moves the iterator
     * one place forward.
     * @throw Exception if there are no more entries.
     * @return The next entry
     * @note You are not required to override this method if this Iterator
     * cannot iterator forward.
     */
    virtual const typename Iter::reference next() const {
        Iter::reference toReturn = *itr;
        ++itr;
        return toReturn;
    }
    /**
     * Checks if this iterator has any more entries in backward direction.
     * @return <i>true</i> if there are more entries, <i>false</i> otherwise.
     * @note You are not required to override this method if this Iterator
     * cannot iterate backward.
     */
    virtual bool hasPrevious() const {
        return itr.hasPrevious();
    }
    /**
     * Returns the next entry in the backward direction and moves the iterator
     * one place backward.
     * @throw Exception if there are no more entries.
     * @return The previous entry
     * @note You are not required to override this method if this Iterator
     * cannot iterate backward.
     */
    virtual const typename Iter::reference previous() const {
        --itr;
        return *itr;
    }

    /**
     * Moves the Iterator to the place "before" the first item, that is,
     * it gives the pointer in the iterator such a value that hasPrevious
     * returns false.
     * @note You are not required to override this method if this Iterator
     * cannot iterate backward.
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
     * @note You are not required to override this method if this Iterator
     * cannot iterate forward
     */
    virtual void back() const {
        while(itr.hasNext()) ++itr;
    }

    /**
     * Returns the next index of the Iterable in the forward direction.
     * @throw Exception if there are no more entries.
     * @return The next index in the Iterable
     * @note You are not required to override this method if this Iterator
     * cannot iterate forward; or if the Iterable is unordered.
     */
    virtual std::idx_t nextIndex() const {
        return itr.currentIndex();
    }

    /**
     * Returns the next index of the Iterable in the backward direction.
     * @throw Exception if there are no more entries.
     * @return The previous index in the Iterable
     * @note You are not required to override this method if this Iterator
     * cannot iterate backward; or if the Iterable is unordered.
     */
    virtual std::idx_t previousIndex() const {
        return itr.currentIndex() - 1;
    }

    /**
     * Replaces the last item returned by next() or previous() with the given
     * item
     * @param t The item to replace the last returned item with.
     * @note You are not required to override this method if the collection
     * does not support replacing.
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
     * Synoynmous for next()
     */
    const typename Iter::reference operator++(int) const {
        return next();
    }

    /**
     * Synonymous for previous()
     */
    const typename Iter::reference operator--(int) const {
        return previous();
    }
private:
    Iter itr;
};

// todo
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

