//
// Created by hvmegy on 03/09/2025.
//

#ifndef GLOBAL_H
#define GLOBAL_H
#include <map>
#include <string>
#include <boost/log/trivial.hpp>

namespace Global {
    extern std::unordered_map<int, double> item_utility;
    extern std::map<int, double> twu;
    extern int n_transactions;
    extern int n_items;
    extern std::unordered_map<int, std::unordered_map<int, double>> eucs;

    extern double minutils_percentage;
    extern double minutils;
    extern int join_counts;

    extern std::string algorithm;
    extern std::string dataset;
    extern std::string input_path;

    extern boost::log::trivial::severity_level severity;
}

#endif // GLOBAL_H
