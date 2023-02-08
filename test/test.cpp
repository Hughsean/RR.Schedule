//#define CLOCK

extern "C" {
#include "core.h"
#include "helper.h"
}

int main() {
    init(kernel);
    clock_g(irq_handler);
    return 0;
}