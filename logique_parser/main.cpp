#include <iostream>

#include "driver.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage:" << std::endl;
        std::cout << "calc <filename>" << std::endl;
        return 1;
    }

    LogiqueParser::Driver cp;
    cp.parse(argv[1]);

    return 0;
}
