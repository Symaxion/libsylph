/* 
 * File:   HashMap.h
 * Author: frank
 *
 * Created on 13 april 2009, 13:15
 */

#ifndef HASHMAP_H_
#define	HASHMAP_H_

#include "Object.h"
#include "Hash.h"
#include "Equals.h"

SYLPH_BEGIN_NAMESPACE
template<class T>
class Collection;
template<class T>
class HashPointer;
template<class K,class V, class H>
class HashEntry;
template<class K, class V, class H>
class HashAssn;
template<class T, class K, class V>
class HashIterator;

template<class _key, class _value, class _hash = Hash<_key>(), class _equals = Equals<_key>()>
class HashMap : public Object {
    //friend class HashClctEntries;
public:
    typedef _key Key;
    typedef _value Value;
    typedef _hash HashFunction;
    typedef _equals EqualsFunction;
public:
    Dictionary(std::size_t initialCapacity = 11, float loadFactor = .75f);
    Dictionary(const Dictionary<Key,Value,HashFunction> & orig);

    virtual ~Dictionary();

    void clear();
    bool containsKey(const Key & key) const;
    bool containsValue(const Value * value) const;
    const Collection<HashEntry*> entrySet();
    std::size_t size();

    Value * get(const Key & key);
    const Value * get(const Key & key) const;

    HashPointer<Key> operator[](Key & key);
    const HashPointer<Key> operator[](Key & key) const;

    bool empty();
    const Collection<Key> keys();
    const Collection<Value *> values();

    Value * put(const Key & key, const Value * value);
    void putAll(const Dictionary<Key,Value,HashFunction> & dict);

    Value * remove(Key & key);

    inline DictAssn<Key,Value,HashFunction>
    insert(const Key & key, const Value * value) {
        put(key,value);
        return DictAssn<Key,Value,HashFunction>(*this);
    }


    template<class T>
    HashIterator<T,Key,Value*> iterator(HashIteratorType type);
    HashIterator<Key,Key,Value*> keyIterator();
    HashIterator<Value*,Key,Value*> valueIterator();
    HashIterator<HashEntry *,Key,Value*> entryIterator();

private:
    std::size_t size;
    Array<HashEntry<Key,Value>*> * buckets;
    std::size_t threshold;
    float loadFactor;
    HashFunction hashf;
    int hash(const Key & key);
    void rehash();
};

template<class K, class V,class H>
class HashAssn : public Object {
public:
    HashAssn(const Dictionary & dict) : _dict(dict) {}
    HashAssn<K,V,H> & operator()(const K & key, const V * value) {
        _dict.put(key, value);
        return *this;
    }
private:
    Dictionary<K,V,H> _dict;
};

SYLPH_END_NAMESPACE

#endif	/* HASHMAP_H_ */

