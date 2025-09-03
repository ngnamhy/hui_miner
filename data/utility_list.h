//
// Created by hvmegy on 03/09/2025.
//

#ifndef UTILITY_LIST_H
#define UTILITY_LIST_H
#include <vector>

#include "utility_list_element.h"


class utility_list {
public:
    int last_item;
    double sum_iutils = 0;
    double sum_rutils = 0;
    std::vector<utility_list_element> elements;

    utility_list();
    utility_list(int item);
    void add(utility_list_element);

    friend utility_list join(utility_list& p, utility_list& px, utility_list& py);
};



#endif //UTILITY_LIST_H
