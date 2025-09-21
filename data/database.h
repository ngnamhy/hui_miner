//
// Created by hvmegy on 03/09/2025.
//

#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include <string>

#include "transaction.h"

class database {
public:
    std::vector<transaction> transactions;
    double total_profit;

    std::string to_string();

    database(std::vector<transaction> transactions);
};

#endif //DATABASE_H
