
#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include "../data/itemset.h" // Assuming itemset is defined here

inline itemset construct(const std::vector<int> &prefix, const int item) {
    auto result = itemset();
    for (int i : prefix) {
        result.insert(i);
    }
    result.insert(item);
    return result;
}

#endif // COMMON_H