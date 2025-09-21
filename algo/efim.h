//
// Created by hvmegy on 21/09/2025.
//

#ifndef EFIM_H
#define EFIM_H

#include "hui_algo.h"
#include "../data/projected_transaction.h"

class efim : public hui_algo {
    std::unordered_map<int, double> local_utility;
    std::unordered_map<int, double> subtree_utility;

    void work(database &database, double minutils) override;
    void search(std::vector<int> & prefix, std::vector<projected_transaction> projection, std::vector<int> & primary, std::vector<int> & secondary);
    std::string name() const override { return "efim"; }
};



#endif //EFIM_H
