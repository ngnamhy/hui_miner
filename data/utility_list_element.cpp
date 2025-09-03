//
// Created by hvmegy on 03/09/2025.
//

#include "utility_list_element.h"

utility_list_element::utility_list_element(int tid, double iutils, double rutils) {
    this->tid = tid;
    this->iutils = iutils;
    this->rutils = rutils;
}

std::ostream & operator<<(std::ostream &os, const utility_list_element &utility) {
    os << "<" << utility.tid << " " << utility.iutils << " " << utility.rutils << ">";
    return os;
}
