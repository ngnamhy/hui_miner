#include "database.h"

#include <vector>
#include "transaction.h"

Database::Database(std::vector<Transaction> transactions): total_profit(0) {
    this->transactions = transactions;
    for (Transaction transaction: this->transactions) {
        total_profit += transaction.profit;
    }
}
