#include "global.h"

namespace Global {
    // Variable
    std::map<int, double> item_utility;
    std::map<int, double> twu;

    // Input stat
    int n_transactions = 0;
    int n_items = 0;

    // Input configuration
    std::string input_path = "D:\\Code\\NCKH\\Dataset";
    std::string dataset = "test";
    double minutils = 4.0;

}