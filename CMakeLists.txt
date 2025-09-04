cmake_minimum_required(VERSION 3.31)

# Set vcpkg toolchain before project()
set(CMAKE_TOOLCHAIN_FILE "D:\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Add vcpkg installed path
set(CMAKE_PREFIX_PATH "D:\\vcpkg\\installed\\x64-windows" ${CMAKE_PREFIX_PATH})

project(hui_miner1)

set(CMAKE_CXX_STANDARD 20)
#
# Find Boost with log and log_setup components
find_package(Boost REQUIRED COMPONENTS log log_setup thread filesystem date_time regex chrono atomic system)

# Add source files
add_executable(hui_miner1
        main.cpp
        tool/logger.cpp
        tool/logger.h
        data/utility_list.cpp
        data/utility_list.h
        data/transaction.h
        data/transaction.cpp
        data/database.cpp
        data/database.h
        tool/global.h
        tool/global.cpp
        tool/input.h
        tool/input.cpp
        algo/hui_miner.cpp
        algo/hui_miner.h
        data/utility_list_element.cpp
        data/utility_list_element.h
        data/itemset.cpp
        data/itemset.h
        tool/config_loader.cpp
        tool/config_loader.h
)

# Link Boost libraries
target_link_libraries(hui_miner1 PRIVATE Boost::log Boost::log_setup Boost::thread Boost::filesystem Boost::date_time Boost::regex Boost::chrono Boost::atomic Boost::system)
