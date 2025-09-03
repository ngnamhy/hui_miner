#include <map>

#include "../global.h"
#include "transaction.h"
#include "iostream"

Transaction::Transaction(int id, std::vector<std::pair<int, int>> item_quantity) {
    this->id = id; 
    this->item_quantity = item_quantity; 
    this->profit = 0.0; 
    for (auto [item, quantiy] : item_quantity) {
        this->profit += quantiy * Global::item_utility[item]; 
    }
}