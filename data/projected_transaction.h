//
// Created by hvmegy on 21/09/2025.
//

#ifndef PROJECTED_TRANSACTION_H
#define PROJECTED_TRANSACTION_H
#include "transaction.h"


class projected_transaction : public transaction {
public:


    int offset = 0;
    double prefix_utility = 0;
    double utility = 0;
    std::vector<std::pair<int, int>>& item_quantity_ref;
    double transaction_utility = 0;

    bool same_itemset(const projected_transaction & other);
    void merge(const projected_transaction & other);
    projected_transaction(projected_transaction previous, int offsetE);
    projected_transaction(transaction previous, int offsetE);


    projected_transaction(const projected_transaction &other)
    : transaction(other),
      offset(other.offset),
      prefix_utility(other.prefix_utility),
      utility(other.utility),
      item_quantity_ref(other.item_quantity_ref),
      transaction_utility(other.transaction_utility) {
    }

    projected_transaction(projected_transaction &&other) noexcept
        : transaction(std::move(other)),
          offset(other.offset),
          prefix_utility(other.prefix_utility),
          utility(other.utility),
          item_quantity_ref(other.item_quantity_ref),
          transaction_utility(other.transaction_utility) {
    }

    projected_transaction & operator=(const projected_transaction &other) {
        if (this == &other)
            return *this;
        transaction::operator =(other);
        offset = other.offset;
        prefix_utility = other.prefix_utility;
        utility = other.utility;
        item_quantity_ref = other.item_quantity_ref;
        transaction_utility = other.transaction_utility;
        return *this;
    }

    projected_transaction & operator=(projected_transaction &&other) noexcept {
        if (this == &other)
            return *this;
        transaction::operator =(std::move(other));
        offset = other.offset;
        prefix_utility = other.prefix_utility;
        utility = other.utility;
        item_quantity_ref = other.item_quantity_ref;
        transaction_utility = other.transaction_utility;
        return *this;
    }

};



#endif //PROJECTED_TRANSACTION_H
