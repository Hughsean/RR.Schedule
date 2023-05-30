#include "config.h"
#include "fstream"
#include "interface.h"
#include "log.h"
#include "program_h.h"

auto main() -> int {
        try {
                int                       clock = 0;
                auto                      vec   = rr::programVec(PROGRAMESPATH "/programs.jsonc");
                std::vector<rr::logslice> dicts;
                std::ofstream             ofs(OUTPUTPATH "/out.json");
                system_init(&clock);
                while (true) {
                        // std::cin.get();
                        rr::programCommit(vec);
                        if (clock++ % CLK_TIME == 0) {
                                clk_irq();
                        }
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
