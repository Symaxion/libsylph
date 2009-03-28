/* 
 * File:   DictionaryIterator.h
 * Author: frank
 *
 * Created on 12 maart 2009, 16:54
 */

#ifndef DICTIONARYITERATOR_H_
#define	DICTIONARYITERATOR_H_

#include "Iterator.h"
#include "Array.h"

SYLPH_START_NAMESPACE(Core)
SYLPH_PUBLIC

enum DictionaryIteratorType {
    KEYS,
    VALUES,
    ENTRIES
};

template<class T, class Key, class Value>
class DictionaryIterator : public virtual Iterator<T> {
public:
    explicit DictionaryIterator(const Dictionary<Key,Value> & _dict,
            DictionaryIteratorType _type) : dict(_dict), type(_type),
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
SYLPH_END_NAMESPACE(Core)

#endif	/* DICTIONARYITERATOR_H_ */

