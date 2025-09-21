//
// Created by hvmegy on 21/09/2025.
//

#include "projected_transaction.h"

#include "../tool/global.h"

projected_transaction::projected_transaction(projected_transaction previous, int offsetE): transaction(),
    item_quantity_ref(previous.item_quantity_ref) {

    double utilityE = this->item_quantity[offsetE].second * Global::item_utility[this->item_quantity[offsetE].first];

    this->prefix_utility = previous.prefix_utility + utilityE;

    this->transaction_utility = previous.transaction_utility;

    for (int i = previous.offset; i <= offsetE; i++) {
        this->transaction_utility -= this->item_quantity_ref[i].second * Global::item_utility[this->item_quantity[offsetE].first];
    }

    this->offset = offsetE + 1;
}

projected_transaction::projected_transaction(transaction previous, int offsetE): item_quantity_ref(previous.item_quantity) {
    this->item_quantity_ref = previous.item_quantity;

    double utilityE = this->item_quantity[offsetE].second * Global::item_utility[this->item_quantity[offsetE].first];

    this->prefix_utility = utilityE;
}

bool projected_transaction::same_itemset(const projected_transaction &other) {
    if (this->item_quantity_ref.size() != other.item_quantity_ref.size()) {
        return false;
    }
    for (auto i = 0; i < this->item_quantity_ref.size(); i++) {
        if (this->item_quantity_ref[i].first != other.item_quantity_ref[i].first) {
            return false;
        }
    }
    return true;
}

void projected_transaction::merge(const projected_transaction &other) {

}
