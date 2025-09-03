#include "global.h"

namespace Global {
    std::map<int, double> item_utility;
    std::map<int, double> twu;

    int n_transactions = 0;
    int n_items = 0;

    std::string dataset = "test";
    double minutils = 4.0;
    std::string input_path = "D:\\Code\\NCKH\\Dataset";
}