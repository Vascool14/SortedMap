#pragma once
#include "SortedMap.h"
#include <vector>

// DO NOT CHANGE THIS PART
class SMIterator {
    friend class SortedMap;
private:
    const SortedMap& map;
    std::vector<TElem> elements;
    size_t currentIndex;
    
    SMIterator(const SortedMap& mapionar);

public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;
};