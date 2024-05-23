#include "SortedMap.h"
#include "SMIterator.h"
#include <exception>
#include <functional>
using namespace std;

#define INITIAL_CAPACITY 16

SortedMap::SortedMap(Relation r) : r(r), length(0), capacity(INITIAL_CAPACITY) {
    table.resize(capacity);
}

int SortedMap::hash(TKey key) const {
    return std::hash<TKey>()(key) % capacity;
}

void SortedMap::resize() {
    int new_capacity = capacity * 2;
    std::vector<std::list<TElem> > new_table(new_capacity);

    for (std::vector<std::list<TElem> >::iterator it = table.begin(); it != table.end(); ++it) {
        for (std::list<TElem>::iterator elem = it->begin(); elem != it->end(); ++elem) {
            int new_index = std::hash<TKey>()(elem->first) % new_capacity;
            new_table[new_index].push_back(*elem);
        }
    }

    table = std::move(new_table);
    capacity = new_capacity;
}

TValue SortedMap::add(TKey c, TValue v) {
    int index = hash(c);
    for (std::list<TElem>::iterator it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->first == c) {
            TValue old_value = it->second;
            it->second = v;
            return old_value;
        }
    }

    if (length + 1 > capacity * 0.75) {
        resize();
        index = hash(c);
    }

    table[index].push_back(make_pair(c, v));  // Use push_back instead of emplace_back
    length++;
    return NULL_TVALUE;
}

TValue SortedMap::search(TKey c) const {
    int index = hash(c);
    for (std::list<TElem>::const_iterator it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->first == c) {
            return it->second;
        }
    }
    return NULL_TVALUE;
}

TValue SortedMap::remove(TKey c) {
    int index = hash(c);
    for (std::list<TElem>::iterator it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->first == c) {
            TValue old_value = it->second;
            table[index].erase(it);
            length--;
            return old_value;
        }
    }
    return NULL_TVALUE;
}

int SortedMap::size() const {
    return length;
}

bool SortedMap::isEmpty() const {
    return length == 0;
}

SMIterator SortedMap::iterator() const {
    return SMIterator(*this);
}

SortedMap::~SortedMap() {
    // No explicit cleanup needed since we are using STL containers
}

std::vector<TKey> SortedMap::keySet() const {
    std::vector<TKey> keys;
    for (std::vector<std::list<TElem> >::const_iterator it = table.begin(); it != table.end(); ++it) {
        for (std::list<TElem>::const_iterator elem = it->begin(); elem != it->end(); ++elem) {
            keys.push_back(elem->first);
        }
    }
    return keys;
}
