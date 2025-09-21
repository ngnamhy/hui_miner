#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include "global.h"
#include "../data/database.h"
#include "input.h"


Input::Input() {
    // Tạo đường dẫn đến file .hui và .pro dựa trên dataset và input_path
    hui_file = Global::input_path + "\\" + Global::dataset + ".hui";
    pro_file = Global::input_path + "\\" + Global::dataset + ".pro";
}

// Đọc dữ liệu từ file .hui và .pro, trả về một Database
database Input::read_data() {
    // Đọc file .hui
    std::ifstream hui_stream(hui_file);
    if (!hui_stream.is_open()) {
        std::cerr << "Error: Cannot open file " << hui_file << std::endl;
        return database({});
    }

    // Đọc dòng đầu tiên: n (số transaction) và m (số item)
    int n, m;
    hui_stream >> n >> m;
    Global::n_transactions = n;
    Global::n_items = m;

    // Khởi tạo danh sách transactions
    std::vector<std::vector<std::pair<int, int> > > temp_transactions(n + 1); // transactions[1..n]
    int item_id, tid, quantity;
    while (hui_stream >> tid >> item_id >> quantity) {
        temp_transactions[tid].push_back({item_id, quantity});
        Global::item_utility[item_id] += quantity; // Cộng dồn quantity cho item_utility
    }
    hui_stream.close();

    // Đọc file .pro
    std::ifstream pro_stream(pro_file);
    if (!pro_stream.is_open()) {
        std::cerr << "Error: Cannot open file " << pro_file << std::endl;
        return {{}};
    }

    double profit;
    for (int i = 1; i <= m; ++i) {
        if (!(pro_stream >> profit)) {
            std::cerr << "Error: Invalid profit data in " << pro_file << std::endl;
            return {{}};
        }
        Global::item_utility[i] = profit;
    }

    pro_stream.close();

    // Chuyển đổi temp_transactions thành vector<Transaction>
    std::vector<transaction> transactions;
    for (int i = 1; i <= n; ++i) {
        if (!temp_transactions[i].empty()) {
            // Chỉ thêm transaction có item
            transactions.emplace_back(i, temp_transactions[i]);
        }
    }

    // Tạo và trả về Database
    return {transactions};
}
