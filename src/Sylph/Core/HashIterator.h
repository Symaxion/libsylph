/* 
 * File:   DictionaryIterator.h
 * Author: frank
 *
 * Created on 12 maart 2009, 16:54
 */

#ifndef HASHITERATOR_H_
#define	HASHITERATOR_H_

#include "Iterator.h"
#include "Array.h"
#include "Dictionary.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

template<class K,class V, class H>
class HashMap;

enum HashIteratorType {
    KEYS,
    VALUES,
    ENTRIES
};

template<class T, class Key, class Value>
class HashIterator : public virtual Iterator<T> {
public:
    explicit HashIterator(const HashMap<Key,Value> & _dict,
            HashIteratorType _type) : dict(_dict), type(_type),
            idx(_dict.buckets->length), count(dict.size) {}
    virtual ~DictionaryIterator() {}

    bool hasNext() const;
    const T & next() const;
    bool hasPrevious() const;
    const T & previous() const;
    std::size_t nextIndex() const;
    std::size_t previousIndex() const;
private:
    Dictionary * dict;
    DictionaryIteratorType type;
    DictionaryEntry<Key,Value> * last = NULL;
    DictionaryEntry<Key,Value> * next = NULL;
    std::size_t idx;
    std::size_t count;

};
SYLPH_END_NAMESPACE

#endif	/* DICTIONARYITERATOR_H_ */

