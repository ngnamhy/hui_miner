cmake_minimum_required(VERSION 3.31)
project(hui_miner1)

set(CMAKE_CXX_STANDARD 20)

add_executable(hui_miner1 main.cpp
        data/utility_list.cpp
        data/utility_list.h
        data/transaction.h
        data/transaction.cpp
        data/database.cpp
        data/database.h
        global.h
        global.cpp
        input.h
        input.cpp
        algo/hui_miner.cpp
        algo/hui_miner.h
        data/utility_list_element.cpp
        data/utility_list_element.h
        data/itemset.cpp
        data/itemset.h)
