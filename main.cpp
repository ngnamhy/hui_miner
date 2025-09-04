#include <chrono>
#include <iostream>
#include <windows.h>
#include <psapi.h>


#include "tool/config_loader.h"
#include "tool/input.h"
#include "tool/global.h"
#include "algo/hui_miner.h"
#include "tool/logger.h"


SIZE_T getMemoryUsageMB() {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *) &pmc, sizeof(pmc));
    return pmc.WorkingSetSize / (1024 * 1024);
}

int main() {
    Config::load_config("config.json");

    Input input;
    Database db = input.read_data();

    logger::init_logging();

    auto start = std::chrono::high_resolution_clock::now();

    hui_miner hui_miner;
    hui_miner.work(db, Global::minutils_percentage);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    LOG(info) << "Dataset: " << Global::dataset << std::endl;
    LOG(info) << "Minutils: " << Global::minutils << std::endl;
    LOG(info) << "Number of HUI: " << hui_miner.huis.size() << std::endl;
    LOG(info) << "Runtime: " << duration.count() << " ms" << std::endl;
    LOG(info) << "Memory: " << getMemoryUsageMB() << " MB" << std::endl;


    return 0;
}
