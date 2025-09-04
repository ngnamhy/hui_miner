#include "input.h"
#include <iostream>
#include "global.h"
#include "algo/hui_miner.h"
#include "tool/logger.h"

int main() {

    Input input;
    Database db = input.read_data();

    logger::init_logging();

    hui_miner hui_miner;
    hui_miner.prepAlgorithm(db, Global::minutils);


    for (itemset is : hui_miner.huis) {
        LOG(info) << is;
    }

    LOG(info) << "SIZE: " << hui_miner.huis.size() << std::endl;

    return 0;
}