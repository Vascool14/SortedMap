#pragma once
// DO NOT INCLUDE SORTEDMAPITERATOR

// DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
#include <utility>
#include <vector>
#include <list>
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TPAIR std::pair<TKey, TValue>(-111111, -111111);
class SMIterator;
typedef bool(*Relation)(TKey, TKey);

class SortedMap {
    friend class SMIterator;
private:
    std::vector<std::list<TElem> > table; // Vector of lists for separate chaining

	// Relation object
    Relation r; 

	// Length of the map
    int length;

	// Capacity of the map
    int capacity;

	// hash function
    int hash(TKey key) const;

	// resize function
    void resize();

public:
    // implicit constructor
    SortedMap(Relation r);

    // adds a pair (key,value) to the map
    // if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
    // if the key does not exist, a new pair is added and the value null is returned
    TValue add(TKey c, TValue v);

    // searches for the key and returns the value associated with the key if the map contains the key or null: NULL_TVALUE otherwise
    TValue search(TKey c) const;

    // removes a key from the map and returns the value associated with the key if the key existed or null: NULL_TVALUE otherwise
    TValue remove(TKey c);

    // returns the number of pairs (key,value) from the map
    int size() const;

    // checks whether the map is empty or not
    bool isEmpty() const;

    // return the iterator for the map
    // the iterator will return the keys following the order given by the relation
    SMIterator iterator() const;

    // destructor
    ~SortedMap();

    // returns a vector with all the keys from the sortedmap
    std::vector<TKey> keySet() const;
};
