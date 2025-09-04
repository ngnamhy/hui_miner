//
// Created by hvmegy on 03/09/2025.
//

#include "itemset.h"

std::ostream & operator<<(std::ostream &os, const itemset &is) {
    os << "[";
    for (auto i : is) {
        os << i << (i == *is.rbegin() ? "" : ", ");
    }
    os << "]";
    return os;
}
