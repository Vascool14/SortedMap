#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m) {
    // Collect all elements from the hash table into a vector
    for (vector<list<TElem> >::const_iterator bucketIt = map.table.begin(); bucketIt != map.table.end(); ++bucketIt) {
		for (list<TElem>::const_iterator elemIt = bucketIt->begin(); elemIt != bucketIt->end(); ++elemIt) {
			elements.push_back(*elemIt);
		}
	}
	
	// // Check if elements are sorted
	// std::cout << "Elements: " << std::endl;
	// for(const auto& element : elements) {
	// 	std::cout << element.first << " and " << element.second << std::endl;
	// }
    
    // Initialize the current index
    currentIndex = 0;
}

void SMIterator::first() {
    currentIndex = 0;
}

void SMIterator::next() {
    if (!valid()) {
        throw exception();
    }
    currentIndex++;
}

bool SMIterator::valid() const {
    return currentIndex < elements.size();
}

TElem SMIterator::getCurrent() const {
    if (!valid()) {
        throw exception();
    }
    return elements[currentIndex];
}