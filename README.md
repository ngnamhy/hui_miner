# HUI_MINER

---

An implementation of [HUI-Miner](https://www.philippe-fournier-viger.com/spmf/huiminer.pdf) algorithm in C++.

⚠️ This implementation is still under development.

---

## Overview
HUI-Miner is an algorithm for **High-Utility Itemset Mining (HUIM)**.  
Given a transaction database with items, quantities, and profits, it finds all itemsets whose total utility is greater than or equal to a given threshold (`minutil`).

This implementation:
- Uses **utility-lists** to avoid scanning the database multiple times.
- Supports configuration via external **JSON config**.
- Logs runtime and memory usage for benchmarking.

---

## Input Format
You will need two files with the same name but different extensions: `.hui` and `.pro`.

### `.hui` file
The `.hui` file contains the transactions with items and their quantities.

Format:
``` 
n m
transaction_id1 item_id1 quantity1
transaction_id2 item_id2 quantity2
transaction_id3 item_id3 quantity3
...
```

- `n` = number of transactions
- `m` = number of distinct items
- Each line after the header = `(transaction_id item_id quantity)`

### `.pro` file
The `.pro` file contains the profit of each item.

Format:

``` 
p1
p2
...
pm
```

## 🔧 Configuration
All runtime parameters are set in a `config.json` file.

Example `config.json`:
```json
{
  "input_path": "path/to/your/dataset",
  "dataset": "accidents",
  "minutils_percentage": 0.4,
  "severity": "debug"
}
