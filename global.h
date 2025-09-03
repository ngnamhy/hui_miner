//
// Created by hvmegy on 03/09/2025.
//

#ifndef GLOBAL_H
#define GLOBAL_H
#include <map>
#include <string>

namespace Global {
    extern std::map<int, double> item_utility;
    extern std::map<int, double> twu;
    extern int n_transactions;
    extern int n_items;
    extern double minutils;
    extern std::string dataset;
    extern std::string input_path;
}

#endif // GLOBAL_H
