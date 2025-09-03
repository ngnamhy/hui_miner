#ifndef INPUT_H
#define INPUT_H
#include <string>
#include "data/database.h"

class Input {
private:
    std::string hui_file;
    std::string pro_file;

public:
    Input();
    Database read_data();
};

#endif // INPUT_H