#define KB
extern "C" {
#include "core.h"
}
#include "helper.h"

#include "iostream"

int main() {
        init(get_kernel());
        //    clock_g();
        pid_alloc();
        pid_alloc();
        Process s{};
        PCB     p{ .pid = pid_alloc(), .prt = H, .pro = &s };
        PCB     q{ .pid = pid_alloc(), .pro = &s, .next = &p };

        show_pcblist(&q);
}