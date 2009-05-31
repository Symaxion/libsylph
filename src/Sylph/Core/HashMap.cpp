#include "Util.h"

#include "Dictionary.h"
#include "Vector.h"
#include "Array.h"

#include <cmath>

SYLPH_BEGIN_NAMESPACE

template<class Key, class Value>
class HashEntry : public virtual Object {
public:

    HashEntry(Key & _key, Value * _value) : key(_key), value(_value) {
    }

    virtual ~HashEntry() {
    }

    HashEntry<Key, Value> * next = NULL;
    Key key;
    Value * value;
};

template<class Key, class Value>
class HashPointer : public virtual Object {
    friend bool operator==(const HashPointer & p, const Value & v);
    friend bool operator!=(const HashPointer & p, const Value & v);
public:

    HashPointer(Key & _key, Dictionary * _dict) :
    key(_key), dict(_dict) {
    }

    operator Value() {
        return dict->get(key);
    }

    operator const Value() const {
        return dict->get(key);
    }

    inline Value * operator=(Value & value) {
        return dict->put(key, value);
    }
private:
    Key key;
    HashMap<Key,Value> * dict;
};

template<class Value>
bool operator==(const HashPointer & p, const Value & v) {
    return Value(p) != NULL && Value(p) == v;
}

template<class Value>
bool operator!=(const HashPointer & p, const Value & v) {
    return !(p == v);
}

template<class K,class V>
class HashClctKeys : public Collection<K> {
public:

    HashClctKeys(HashMap<K,V> * _map) : map(_map) {
    }

    virtual ~HashClctKeys() {
    }

    bool add(const K & t) {
        sthrow(UnsupportedOperationException);
    }
    bool addAll(Collection<K> & c) {
        sthrow(UnsupportedOperationException);
    }
    void clear() {
       map->clear()
    }
    bool contains(K & t) {
        return map->containsKey(t);
    }
    bool containsAll(Collection<K> & c) {
        sthrow(UnsupportedOperationException);
    }
    bool operator ==(Collection<K> & c) {
        sthrow(UnsupportedOperationException);
    }

    int hashCode() {
        // TODO!
        return 0;
    }
    bool empty() {
        return map->empty();
    }
    bool remove(K & t) {
        return map->remove(t) != NULL;
    }
    bool removeAll(Collection<K> & c) {
        sthrow(UnsupportedOperationException);
    }
    bool retainAll(Collection<K> & c) {

    }
    std::size_t size() const {
        return map->size();
    }
    const Array<K> toArray() const {
        sthrow(UnsupportedOperationException);
    }

    Iterator<K> iterator() const {
        return map->keyIterator();
    }
    MutableIterator<K> mutableIterator() {
        sthrow(UnsupportedOperationException);
    }
private:
    HashMap * map;
};


template<class T>
class HashClctValues : public Collection<T> {
public:

    HashClctValues(HashMap<K,V> * _dict) : map(_map) {
    }

    virtual ~HashClctValues() {
    }

    bool add(const T & t) {
        sthrow(UnsupportedOperationException);
    }
    bool addAll(Collection<T> & c) {
        sthrow(UnsupportedOperationException);
    }
    void clear() {
        dict->clear()
    }
    bool contains(T & t) {
        return dict->containsValue(t);
    }
    bool containsAll(Collection<T> & c) {
        sthrow(UnsupportedOperationException);
    }
    bool operator ==(Collection<T> & c) {
        sthrow(UnsupportedOperationException);
    }

    int hashCode() {
        // TODO!
        return 0;
    };
    bool empty() {
        return dict->empty();
    }
    bool remove(T & t) {
        sthrow(UnsupportedOperationException);
    }
    bool removeAll(Collection<T> & c) {
        sthrow(UnsupportedOperationException);
    }
    bool retainAll(Collection<T> & c) {

    }
    std::size_t size() const {
        return dict->size();
    }
    const Array<T> toArray() const {
        sthrow(UnsupportedOperationException);
    }

    Iterator<T> iterator() const {
        return dict->valueIterator();
    }
    MutableIterator<T> mutableIterator() {
        sthrow(UnsupportedOperationException);
    }
private:
    HashMap * map;
};

template<class K,class V>
class DictClctEntries : public Collection<DictionaryEntry<K,V*> > {
public:

    DictClctEntries(Dictionary * _dict) : dict(_dict) {
    }

    virtual ~DictClctEntries() {
    }

    bool add(const DictionaryEntry<K,V*> & t) {
        dict->put(t.key, t.value);
    }
    bool addAll(Collection<DictionaryEntry<K,V*> > & c) {
        sforeach(DictionaryEntry<K,V*> & entry, c) {
            dict->put(entry.key, entry.value);
        }
    }
    void clear() {
        dict->clear()
    }
    bool contains(DictionaryEntry<K,V*> & t) {
        return Equals(dict->get(t.key),t.value);
    }
    bool containsAll(Collection<DictionaryEntry<K,V*> > & c) {
        sforeach(DictionaryEntry<K,V*> & entry, c) {
            if(!contains(entry)) return false;
        }
        return true;
    }
    bool operator ==(Collection<DictionaryEntry<K,V*> > & c) {
        sthrow(UnsupportedOperationException);
    }

    int hashCode() {
        // TODO!
        return 0;
    };
    bool empty() {
        return dict->empty();
    }
    bool remove(DictionaryEntry<K,V*> & t) {
        return dict->remove(t.key) != NULL;
    }
    bool removeAll(Collection<DictionaryEntry<K,V*> > & c) {
        sthrow(UnsupportedOperationException);
    }
    bool retainAll(Collection<DictionaryEntry<K,V*> > & c) {
        sthrow(UnsupportedOperationException);
    }
    std::size_t size() const {
        return dict->size();
    }
    const Array<DictionaryEntry<K,V*> > toArray() const {
        sthrow(UnsupportedOperationException);
    }

    Iterator<DictionaryEntry<K,V*> > iterator() const {
        return dict->entryIterator();
    }
    MutableIterator<DictionaryEntry<K,V*> > mutableIterator() {
        sthrow(UnsupportedOperationException);
    }
private:
    Dictionary * dict;
};




Dictionary::Dictionary(std::size_t initialCapacity, float loadFactor) {
    this->loadFactor = loadFactor;
    this->size = 0;
    this->threshold = initialCapacity * loadFactor;
    this->buckets = new Array<DictionaryEntry<Key, Value>*>(initialCapacity);
    for (int x = 0; x < buckets.length; x++) {
        buckets[x] = NULL;
    }
}

Dictionary::Dictionary(Dictionary<Key, Value, HashFunction> & orig) {
    this->loadFactor = orig.loadFactor;
    this->size = orig.size;
    this->threshold = orig.threshold;
    this->buckets = new Array<DictionaryEntry<Key, Value>*>(orig.buckets->length);
    arraycopy(*(orig.buckets), 0, *buckets, 0, orig.buckets->length);
}

Dictionary::~Dictionary() {
    delete this->buckets;
}

bool Dictionary::containsKey(Key & key) const {
    std::size_t idx = hash(key);
    DictionaryEntry<Key, Value> * entry = buckets[idx];
    while (entry != NULL) {
        if (Equals(key, entry->key)) return true;
        entry = entry->next;
    }
    return false;
}

bool Dictionary::containsValue(Value & value) const {
    for (std::size_t i = buckets.length - 1; i >= 0; i--) {
        DictionaryEntry<Key, Value> * entry = buckets[i];
        while (entry != NULL) {
            if (Equals(value, entry->value)) return true;
            entry = entry->next;
        }
    }
    return false;
}

const Collection<DictionaryEntry*> Dictionary::entrySet() {
    return DictClctEntries<Key,Value>;
}

std::size_t Dictionary::size() {
    return size;
}
_value * Dictionary::get(Key & key) {
    int h = hash(Key);
    DictionaryEntry<Key, Value> * entry = buckets[h];
    if (entry == NULL) return NULL;
    while (entry->next != NULL) {
        if (entry->key == key) return entry->value;
        entry = entry->next;
    }
    return NULL;
}

const _value * Dictionary::get(Key & key) const {
    int h = hash(Key);
    DictionaryEntry<Key, Value> * entry = buckets[h];
    if (entry == NULL) return NULL;
    while (entry->next != NULL) {
        if (entry->key == key) return entry->value;
        entry = entry->next;
    }
    return NULL;
}

DictionaryPointer<_key, _value> Dictionary::operator[](Key & key) {
    return DictionaryPointer<Key, Value > (key, this);
}

const DictionaryPointer<_key, _value> Dictionary::operator[](Key & key) const {
    return DictionaryPointer<Key, Value > (key, this);
}

bool Dictionary::empty() {
    return size() == 0;
}

const Collection<_key> Dictionary::keys() {
    return DictClctKeys<Key>(this);
}

const Collection<_value *> Dictionary::values() {
    return DictClctValues<Value*>(this);
}

_value * Dictionary::put(Key & key, Value & value) {
    int idx = hash(key);
    DictionaryEntry<Key, Value> entry = buckets[idx];

    while (entry != NULL) {
        if (Equals(key, entry->key)) {
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
    DictionaryEntry<Key, Value> newEnt = new DictionaryEntry<Key, Value > (key, value);
    newEnt.next = buckets[idx];
    buckets[idx] = newEnt;

    return NULL;
}

void Dictionary::putAll(Dictionary<Key, Value, HashFunction> & dict) {

    sforeach(DictionaryEntry de, dict.entrySet()) {
        this->put(de.key, de.value);
    }
}

_value * Dictionary::remove(Key & key) {
    std::size_t idx = hash(key);
    DictionaryEntry<Key, Value> * entry = buckets[idx];
    DictionaryEntry<Key, Value> * last = NULL;

    while (entry != NULL) {
        if (Equals(key, entry->key)) {
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

void Dictionary::clear() {
    delete buckets;

    threshold = loadFactor * 11;
    size = 0;
    buckets = new Array<DictionaryEntry<Key, Value>*>(11);

}

int Dictionary::hash(Key & key) {
    return key == NULL ? 0 : abs(hashf(key) % buckets.length)
}

void Dictionary::rehash() {
    Array<DictionaryEntry<Key, Value>*> * oldBuckets = buckets;

    int newcapacity = (buckets.length * 2) + 1;
    threshold = (int) (newcapacity * loadFactor);
    buckets = new Array<DictionaryEntry<Key, Value>*>(newcapacity);

    for (int i = oldBuckets.length - 1; i >= 0; i--) {
        DictionaryEntry<Key, Value>* entry = oldBuckets[i];
        while (entry != NULL) {
            int idx = hash(entry->key);
            DictionaryEntry<Key, Value>* next = entry->next;
            entry->next = buckets[idx];
            buckets[idx] = entry;
            entry = next;
        }
    }
}

template<class T>
DictionaryIterator<T, _key, _value *> Dictionary::iterator(DictionaryIteratorType type) {
    return DictionaryIterator<T, Key, Value > (*this, type);
}

DictionaryIterator<_key, _key, _value *> Dictionary::keyIterator() {
    return DictionaryIterator<Key, Key, Value > (*this, KEYS);
}

DictionaryIterator<_value *, _key, _value *> Dictionary::valueIterator() {
    return DictionaryIterator<Key, Key, Value > (*this, VALUES);
}

DictionaryIterator<DictionaryEntry *, _key, _value *> Dictionary::entryIterator() {
    return DictionaryIterator<Key, Key, Value > (*this, ENTRIES);

}

SYLPH_END_NAMESPACE
