//
// Created by hvmegy on 03/09/2025.
//

#include "utility_list.h"

#include "../tool/global.h"

utility_list::utility_list() {

}

utility_list::utility_list(int item) {
    this->last_item = item;
}

void utility_list::add(utility_list_element element) {
    this->elements.push_back(element);
    sum_rutils += element.rutils;
    sum_iutils += element.iutils;
}

utility_list join(utility_list& p, utility_list& px, utility_list& py) {
    Global::join_counts += 1;
    int p_index = 0;
    int py_index = 0;
    utility_list pxy = utility_list(py.last_item);
    for (utility_list_element xelement: px.elements) {
        while (py_index < py.elements.size() && py.elements[py_index].tid < xelement.tid) {
            py_index++;
        }
        if (py_index >= py.elements.size() || py.elements[py_index].tid > xelement.tid) {
            continue;
        }
        if (p.elements.empty()) {
            pxy.add(utility_list_element(xelement.tid, xelement.iutils + py.elements[py_index].iutils, py.elements[py_index].rutils));
        }
        else {
            while (p_index < p.elements.size() && p.elements[p_index].tid < xelement.tid) {
                p_index++;
            }
            if (p_index >= p.elements.size() || p.elements[p_index].tid > xelement.tid) {
                continue;
            }
            pxy.add(utility_list_element(xelement.tid, xelement.iutils + py.elements[py_index].iutils - p.elements[p_index].iutils, py.elements[py_index].rutils));
        }
    }
    return pxy;
}
