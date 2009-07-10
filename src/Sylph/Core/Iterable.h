/* 
 * File:   Iterable.h
 * Author: frank
 *
 * Created on 6 december 2008, 17:15
 */

#ifndef _ITERABLE_H
#define	_ITERABLE_H

#include "Object.h"
#include "Iterator.h"

SYLPH_BEGIN_NAMESPACE

SYLPH_PUBLIC
SYLPH_END_NAMESPACE

#define S_ITERABLE(type) \
public: \
typedef type Type; \
typedef SylphIterator<iterator> MutableIterator; \
typedef const iterator const_iterator; \
typedef const SylphIterator<iterator> Iterator; \
    /**\
     * Get an instance of the Iterator for this class. The iterator returned \
     * is not mutable, i.e. it cannot modify the contents of the collection.<p>\
     * Unless mutability is really required, it is recommended to prefer this\
     * method, as it does not allow accidential modifications.\
     * @return An SylphIterator specific for the class being iterated over.\
     */\
    virtual Iterator getIterator() const; \
    /**\
     * Get an instance of the MutableIterator for this class. The iterator\
     * returned is mutable, i.e. it can modifiy the contents of the collection.\
     * @return A mutable SylphIterator for the class being iterated over.\
     */\
    virtual MutableIterator getMutableIterator();\
\
    /** \
     * Alias for getIterator() \
     * @return An SylphIterator specific for the class being iterated over.\
     */\
    inline Iterator itr() { return getIterator(); }\
    /** \
     * Alias for getMutableIterator() \
     * @return A mutable SylphIterator for the class being iterated over.\
     */\
    inline MutableIterator mitr() { return getMutableIterator(); }\
\
    virtual iterator begin() { return iterator(::Sylph::itr_begin, *this); }\
    virtual iterator end() { return iterator(::Sylph::itr_end, *this); }\
\
    virtual iterator begin() const { my_iterator(::Sylph::itr_begin, *this); }\
    virtual iterator end() const { my_iterator(::Sylph::itr_end, *this); }


#endif	/* _ITERABLE_H */

