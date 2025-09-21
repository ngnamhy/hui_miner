//
// Created by hvmegy on 03/09/2025.
//

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <map>
#include <utility>
#include <vector>
#include <string>

class transaction {
public:
    std::vector<std::pair<int, int>> item_quantity;
    int id;
    double profit;

    std::string to_string();

    transaction() {}
    transaction(int id, std::vector<std::pair<int, int>> item_quantity);

};


#endif //TRANSACTION_H
