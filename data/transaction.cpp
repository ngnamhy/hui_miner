#include <map>

#include "../tool/global.h"
#include "transaction.h"
#include "iostream"

transaction::transaction(int id, std::vector<std::pair<int, int>> item_quantity) {
    this->id = id; 
    this->item_quantity = item_quantity; 
    this->profit = 0.0; 
    for (auto [item, quantiy] : item_quantity) {
        this->profit += quantiy * Global::item_utility[item]; 
    }
}

std::string transaction::to_string() {
    std::string result = "[";
    for (auto [item, quantiy] : item_quantity) {
        result += std::to_string(item) + "," + std::to_string(quantiy);
        if (item != item_quantity.back().first) {
            result += " ";
        };
    }
    return result + "]";
}