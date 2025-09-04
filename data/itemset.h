//
// Created by hvmegy on 03/09/2025.
//

#ifndef ITEMSET_H
#define ITEMSET_H
#include <iostream>
#include <set>


class itemset : public std::set<int> {
    friend std::ostream& operator<<(std::ostream& os, const itemset& is);
};



#endif //ITEMSET_H
