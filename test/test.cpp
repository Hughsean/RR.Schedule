extern "C" {
#include "core.h"
}
#include "cstdlib"
#include "format"
#include "fstream"
#include "iostream"
#include "log.h"
#include "process_h.h"
#include "json/json.h"
auto main() -> int {
        auto vec = fox::programVec(R"(D:\WorkSpace\OS.CD\test\programs.jsonc)");
        for (auto &&i : vec) {
                std::cout << std::format("len {}; arr{}; req{}; insts:{}\n", i.as.length,
                                         i.arrive_time, i.io_time_required,
                                         i.as.length / 4);
        }
        int i = 100;
        system_init();
        while (true) {
                fox::programCommit(vec);
                fox::log(std::cout);
                run();
                if (--i == 0) {
                        break;
                        ;
                }
        }
}
