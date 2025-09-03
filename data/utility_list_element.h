//
// Created by hvmegy on 03/09/2025.
//

#ifndef UTILITY_LIST_ELEMENT_H
#define UTILITY_LIST_ELEMENT_H
#include <iostream>


class utility_list_element {
public:
    int tid;
    double iutils = 0;
    double rutils = 0;

    utility_list_element(int tid, double iutils, double rutils);
    friend std::ostream &operator<<(std::ostream &os, const utility_list_element &utility);
};



#endif //UTILITY_LIST_ELEMENT_H
