extern "C" {
#include "core.h"
}
#include "cstdlib"
#include "format"
#include "fstream"
#include "iostream"
#include "log.h"
#include "program_h.h"
#include "json/json.h"
auto main() -> int {
        try {
                int                       i   = 100;
                auto                      vec = rr::programVec(R"(d:\WorkSpace\RR.Schedule\test\programs.jsonc)");
                std::vector<rr::jsondict> dicts;
                std::ofstream             ofs(R"(d:\WorkSpace\RR.Schedule\test\out.json)");
                system_init();
                while (true) {
                        rr::programCommit(vec);
                        if (i % CLK_IRQ == 0) {
                                clk_irq();
                        }
                        dicts.emplace_back(rr::log(std::cout));
                        io_run();
                        cpu_run();
                        rr::urlog(std::cout);
                        if (rr::programFinish(vec)) {
                                break;
                        }
                }
                std::cout << rr::summary(vec) << std::endl;
                rr::jsonoutput(ofs, dicts);
        }
        catch (const std::exception& e) {
        }
}
