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
                auto                      vec = rr::programVec(R"(d:\WorkSpace\RR.Schedule\test\programs.jsonc)");
                std::vector<rr::logslice> dicts;
                std::ofstream             ofs(R"(d:\WorkSpace\RR.Schedule\test\out.json)");
                system_init();
                while (true) {
                        rr::programCommit(vec);
                        clk_irq();
                        // 每个周期开始前获取进程及IO信息
                        dicts.emplace_back(rr::log(std::cout));
                        io_run();
                        cpu_run();
                        // 必须在CPU运行后抓取寄存器值
                        rr::urlog(std::cout);
                        if (rr::programFinish(vec)) {
                                break;
                        }
                }
                rr::jsonoutput(ofs, dicts);
        }
        catch (const std::exception& e) {
                return 1;
        }
        return 0;
}
