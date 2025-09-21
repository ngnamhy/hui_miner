
#include <chrono>
#include <iostream>
#include <windows.h>
#include <psapi.h>


#include "tool/config_loader.h"
#include "tool/input.h"
#include "tool/global.h"
#include "tool/logger.h"

#include "algo/fhm.h"
#include "algo/hui_miner.h"
#include "algo/efim.h"


SIZE_T getMemoryUsageMB() {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *) &pmc, sizeof(pmc));
    return pmc.WorkingSetSize / (1024 * 1024);
}

std::unique_ptr<hui_algo> createMiner(const std::string& algorithm) {
    if (algorithm == "fhm") {
        return std::make_unique<fhm>();
    }
    if (algorithm == "hui_miner") {
        return std::make_unique<hui_miner>();
    }
    if (algorithm == "efim") {
        return std::make_unique<efim>();
    }
    throw std::runtime_error("Unknown algorithm: " + algorithm);
}

int main() {
    Config::load_config("config.json");

    Input input;
    database db = input.read_data();

    logger::init_logging();

    auto start = std::chrono::high_resolution_clock::now();

    std::unique_ptr<hui_algo> miner;
    try {
        miner = createMiner(Global::algorithm); // Giả sử Global::algorithm lưu tên thuật toán từ JSON
    } catch (const std::runtime_error& e) {
        LOG(error) << e.what() << std::endl;
        return 1;
    }
    miner->work(db, Global::minutils_percentage);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);


    LOG(info) << "Algorithm: " << miner->name() << std::endl;
    LOG(info) << "Dataset: " << Global::dataset << std::endl;
    LOG(info) << "Minutils: " << Global::minutils << std::endl;
    LOG(info) << "Join counts: " << Global::join_counts << std::endl;
    LOG(info) << "Number of HUI: " << miner->huis.size() << std::endl;
    LOG(info) << "Runtime: " << duration.count() << " ms" << std::endl;
    LOG(info) << "Memory: " << getMemoryUsageMB() << " MB" << std::endl;


    return 0;
}
