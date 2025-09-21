//
// Created by hvmegy on 21/09/2025.
//

#include "efim.h"

#include <optional>

#include "../data/projected_transaction.h"
#include "../tool/logger.h"
#include "../data/utility_list.h"

void efim::work(database &database, double minutils_percentage) {
    double sum_tu = 0.0;
    for (transaction &t: database.transactions) {
        double tu = 0;
        for (auto [k, v]: t.item_quantity) {
            tu += v * Global::item_utility[k];
        }
        sum_tu += tu;
        for (auto [k, v]: t.item_quantity) {
            local_utility[k] += tu;
        }
    }

    double minutils = minutils_percentage * sum_tu;
    Global::minutils = minutils;

    std::vector<int> secondary;

    for (auto [k, v]: local_utility) {
        if (v >= minutils) {
            secondary.emplace_back(k);
        }
    }

    std::ranges::sort(secondary, [&](const utility_list &i, const utility_list &j) {
        return local_utility[i.last_item] < local_utility[j.last_item];
    });
    std::unordered_map<int, int> map_item_to_index;
    for (int i = 0; i < secondary.size(); ++i) {
        map_item_to_index[secondary[i]] = i;
    }

    for (transaction &t: database.transactions) {
        std::ranges::sort(t.item_quantity, [&](const std::pair<int, int> i, const std::pair<int, int> j) {
            return local_utility[i.first] < local_utility[j.first];
        });
        double rutils = 0;
        for (int i = t.item_quantity.size() - 1; i >= 0; i--) {
            if (!map_item_to_index.contains(t.item_quantity[i].first)) { continue; }
            double iutils = t.item_quantity[i].second * Global::item_utility[t.item_quantity[i].first];
            rutils += iutils;
            subtree_utility[t.item_quantity[i].first] += rutils;
        }
    }

    std::vector<int> primary;
    for (int item : secondary) {
        if (subtree_utility[item] >= Global::minutils) {
            primary.push_back(item);
        }
    }

    std::vector<projected_transaction> projection;
    for (transaction t : database) {
        projection.push_back(projected_transaction(t, 0));
    }
    std::vector<int> prefix;
    efim::search(prefix, projection, primary, secondary);
}

void efim::search(std::vector<int> & prefix, std::vector<projected_transaction> projection, std::vector<int> & primary, std::vector<int> & secondary) {
    for (int i : primary) {
        double this_utility = 0;
        std::vector<projected_transaction> next_projection;
        std::optional<projected_transaction> previous_transaction;

        for (projected_transaction p : projection) {

            int lo = p.offset - 1;
            int hi = p.item_quantity_ref.size();
            double twuI = Global::twu[i];
            while (lo + 1 < hi) {
                int mi = (lo + hi) >> 1;
                double twuMi = Global::twu[p.item_quantity_ref[mi].first];
                if (twuMi >= twuI) {
                    hi = mi;
                }
                else {
                    lo = mi;
                }
            }
            if (hi < p.item_quantity_ref.size()) {
                if (hi == p.item_quantity_ref.size() - 1) {
                    this_utility += p.prefix_utility + p.item_quantity_ref[hi].second * Global::twu[p.item_quantity_ref[hi].first];
                }
                else {
                    this_utility += p.prefix_utility + p.item_quantity_ref[hi].second * Global::twu[p.item_quantity_ref[hi].first];
                    if (previous_transaction.has_value()) {
                        if (previous_transaction.value().same_itemset(p)) {
                            previous_transaction
                        }
                    }
                    else {
                        previous_transaction = std::optional<projected_transaction>(p);
                    }
                }
            }
        }
    }
}
