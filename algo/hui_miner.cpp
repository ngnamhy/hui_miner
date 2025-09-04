//
// Created by hvmegy on 03/09/2025.
//

#include "hui_miner.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>

#include "../global.h"
#include "../tool/logger.h"

void hui_miner::prepAlgorithm(Database database, double minutils) {
    // first database scan to calculate twu for each item;
    LOG(trace) << "Hello from hui_miner";
    for (Transaction &t : database.transactions) {
        double tu = 0;
        for (auto [k, v] : t.item_quantity) {
            tu += v * Global::item_utility[k];
        }
        for (auto [k, v] : t.item_quantity) {
            Global::twu[k] += tu;
        }
    }

    std::vector<utility_list> high_twu_itemsets;

    for (auto [k, v] : Global::twu) {
        if (v >= minutils) {
            high_twu_itemsets.push_back(utility_list(k));
        }
    }

    std::sort(high_twu_itemsets.begin(), high_twu_itemsets.end(), [&](utility_list i, utility_list j) {
        return Global::twu[i.last_item] < Global::twu[j.last_item];
    });
    std::map<int, int> map_item_to_index;
    for (int i = 0; i < high_twu_itemsets.size(); ++i) {
        map_item_to_index[high_twu_itemsets[i].last_item] = i;
    }

    for (Transaction &t : database.transactions) {
        std::sort(t.item_quantity.begin(), t.item_quantity.end(), [&](std::pair<int, int> i,  std::pair<int, int> j) {
            return Global::twu[i.first] < Global::twu[j.first];
        });
        double rutils = 0;
        for (int i = t.item_quantity.size() - 1; i >= 0; i--) {
            if (map_item_to_index.count(t.item_quantity[i].first) == 0) { continue; }
            utility_list& ul = high_twu_itemsets[map_item_to_index[t.item_quantity[i].first]];
            double iutils = t.item_quantity[i].second * Global::item_utility[t.item_quantity[i].first];
            ul.add(utility_list_element(t.id, iutils, rutils));
            rutils += iutils;
        }
    }

    // for (auto i : high_twu_itemsets) {
    //     std::cout << i.last_item << " " << i.sum_iutils << std::endl;
    //     for (auto j : i.elements) {
    //         std::cout << j << std::endl;
    //     }
    // }

    // std::cout << "START MINING " << std::endl;

    std::vector<int> prefix = std::vector<int>();
    huimine(prefix, utility_list(), high_twu_itemsets);
}

itemset construct(std::vector<int> & prefix, int item) {
    itemset result = itemset();
    std::string str = "";
    for (int i : prefix) {
        result.insert(i);
        str += std::to_string(i);
    }
    result.insert(item);
    str += std::to_string(item);
    // std::cout << "FOUND HUI: " << str << std::endl;
    return result;
}

void hui_miner::huimine(std::vector<int> & prefix, utility_list prefix_ul, std::vector<utility_list> uls) {
    // if (prefix.size()) {
    //     std::cout << prefix.back() << std::endl;
    // }
    // else {
    //     std::cout << "{}" << std::endl;
    // }
    for (int i = 0; i < uls.size(); i++) {
        utility_list ulx = uls[i];
        if (ulx.sum_iutils >= Global::minutils) {
            // std::cout << "FOUND: " << ulx.last_item << " " << ulx.sum_iutils << std::endl;
            this->huis.insert(construct(prefix, ulx.last_item));
        }
        if (ulx.sum_iutils + ulx.sum_rutils < Global::minutils) {
            continue;
        }

        std::vector<utility_list> next_ul;

        for (int j = i + 1; j < uls.size(); j++) {
            utility_list uly = uls[j];
            next_ul.push_back(join(prefix_ul, ulx, uly));
        }

        prefix.push_back(ulx.last_item);
        huimine(prefix, ulx, next_ul);
        prefix.pop_back();
    }
    // std::cout << "back" << std::endl;
}
