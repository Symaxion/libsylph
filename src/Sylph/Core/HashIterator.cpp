#include "DictionaryIterator.h"

SYLPH_START_NAMESPACE(Core)

bool DictionaryIterator::hasNext() const {
    return count > 0;
}

const T & DictionaryIterator::next() const {
    if (count == 0) sthrow(ArrayException, "End of iterator, please all get off!");
    count--;
    DictionaryEntry<Key, Value> * entry = next;

    while (entry == NULL) {
        entry = dict->buckets[--idx];
    }

    next = entry->next;
    last = entry;
    if (type == VALUES) return (T) entry->value;
    else if (type == KEYS) return (T) entry->key;
    else return (T) entry;
}

bool DictionaryIterator::hasPrevious() const {
    sthrow(UnsupportedOperationException, "hasPrevious() not supported");
}

const T & DictionaryIterator::previous() const {
    sthrow(UnsupportedOperationException, "previous() not supported");
}

std::size_t DictionaryIterator::nextIndex() const {
    sthrow(UnsupportedOperationException, "nextIndex() not supported");
}

std::size_t DictionaryIterator::previousIndex() const {
    sthrow(UnsupportedOperationException, "previousIndex() not supported");
}
SYLPH_END_NAMESPACE(Core)