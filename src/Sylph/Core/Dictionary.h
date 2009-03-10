/* 
 * File:   Dictionary.h
 * Author: frank
 *
 * Created on 8 februari 2009, 14:19
 */

#ifndef _DICTIONARY_H
#define	_DICTIONARY_H

#include "Object.h"
#include "Hash.h"

SYLPH_START_NAMESPACE(Core)
class Vector;
class DictionaryPointer;
class DictionaryEntry;

template<class _key, class _value, class _hash = Hash<_key>()>
class Dictionary {
public:
    typedef _key Key;
    typedef _value Value;
    typedef _hash HashFunction;
public:
    Dictionary(std::size_t initialCapacity = 11, float loadFactor = .75f);
    Dictionary(Dictionary<Key,Value,HashFunction> & orig);

    virtual ~Dictionary();

    void clear();
    bool containsKey(Key & key) const;
    bool containsValue(Value & value) const;
    const Vector<DictionaryEntry> entrySet();

    Value * get(Key & key);
    const Value * get(Key & key) const;

    DictionaryPointer<Key> operator[](Key & key);
    const DictionaryPointer<Key> operator[](Key & key) const;

    bool empty();
    const Vector<Key> keys();
    const Vector<Value *> values();

    Value * put(Key & key, Value * value);
    void putAll(Dictionary<Key,Value,HashFunction> & dict);

    Value * remove(Key & key);
    void clear();
private:
    std::size_t size;
    Array<DictionaryEntry<Key,Value>*> * buckets;
    Vector<Key> keyCache;
    Vector<Value *> valueCache;
    Vector<DictionaryEntry<Key,Value>*> entryCache;
    std::size_t threshold;
    float loadFactor;
    HashFunction hashf;
    int hash(Key & key);
    void rehash();
};

SYLPH_END_NAMESPACE(Core)

#endif	/* _DICTIONARY_H */

