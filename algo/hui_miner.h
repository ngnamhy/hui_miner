//
// Created by hvmegy on 03/09/2025.
//

#ifndef HUI_MINER_H
#define HUI_MINER_H
#include "../data/database.h"
#include "../data/itemset.h"
#include "../data/utility_list.h"


class hui_miner {
public:
    std::set<itemset> huis;

    void prepAlgorithm(Database database, double minutils);
    void huimine(std::vector<int> & prefix, utility_list prefix_ul, std::vector<utility_list> uls);
};



#endif //HUI_MINER_H
