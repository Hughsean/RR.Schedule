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
                int                        i   = 100;
                auto                       vec = fox::programVec(R"(d:\WorkSpace\RR.Schedule\test\programs.jsonc)");
                std::vector<fox::jsondict> dicts;
                std::ofstream              ofs(R"(d:\WorkSpace\RR.Schedule\test\out.json)");
                std::cout << fox::summary(vec) << std::endl;
                system_init();
                while (true) {
                        fox::programCommit(vec);
                        if (i % CLK_IRQ == 0) {
                                clk_irq();
                        }
                        dicts.emplace_back(fox::log(std::cout));
                        io_run();
                        cpu_run();
                        if (fox::programFinish(vec)) {
                                break;
                        }
                }
                fox::jsonoutput(ofs, dicts);
        }
        catch (const std::exception& e) {
        }
}
