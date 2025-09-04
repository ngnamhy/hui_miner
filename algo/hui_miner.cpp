//
// Created by hvmegy on 03/09/2025.
//

#include "hui_miner.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>

#include "../tool/global.h"
#include "../tool/logger.h"

void hui_miner::work(Database database, double minutils_percentage) {
    // first database scan to calculate twu for each item;

    double sum_tu = 0.0;
    for (Transaction &t: database.transactions) {
        double tu = 0;
        for (auto [k, v]: t.item_quantity) {
            tu += v * Global::item_utility[k];
        }
        sum_tu += tu;
        for (auto [k, v]: t.item_quantity) {
            Global::twu[k] += tu;
        }
    }

    double minutils = minutils_percentage * sum_tu;
    LOG(debug) << sum_tu << " " << minutils_percentage << std::endl;
    Global::minutils = minutils;

    std::vector<utility_list> high_twu_itemsets_uls;

    for (auto [k, v]: Global::twu) {
        if (v >= minutils) {
            high_twu_itemsets_uls.emplace_back(k);
        }
    }

    std::ranges::sort(high_twu_itemsets_uls, [&](const utility_list &i, const utility_list &j) {
        return Global::twu[i.last_item] < Global::twu[j.last_item];
    });
    std::map<int, int> map_item_to_index;
    for (int i = 0; i < high_twu_itemsets_uls.size(); ++i) {
        map_item_to_index[high_twu_itemsets_uls[i].last_item] = i;
    }

    for (Transaction &t: database.transactions) {
        std::ranges::sort(t.item_quantity, [&](const std::pair<int, int> i, const std::pair<int, int> j) {
            return Global::twu[i.first] < Global::twu[j.first];
        });
        double rutils = 0;
        for (int i = t.item_quantity.size() - 1; i >= 0; i--) {
            if (!map_item_to_index.contains(t.item_quantity[i].first)) { continue; }
            utility_list &ul = high_twu_itemsets_uls[map_item_to_index[t.item_quantity[i].first]];
            double iutils = t.item_quantity[i].second * Global::item_utility[t.item_quantity[i].first];
            ul.add(utility_list_element(t.id, iutils, rutils));
            rutils += iutils;
        }
    }

    auto prefix = std::vector<int>();
    huimine(prefix, utility_list(), high_twu_itemsets_uls);
}

itemset construct(const std::vector<int> &prefix, const int item) {
    auto result = itemset();
    for (int i: prefix) {
        result.insert(i);
    }
    result.insert(item);
    return result;
}

void hui_miner::huimine(std::vector<int> &prefix, utility_list prefix_ul, const std::vector<utility_list> &uls) {
    for (int i = 0; i < uls.size(); i++) {
        utility_list ulx = uls[i];
        if (ulx.sum_iutils >= Global::minutils) {
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
}
