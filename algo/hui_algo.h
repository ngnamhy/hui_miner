//
// Created by hvmegy on 18/09/2025.
//
#pragma once
#include "../tool/global.h"
#include "../tool/input.h"
#include<set>
#include "../data/itemset.h"

class hui_algo {
public:
    virtual void work(database &db, double minutils_percentage) = 0;

    virtual std::string name() const = 0;

    virtual ~hui_algo() = default;

    std::set<itemset> huis;
};
