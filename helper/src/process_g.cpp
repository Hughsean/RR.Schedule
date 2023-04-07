#define CLOCK_TIME 400000

extern "C" {
#include "core.h"
}
#include "helper.h"
#include "iostream"
#include "random"
//
#define PRO_MAX_TIME 20
#define PRO_MIN_TIME 5
//
Pro_d    *pro_pool = nullptr;
static IO io_[4]   = { NO, NET, DISK };
//

Process process_random_g() {
        static std::default_random_engine         e{ std::random_device{}() };
        static std::uniform_int_distribution<int> u{ 0, 1000 };

        Process p{
                .time_need = u(e) % (PRO_MAX_TIME - PRO_MIN_TIME) + PRO_MIN_TIME,
                .io        = io_[u(e) % IO_N],
        };
        if (p.io != NO) {

                p.io_point = u(e) % (p.time_need - PRO_MIN_TIME) + PRO_MIN_TIME;
        }
        else {
                p.io_point = -1;
        }

        return p;
}