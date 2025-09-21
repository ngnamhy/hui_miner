#include "global.h"

namespace Global {
    // Variable
    std::unordered_map<int, double> item_utility;
    std::map<int, double> twu;

    // Input stat
    int n_transactions = 0;
    int n_items = 0;
    int join_counts = 0;

    std::unordered_map<int, std::unordered_map<int, double>> eucs;

    // Input configuration
    std::string algorithm;
    std::string input_path = "D:\\Code\\NCKH\\Dataset";
    std::string dataset = "accidents";
    double minutils_percentage = 40 / 100.0;
    double minutils;
    boost::log::trivial::severity_level severity = boost::log::trivial::debug;
}
