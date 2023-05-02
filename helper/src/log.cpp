//
// Created by xSeung on 2023/5/2.
//
#include "log.h"
#include "core.h"
#include "format"
#include "map"
#include "tuple"
namespace fox {
        // DICT = {"mov": (0, 2), "movi": (1, 2), "add": (2, 3), "addi": (3, 3), "int":
        // (4, 0)}
        static std::map<int, std::tuple<std::string, int>> dict{ { 0, { "mov", 2 } },
                                                                 { 1, { "movi", 2 } },
                                                                 { 2, { "add", 3 } },
                                                                 { 3, { "addi", 3 } },
                                                                 { 4, { "int", 0 } } };

        Info infoFetch() {
                return Info{ .kernel    = kernel_entrance(),
                             .cpu       = cpu_entrance(),
                             .io_devide = ioDevice_entrance(0) };
        }

        void log(std::ostream& os) {
                Info info = infoFetch();
                auto s    = format(info);
                os << s;
        }

        std::string format(const Info& info) {
                std::string      inst    = translate(info);
                int              clk     = info.kernel->clk;
                int              rr_timr = info.kernel->rr_time;
                const PCB*       ep      = info.kernel->execute_p;
                const PCB_Queue  rq      = info.kernel->ready_queue;
                const PCB_Queue  bq      = info.kernel->block_queue;
                Regs             regs    = info.cpu->user_regs;
                int              io_bus  = info.cpu->io_bus;
                const IO_Device* iod     = info.io_devide;

                return std::format("CLK({:^4}) 指令:{}\n", clk, inst);
        }

        std::string translate(Info info) {
                auto br = (int*)info.cpu->user_regs.br;
                auto pc = info.cpu->user_regs.pc;
                if (br == nullptr) {
                        if (info.kernel->ready_queue.head == nullptr) {
                                return "NULL";
                        }
                        br = (int*)kernel_entrance()->ready_queue.head->regs.br;
                }
                int op        = br[pc];
                int r1        = br[pc + 1];
                int r2        = br[pc + 2];
                int r3        = br[pc + 3];
                auto [str, n] = dict.at(op);
                if (n == 2) {
                        str = std::format("{} {},{}", str, r1, r2);
                }
                if (n == 3) {
                        str = std::format("{} {},{},{}", str, r1, r2, r3);
                }
                return str;
        }

}  // namespace fox