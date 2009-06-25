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
#include "Util.h"

#include "Array.h"
#include "Collection.h"
#include "Ptr.h"

#include <cmath>
#include <initializer_list>

#ifdef SYLPH_DOXYGEN
#define SYLPH_HASHMAP_RETURN_T(type) type
#else
#define SYLPH_HASHMAP_RETURN_T(type) HashPointer
#endif

SYLPH_BEGIN_NAMESPACE

template<class key_, class value_, class hash_ = sint(*)(key_), class equals_ = bool(*)(key_) >
class HashMap : public virtual Object {
private:
    class Entry;
public:
    typedef key_ Key;
    typedef value_ Value;
    typedef hash_ HashFunction;
    typedef equals_ EqualsFunction;
    typedef std::pair<Key, Value> EntryPair;
    typedef std::initializer_list<EntryPair> EntryList;
    typedef Entry* EntryPtr;
public:

    class Entry : public virtual Object {
        friend class HashMap;
        friend class iterator;
    public:

        Entry(Key & _key, Value * _value) : key(_key), value(_value),
        next(NULL) {
        }

        virtual ~Entry() {
            delete value;
        }

        Key key;
        Value * value;
    private:
        Entry * next;
    };

    class Pointer : public virtual Object {
    public:

        Pointer(Key & key, HashMap * _map) :
        key(key), map(map) {
        }

        inline operator Value*() {
            return map->get(key);
        }

        inline operator const Value*() const {
            return map->get(key);
        }

        inline Value & operator*() {
            return *map->get(key);
        }

        inline const Value & operator*() const {
            return *map->get(key);
        }

        inline Value & operator->() {
            return *map->get(key);
        }

        inline const Value & operator->() const {
            return *map->get(key);
        }

        inline Value * operator=(Value * value) {
            return map->put(key, value);
        }

        bool operator==(const Value * v) {
            return static_cast<Value*> (*this) != NULL && v != NULL &&
                    static_cast<Value*> (*this) == v;
        }

        bool operator!=(const Value & v) {
            return !(*this == v);
        }

    private:
        Key key;
        HashMap * map;
    };

    class iterator : public ForwardIterator<Entry, HashMap> {
    public:
        S_FORWARD_ITERATOR(iterator, Entry, HashMap)
        void construct(bool begin, HashMap* obj) const {
            map = obj;
            if(begin) {
                count = map.size();
                idx = map.buckets->length;
                currentPointer = *(map.buckets)[idx];
                while(currentPointer == NULL) {
                    currentPointer = *(map.buckets)[--idx];
                }
            } else {
                count = 0;
                idx = 0;
                currentPointer = NULL;
            }
        }
        pointer current() const {
            return currentPointer;
        }
        void next() const {
            currentPointer = currentPointer->next;
            while(currentPointer == NULL) {
                currentPointer = *(map.buckets)[--idx];
            }
        }
        bool hasNext() const {
            return count > 0;
        }
        bool equals(iterator<Entry,HashMap>& other) const {
            return map == other.map && ((count == other.count && idx == other.idx
                    && currentPointer == other.currentPointer) || (count ==
                    other.count == 0));
        }
        void copyFrom(iterator<Entry,HashMap>& other) const {
            map = other.map;
            count = other.count;
            idx = other.idx;
            currentPointer = other.currentPointer;
        }
    private:
        HashMap * map;
        mutable idx_t count;
        mutable idx_t idx;
        EntryPtr currentPointer;

    };

public:

    explicit HashMap(std::size_t initialCapacity = 11, float loadFactor = .75f,
            HashFunction h = Hash<Key>, EqualsFunction e = Equals<Key>) {
        this->loadFactor = loadFactor;
        this->_size = 0;
        this->threshold = initialCapacity * loadFactor;
        this->buckets = new Array<EntryPtr > (initialCapacity);
        for (int x = 0; x < buckets.length; x++) {
            buckets[x] = NULL;
        }
        hashf = h;
        equf = e;
    }

    HashMap(const HashMap<Key, Value, HashFunction, EqualsFunction> & orig) {
        this->loadFactor = orig.loadFactor;
        this->_size = orig._size;
        this->threshold = orig.threshold;
        this->buckets = new Array<EntryPtr > (orig.buckets->length);
        arraycopy(*(orig.buckets), 0, *buckets, 0, orig.buckets->length);
    }

    HashMap(const EntryList & elist) : HashMap() {
        for (EntryPair * ptr = elist.begin(); ptr != elist.end(); ptr++) {
            put(ptr->first, ptr->second);
        }
    }

    virtual ~HashMap() {
        delete this->buckets;
    }

    void clear() {
        delete buckets;

        threshold = loadFactor * 11;
        _size = 0;
        buckets = new Array<EntryPtr > (11);

    }

    bool containsKey(const Key & key) const {
        std::idx_t idx = hash(key);
        EntryPtr entry = buckets[idx];
        while (entry != NULL) {
            if (equf(key, entry->key)) return true;
            entry = entry->next;
        }
        return false;
    }

    bool containsValue(const Value * value) const {
        for (std::idx_t i = buckets.length - 1; i >= 0; i--) {
            EntryPtr entry = buckets[i];
            while (entry != NULL) {
                if (equf(value, entry->value)) return true;
                entry = entry->next;
            }
        }
        return false;
    }

    std::size_t size() const {
        return _size;
    }

    Value * get(const Key & key) {
        int h = hash(key);
        EntryPtr entry = buckets[h];
        if (entry == NULL) return NULL;
        while (entry->next != NULL) {
            if (entry->key == key) return entry->value;
            entry = entry->next;
        }
        return NULL;
    }

    const Value * get(const Key & key) const {
        int h = hash(key);
        EntryPtr entry = buckets[h];
        if (entry == NULL) return NULL;
        while (entry->next != NULL) {
            if (entry->key == key) return entry->value;
            entry = entry->next;
        }
        return NULL;
    }

    SYLPH_HASHMAP_RETURN_T(type) operator[](const Key & key) {
        return Pointer(key, this);
    }

    const SYLPH_HASHMAP_RETURN_T(type) operator[](const Key & key) const {
        return Pointer(key, this);
    }

    bool empty() const {
        return size() == 0;
    }

    Value * put(const Key & key, const Value * value) {
        idx_t idx = hash(key);
        EntryPtr entry = buckets[idx];

        while (entry != NULL) {
            if (EqualsFunction(key, entry->key)) {
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

    void putAll(const HashMap<Key, Value, HashFunction, EqualsFunction> & map) {

        sforeach(EntryPtr ptr, map.entrySet()) {
            this->put(ptr->key, ptr->value);
        }
    }

    Value * remove(const Key & key) {
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

    HashMap & operator<<(const EntryList& elist) {
        for (EntryPair * ptr = elist.begin(); ptr != elist.end(); ptr++) {
            put(ptr->first, ptr->second);
        }
        return *this;
    }

private:
    std::size_t _size;
    Array<EntryPtr> * buckets;
    std::size_t threshold;
    float loadFactor;
    HashFunction hashf;
    EqualsFunction equf;

    sint hash(const Key & key) {
        return key == NULL ? 0 : abs(hashf(key) % buckets.length);
    }

    void rehash() {
        Array<EntryPtr> * oldBuckets = buckets;

        int newcapacity = (buckets.length * 2) + 1;
        threshold = (int) (newcapacity * loadFactor);
        buckets = new Array<EntryPtr > (newcapacity);

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

SYLPH_END_NAMESPACE
#endif	/* HASHMAP_H_ */

