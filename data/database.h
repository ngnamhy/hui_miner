//
// Created by hvmegy on 03/09/2025.
//

#ifndef DATABASE_H
#define DATABASE_H
#include <vector>

#include "transaction.h"

class Database {
public:
    std::vector<Transaction> transactions;
    double total_profit;

    Database(std::vector<Transaction> transactions);
};

#endif //DATABASE_H
