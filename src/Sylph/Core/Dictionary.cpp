#include "Util.h"

#include "Dictionary.h"
#include "Vector.h"
#include "Array.h"

#include <cmath>

SYLPH_START_NAMESPACE(Core)

template<class Key, class Value>
class DictionaryEntry : public Object {
public:

    DictionaryEntry(Key & _key, Value * _value) : key(_key), value(_value) {
    }

    virtual ~DictionaryEntry() {
    }

    DictionaryEntry<Key, Value> * next = NULL;
    Key key;
    Value * value;
};

template<class Key, class Value>
class DictionaryPointer : public Object {
    friend bool operator==(const DictionaryPointer & p, const Value & v);
    friend bool operator!=(const DictionaryPointer & p, const Value & v);
public:

    DictionaryPointer(Key & _key, Dictionary * _dict) :
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
    Dictionary * dict;
};

template<class Value>
bool operator==(const DictionaryPointer & p, const Value & v) {
    return Value(p) != NULL && Value(p) == v;
}

template<class Value>
bool operator!=(const DictionaryPointer & p, const Value & v) {
    return !(p == v);
}

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

virtual Dictionary::~Dictionary() {
    delete this->buckets;
}

void Dictionary::clear() {
    delete this->buckets;
    this->buckets = new new Array<DictionaryEntry<Key, Value>*>(11);
}

bool Dictionary::containsKey(Key & key) const {

}

bool Dictionary::containsValue(Value & value) const {

}

Vector<DictionaryEntry> Dictionary::entrySet() {

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

Vector<_key> Dictionary::keys() {

}

Vector<_value> Dictionary::values() {

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
        this->put(de.key,de.value);
    }
}

_value * Dictionary::remove(Key & key) {

}

void Dictionary::clear() {

}

int Dictionary::hash(Key & key) {
    return key == NULL ? 0 : abs(hashf(key) % buckets.length)
}

void Dictionary::rehash() {

}
SYLPH_END_NAMESPACE(Core)
