#include "database.h"

#include <vector>
#include "transaction.h"

std::string database::to_string() {
    std::string result = "\n";
    for (auto t : transactions) {
        result += t.to_string();
        if (&t != &transactions.back()) {
            result += "\n";
        }
    }
    return result;
}

database::database(std::vector<transaction> transactions): total_profit(0) {
    this->transactions = transactions;
    for (transaction transaction: this->transactions) {
        total_profit += transaction.profit;
    }
}
