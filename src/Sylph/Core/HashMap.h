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
 * Created on 13 april 2009, 13:15
 */

#ifndef HASHMAP_H_
#define	HASHMAP_H_

#include "Object.h"
#include "Debug.h"
#include "Hash.h"
#include "Equals.h"
#include "Util.h"

#include "Array.h"

#include <cmath>
#include <initializer_list>

SYLPH_BEGIN_NAMESPACE

/**
 * @todo Write better documentation!
 */
template<class key_, class value_,
class hash_ = Hash<key_>,
class equals_ = Equals<value_*> >
class HashMap : public virtual Object {
public:
    class Entry;
public:
    typedef key_ Key;
    typedef value_ Value;
    typedef hash_ HashFunction;
    typedef equals_ EqualsFunction;
    typedef Entry* EntryPtr;
public:

    struct EntryHelper {
        Key key;
        Value& value;
    };

    class Entry {
        friend class HashMap;
        friend class iterator;
    public:

        Entry(Key & _key, Value * _value) : key(_key), value(_value),
        next(NULL) {
        }

        virtual ~Entry() {
            delete value;
        }

        const Key key;
        Value * value;
    private:
        Entry * next;
    };

    class Pointer : public virtual Object {
    public:

        Pointer(Key _key, HashMap * _map) :
        key(_key), map(_map) {
        }

        inline operator Value&() {
            Value * v = map->get(key);
            check_nullptr(v);
            return *v;
        }

        inline operator const Value&() const {
            Value * v = map->get(key);
            check_nullptr(v);
            return *v;
        }

        inline void operator=(Value& value) {
            map->put(key, &value);
        }

        inline void operator=(Value value) {
            map->put(key, new Value(value));
        }

    private:
        Key key;
        HashMap * map;
    };

    class iterator : public ForwardIterator<Entry, iterator> {
        typedef ForwardIterator<Entry, iterator> super;
    public:

        iterator(bool begin = false,
                HashMap<key_, value_, hash_, equals_>* obj = NULL) : super(begin),
        map(obj) {
            if (begin) {
                count = map->size();
                idx = map->buckets.length;
                currentPointer = map->buckets[idx];
                while (currentPointer == NULL) {
                    currentPointer = map->buckets[--idx];
                }
            } else {
                count = 0;
                idx = 0;
                currentPointer = NULL;
            }
        }

        iterator(bool begin = false,
                const HashMap<key_, value_, hash_, equals_>* obj = NULL) :
        super(begin),
        map(const_cast<HashMap<key_, value_, hash_, equals_>*> (obj)) {
            if (begin) {
                count = map->size();
                idx = map->buckets.length;
                currentPointer = map->buckets[idx];
                while (currentPointer == NULL) {
                    currentPointer = map->buckets[--idx];
                }
            } else {
                count = 0;
                idx = 0;
                currentPointer = NULL;
            }
        }

        iterator(const iterator& other) : map(other.map), count(other.count),
        idx(other.idx), currentPointer(other.currentPointer) {
        }

        typename super::reference current() const {
            return *currentPointer;
        }

        void next() const {
            currentPointer = currentPointer->next;
            while (currentPointer == NULL) {
                currentPointer = map->buckets[--idx];
            }
        }

        bool hasNext() const {
            return count > 0;
        }

        bool equals(const iterator& other) const {
            return map == other.map && ((count == other.count && idx == other.idx
                    && currentPointer == other.currentPointer) || (count ==
                    other.count));
        }


    private:
        HashMap * map;
        mutable idx_t count;
        mutable idx_t idx;
        mutable EntryPtr currentPointer;
    };

    S_ITERABLE(Entry)

public:

    /**
     * Creates a new HashMap.
     * @param initialCapacity The capacity the HashMap starts with. Recommended
     * to be a prime.
     * @param _loadFactor The percentage of the HashMap that has to be filled
     * before rehashing starts.
     * @param h A suitable hash function
     * @param e A suitable equals function.
     */
    explicit HashMap(std::size_t initialCapacity = 11, float _loadFactor = .75f,
            HashFunction h = Hash<Key>(), EqualsFunction e = Equals<Value*>())
    : loadFactor(_loadFactor), _size(0), buckets(initialCapacity),
    threshold(initialCapacity*loadFactor), hashf(h), equf(e) {
    }

    /**
     * Copies the contents of another HashMap into this HashMap.
     * @param orig The original HashMap
     */
    HashMap(const HashMap<Key, Value, HashFunction, EqualsFunction> & orig)
    : loadFactor(orig.loadFactor), _size(orig._size),
    buckets(orig.buckets.length), threshold(orig.threshold),
    hashf(orig.hashf), equf(orig.equf) {
        arraycopy(orig.buckets, 0, buckets, 0, orig.buckets.length);
    }

    /**
     * Creates a HashMap from an initializer list. E.g.
     * <pre>
     * HashMap&lt;String,String&gt; h = {{"Hello","Hi"},{"World","Earth"}};
     * </pre>
     * All parameters will be initialized to default.
     * @param init An initializer list
     */
    HashMap(const std::initializer_list<EntryHelper>& init) : loadFactor(.75f),
    _size(init.size()), buckets((init.size() << 1) + 1),
    threshold(buckets.length*loadFactor), hashf(Hash<Key>()),
    equf(Equals<Value*>()) {
        for (EntryHelper* it = init.begin(); it != init.end(); ++it) {
            put(it->key, &(it->value));
        }
    }

    virtual ~HashMap() {
        try {
            size_t count = size();
            idx_t idx = buckets.length - 1;
            EntryPtr currentPointer = buckets[idx];
            while (count > 0) {
                while (currentPointer == NULL) {
                    currentPointer = buckets[--idx];
                }
                EntryPtr oldPtr = currentPointer;
                currentPointer = currentPointer->next;
                --count;
                delete oldPtr;
            }
        } strace;
    }

    /**
     * Removes all entries from the HashMap
     */
    void clear() {
        threshold = loadFactor * 11;
        _size = 0;
        buckets.clear();

    }

    /**
     * Checks whether this HashMap contains a given key.
     * @return <i>true</i> iff this HashMap contains given key.
     */
    bool containsKey(Key key) const {
        std::idx_t idx = hash(key);
        EntryPtr entry = buckets[idx];
        while (entry != NULL) {
            if (key == entry->key) return true;
            entry = entry->next;
        }
        return false;
    }

    /**
     * Checks whether this HashMap contains a given value.
     * @return <i>true</i> iff this HashMap contains given value.
     */
    bool containsValue(const Value * value) const {
        if(buckets.length == 0) return false;
        for (std::idx_t i = (buckets.length - 1); (signed)i >= 0; --i) {
            EntryPtr entry = buckets[i];
            while (entry != NULL) {
                if (equf(value, entry->value)) return true;
                entry = entry->next;
            }
        }
        return false;
    }

    /**
     * Returns the amount of entries in this HashMap.
     * @return The amount of entries in this HashMap.
     */
    std::size_t size() const {
        return _size;
    }

    /**
     * Get the value for given key, or null if this key does not exist.
     * @param key A key to search the value for
     * @return The value for given key, or null if this key does not exist.
     */
    Value * get(Key key) {
        int h = hash(key);
        EntryPtr entry = buckets[h];
        if (entry == NULL) {
            return NULL;
        }
        do {
            if (entry->key == key) return entry->value;
            entry = entry->next;
        } while (entry->next != NULL);
        return NULL;
    }

    /**
     * Get the value for given key, or null if this key does not exist.
     * @param key A key to search the value for
     * @return The value for given key, or null if this key does not exist.
     */
    const Value * get(Key key) const {
        int h = hash(key);
        EntryPtr entry = buckets[h];
        if (entry == NULL) {
            return NULL;
        }
        do {
            if (entry->key == key) return entry->value;
            entry = entry->next;
        } while (entry->next != NULL);
        return NULL;
    }

    Pointer operator[](Key key) {
        return Pointer(key, this);
    }

    const Pointer operator[](Key key) const {
        return Pointer(key, this);
    }

    /**
     * Checks if this HashMap is empty, i\.e\. it has no keys in it.
     * @return <i>true</i> iff size() == 0
     */
    bool empty() const {
        return size() == 0;
    }

    /**
     * Map a value to a given key. If the key does not yet exist, it is added.
     * If the key already exists, the value is overwritten and the old value
     * is returned.
     * @param key A new key
     * @param value The value for this new key
     * @return The old value if the key already existed, null otherwise.
     */
    Value * put(Key key, Value * value) {
        idx_t idx = hash(key);
        EntryPtr entry = buckets[idx];

        while (entry != NULL) {
            if (key == entry->key) {
                Value * val = entry->value;
                entry->value = val;
                return val;
            } else {
                entry = entry->next;
            }
        }

        if (++_size > threshold) {
            rehash();
            idx = hash(key);
        }
        EntryPtr newEnt = new Entry(key, value);
        newEnt->next = buckets[idx];
        buckets[idx] = newEnt;

        return NULL;
    }

    /**
     * Copies everything from the given HashMap into this HashMap. Existing
     * keys will be overwritten.
     * @param map Another HashMap.
     */
    void putAll(const HashMap<Key, Value, HashFunction, EqualsFunction>& map) {

        for (iterator it = map.begin(); it != map.end(); ++it) {
            this->put((*it)->key, (*it)->value);
        }
    }

    /**
     * Removes given key from the HashMap. If the key was in the HashMap, return
     * the associated value. If it was not, return null.
     * @return The old value of the key if it existed, null otherwise.
     */
    Value * remove(Key key) {
        std::idx_t idx = hash(key);
        EntryPtr entry = buckets[idx];
        EntryPtr last = NULL;

        while (entry != NULL) {
            if (equf(key, entry->key)) {
                if (last == NULL) {
                    buckets[idx] = entry->next;
                } else {

                    last->next = entry->next;
                }
                _size--;
                return entry->value;
            }
            last = entry;
            entry = entry->next;
        }
        return NULL;
    }

    HashMap & operator<<(const EntryHelper& eh) {
        put(eh.key, &(eh.value));
        return *this;
    }

private:
    float loadFactor;
    std::size_t _size;
    Array<EntryPtr> buckets;
    std::size_t threshold;
    HashFunction hashf;
    EqualsFunction equf;

    sint hash(const Key& key) const {
        return abs(hashf(key) % buckets.length);
    }

    void rehash() {
        Array<EntryPtr> oldBuckets = buckets;

        int newcapacity = (buckets.length * 2) + 1;
        threshold = (int) (newcapacity * loadFactor);
        buckets = Array<EntryPtr > (newcapacity);

        for (idx_t i = oldBuckets.length - 1; i >= 0; i--) {
            EntryPtr entry = oldBuckets[i];
            while (entry != NULL) {
                idx_t idx = hash(entry->key);
                EntryPtr next = entry->next;
                entry->next = buckets[idx];
                buckets[idx] = entry;
                entry = next;
            }
        }
    }
};

template<class K, class V, class H, class E>
bool operator==(const HashMap<K,V,H,E>& lhs, const HashMap<K,V,H,E>& rhs) {
    static E eq;
    for(typename HashMap<K,V,H,E>::iterator it = lhs.begin();
            it != lhs.end(); ++it) {
        if(!rhs.containsKey(it->key) || !eq(rhs.get(it->key), it->value))
            return false;
    }
    for(typename HashMap<K,V,H,E>::iterator it = rhs.begin();
            it != rhs.end(); ++it) {
        if(!lhs.containsKey(it->key) || !eq(lhs.get(it->key), it->value))
            return false;
    }
    return true;
}

SYLPH_END_NAMESPACE
#endif	/* HASHMAP_H_ */

