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

template<class _key, class _value, class _hash = Hash<_key>(), class _equals = Equals<_key>()>
class HashMap : public virtual Object {
private:

    class HashEntry : public virtual Object {
    public:

        HashEntry(Key & _key, Value * _value) : key(_key), value(_value),
        next(NULL) {
        }

        virtual ~HashEntry() {
            delete Value;
        }

        HashEntry<Key, Value> * next;
        Key key;
        Value * value;
    };

    class HashPointer : public virtual Object {
    public:

        HashPointer(Key & key, HashMap * _map) :
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
    private:
        Key key;
        HashMap * map;
    };

    bool operator==(const HashPointer & p, const Value * v) {
        return Value(p) != NULL && v != NULL && Value(p) == v;
    }

    template<class Value>
    bool operator!=(const HashPointer & p, const Value & v) {
        return !(p == v);
    }

    class HashClctKeys : public Collection<Key> {
    public:

        HashClctKeys(HashMap * _map) : map(_map) {
        }

        virtual ~HashClctKeys() {
        }

        bool add(const Key & t) {
            map->put(t, NULL);
        }

        bool addAll(const Collection<Key> & c);

        void clear() {
            map->clear()
        }

        bool contains(const Key & t) const {
            return map->containsKey(t);
        }

        bool containsAll(const Collection<Key> & c) const;

        bool operator ==(const Collection<Key> & c) const;

        sint hashCode() const {
            // TODO!
            return 0;
        }

        bool empty() const {
            return map->empty();
        }

        bool remove(const Key & t) {
            return map->remove(t) != NULL;
        }

        bool removeAll(const Collection<Key> & c);

        bool retainAll(const Collection<Key> & c) {

        }

        std::size_t size() const {
            return map->size();
        }

        const Array<Key> toArray() const;

        Iterator iterator() const {
            return map->keyIterator();
        }

        MutableIterator mutableIterator();
    private:
        HashMap * map;
    };

    class HashClctValues : public Collection<Value *> {
    public:

        HashClctValues(HashMap * _map) : map(_map) {
        }

        virtual ~HashClctValues() {
        }

        bool add(const Value * & t);

        bool addAll(const Collection<Value *> & c);

        void clear() {
            map->clear()
        }

        bool contains(const Value * & t) const {
            return map->containsValue(t);
        }
        bool containsAll(const Collection<Value *> & c) const;
        bool operator ==(const Collection<Value *> & c) const;

        sint hashCode() const {
            // TODO!
            return 0;
        }

        bool empty() const {
            return map->empty();
        }

        bool remove(const Value * & t);

        bool removeAll(const Collection<Value *> & c);

        bool retainAll(const Collection<Value *> & c);

        std::size_t size() const {
            return map->size();
        }
        const Array<Value *> toArray() const;

        Iterator iterator() const {
            return map->valueIterator();
        }
        MutableIterator mutableIterator();

    private:
        HashMap * map;
    };

    class HashClctEntries : public Collection<EntryPtr> {
    public:

        HashClctEntries(HashMap * _map) : map(_map) {
        }

        virtual ~HashClctEntries() {
        }

        bool add(const EntryPtr& t) {
            map->put(t->key, t->value);
        }

        bool addAll(const Collection<EntryPtr> & c) {

            sforeach(EntryPtr entry, c) {
                map->put(entry->key, entry->value);
            }
        }

        void clear() {
            map->clear()
        }

        bool contains(const HashEntry & t) const {
            return EqualsFunction(map->get(t.key), t.value);
        }

        bool containsAll(const Collection<EntryPtr> & c) const {

            sforeach(EntryPtr entry, c) {
                if (!contains(entry)) return false;
            }
            return true;
        }

        bool operator ==(Collection<HashEntry > & c) const;

        int hashCode() {
            // TODO!
            return 0;
        };

        bool empty() const {
            return map->empty();
        }

        bool remove(const HashEntry & t) {
            return map->remove(t.key) != NULL;
        }

        bool removeAll(const Collection<HashEntry> & c);

        bool retainAll(const Collection<HashEntry> & c);

        std::size_t size() const {
            return map->size();
        }

        const Array<EntryPtr> toArray() const;

        Iterator iterator() const {
            return map->entryIterator();
        }

        MutableIterator mutableIterator();
    private:
        HashMap * map;
    };

    template<class T>
    class HashIterator : public Iterator<T> {
    public:

        enum IteratorType {
            KEYS,
            VALUES,
            ENTRIES
        };
    public:

        explicit HashIterator(const HashMap<Key, Value> & _map,
                HashIterator::IteratorType _type) : map(_map), type(_type),
        idx(map.buckets->length), count(map.size()), last(NULL), next(NULL) {
        }

        virtual ~HashIterator() {
        }

        bool hasNext() const {
            return count > 0;
        }

        const T & next() const {
            if (count == 0) sthrow(ArrayException, "End of iterator, please all get off!");
            count--;
            EntryPtr entry = next;

            while (entry == NULL) {
                entry = map->buckets[--idx];
            }

            next = entry->next;
            last = entry;
            if (type == VALUES) return (T) entry->value;
            else if (type == KEYS) return (T) entry->key;
            else return (T) entry;
        }
        bool hasPrevious() const;
        const T & previous() const;
        std::size_t nextIndex() const;
        std::size_t previousIndex() const;
    private:
        HashMap * map;
        IteratorType type;
        EntryPtr last;
        EntryPtr next;
        std::size_t idx;
        std::size_t count;
    };
public:
    typedef _key Key;
    typedef _value Value;
    typedef _hash HashFunction;
    typedef _equals EqualsFunction;
    typedef std::pair<Key, Value> EntryPair;
    typedef std::initializer_list<EntryPair> EntryList;
    typedef Ptr<HashEntry<Key, Value*> > EntryPtr;
public:

    explicit HashMap(std::size_t initialCapacity = 11, float loadFactor = .75f) {
        this->loadFactor = loadFactor;
        this->size = 0;
        this->threshold = initialCapacity * loadFactor;
        this->buckets = new Array<EntryPtr>(initialCapacity);
        for (int x = 0; x < buckets.length; x++) {
            buckets[x] = NULL;
        }
    }

    HashMap(const HashMap<Key, Value, HashFunction, EqualsFunction> & orig) {
        this->loadFactor = orig.loadFactor;
        this->size = orig.size;
        this->threshold = orig.threshold;
        this->buckets = new Array<EntryPtr>(orig.buckets->length);
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
        size = 0;
        buckets = new Array<EntryPtr>(11);

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

    Collection<HashEntry*> entrySet() {
        return HashClctEntries<Key, Value>;
    }

    const Collection<HashEntry*> entrySet() const {
        return HashClctEntries<Key, Value>;
    }

    std::size_t size() const {
        return size;
    }

    Value * get(const Key & key) {
        int h = hash(Key);
        EntryPtr entry = buckets[h];
        if (entry == NULL) return NULL;
        while (entry->next != NULL) {
            if (entry->key == key) return entry->value;
            entry = entry->next;
        }
        return NULL;
    }

    const Value * get(const Key & key) const {
        int h = hash(Key);
        EntryPtr entry = buckets[h];
        if (entry == NULL) return NULL;
        while (entry->next != NULL) {
            if (entry->key == key) return entry->value;
            entry = entry->next;
        }
        return NULL;
    }

    SYLPH_HASHMAP_RETURN_T(type) operator[](const Key & key) {
        return HashPointer(key, this);
    }

    const SYLPH_HASHMAP_RETURN_T(type) operator[](const Key & key) const {
        return HashPointer(key, this);
    }

    bool empty() const {
        return size() == 0;
    }

    const Collection<Key> keys() const {
        return HashClctKeys<Key > (this);
    }

    const Collection<_value *> values() const {
        return HashClctValues<Value*>(this);
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

        if (++size > threshold) {
            rehash();
            idx = hash(key);
        }
        EntryPtr newEnt = new HashEntry<Key, Value > (key, value);
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
                size--;
                return entry->value;
            }
            last = entry;
            entry = entry->next;
        }
        return NULL;
    }

    template<class T>
    HashIterator<T> iterator(HashIterator::IteratorType type) {
        return HashIterator<T>(*this, type);
    }
    HashIterator<Key> keyIterator() {
        return HashIterator<Key>(*this, HashIterator::KEYS);
    }
    HashIterator<Value*> valueIterator() {
        return HashIterator<Value*>(*this, HashIterator::VALUES);
    }
    HashIterator<EntryPtr> entryIterator() {
        return HashIterator<EntryPtr>(*this, HashIterator::ENTRIES);
    }

    HashMap & operator<<(const EntryList& elist) {
        for (EntryPair * ptr = elist.begin(); ptr != elist.end(); ptr++) {
            put(ptr->first, ptr->second);
        }
        return *this;
    }

private:
    std::size_t size;
    Array<EntryPtr> * buckets;
    std::size_t threshold;
    float loadFactor;
    HashFunction hashf;
    EqualsFunction equf;

    sint hash(const Key & key) {
        return key == NULL ? 0 : abs(hashf(key) % buckets.length)
    }

    void rehash() {
        Array<EntryPtr> * oldBuckets = buckets;

        int newcapacity = (buckets.length * 2) + 1;
        threshold = (int) (newcapacity * loadFactor);
        buckets = new Array<EntryPtr>(newcapacity);

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

