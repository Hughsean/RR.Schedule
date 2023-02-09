//// #define CLOCK

extern "C" {
#include "core.h"
#include "helper.h"
}

#include "iostream"

int main() {
    init(kernel);
    clock_g(irq_signal);
    std::cout << "POWER OFF\n";
    return 0;
}