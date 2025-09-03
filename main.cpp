#include "input.h"
#include <iostream>
#include "global.h"
#include "algo/hui_miner.h"

int main() {
    Input input;
    Database db = input.read_data();

    // for (Transaction t : db.transactions) {
    //     for (auto [k, v] : t.item_quantity) {
    //         std::cout << k << "," << v << " ";
    //     }
    //     std::cout << std::endl;
    // }
    std::cout << "Total profit: " << db.total_profit << std::endl;

    hui_miner hui_miner;
    hui_miner.prepAlgorithm(db, Global::minutils);

    for (itemset is: hui_miner.huis) {
        for (int i : is) {
            std::cout << i;
        }
        std::cout << std::endl;
    }

    std::cout << "SIZE: " << hui_miner.huis.size() << std::endl;
    return 0;
}
