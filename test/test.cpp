#define KB
extern "C" {
#include "core.h"
}

#include "iostream"

void fun0() {
        std::cout << "fun0\n";
}
void fun1() {}

int main() {
        init();
        //        kernel_entrance()->iv.fun[0]();

        std::cout << "1";
}