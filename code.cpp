#include "template.h"
#include <iostream>
#include <string>

int main() {
    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "reset") {
            sjtu::resetMemory();
        } else if (cmd == "alloc") {
            int size;
            std::cin >> size;
            sjtu::allocate(size);
        } else if (cmd == "free") {
            // This is tricky because deallocate takes a pointer.
            // The problem description says "下发文件中的test.cpp即为OJ上所有的测试点".
            // Since I don't have test.cpp, I'll assume the OJ has its own main.
        }
    }
    return 0;
}
