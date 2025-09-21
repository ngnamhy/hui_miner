//
// Created by hvmegy on 18/09/2025.
//

#ifndef FHM_H
#define FHM_H
#include "hui_algo.h"
#include "../data/database.h"
#include "../data/itemset.h"
#include "../data/utility_list.h"


class fhm : public hui_algo {
public:

    void work(database &database, double minutils_percentage) override;
    void huimine(std::vector<int> & prefix, utility_list prefix_ul, const std::vector<utility_list> &uls);
    std::string name() const override { return "fhm"; }
};




#endif //FHM_H
