//
// Created by xSeung on 2023/5/2.
//
#include "log.h"
#include "format"
#include "map"
#include "tuple"
#include "vector"
#include "json/json.h"
namespace rr {
        bool prefetchinst(const CPU* cpu, const Kernel* kernel) {
                if (cpu->user_regs.br == nullptr && kernel->ready_queue.head != nullptr) {
                        return true;
                }
                else if (kernel->rr_time >= RR_SLICE) {
                        if (kernel->ready_queue.head != nullptr) {
                                return true;
                        }
                }

                return false;
        }
        // io0: pid  io1: pid
        std::tuple<std::string, std::string> ioinfoextract(const IO_Device* iod) {
                std::string io[IO_DEVICE_N];
                for (int i = 0; i < IO_DEVICE_N; i++) {
                        auto        p   = iod[i].head;
                        std::string pid = "*";
                        if (p != nullptr) {
                                pid = std::to_string(p->pid);
                        }
                        io[i] = std::move(pid);
                }
                return std::make_tuple(std::move(io[0]), std::move(io[1]));
        }
        // DICT = {"mov": (0, 2), "movi": (1, 2), "add": (2, 3), "addi": (3, 3), "int":
        static std::map<int, std::tuple<std::string, int>> transdict{ { 0, { "mov", 2 } },
                                                                      { 1, { "movi", 2 } },
                                                                      { 2, { "add", 3 } },
                                                                      { 3, { "addi", 3 } },
                                                                      { 4, { "int", 0 } } };

        Info infoFetch() {
                return Info{ .kernel = kernel_entrance(), .cpu = cpu_entrance(), .io_devide = ioDevice_entrance(0) };
        }

        logslice log(std::ostream& os) {
                Info     info                                    = infoFetch();
                logslice slice                                   = infoextract(info);
                const auto& [clk, name, pid, inst, pc, io0, io1] = slice;
                os << std::format("clk({:4})  name: {:5}  pid: {:3}  inst: {:20}  pc: {:3}  io(0): {:3} io(1): {:3}",
                                  clk, name, pid, inst, pc, io0, io1);
                return slice;
        }
        void urlog(std::ostream& os) {
                std::string str{ " user_regs:" };
                for (auto&& e : cpu_entrance()->user_regs.ur) {
                        str.append(std::format(" {:3}", e));
                }
                str += '\n';
                os << str;
                os.flush();
        }

        logslice infoextract(const Info& info) {
                logslice         slice;
                int              clk     = info.kernel->clk;
                int              rr_timr = info.kernel->rr_time;
                const PCB*       ep      = info.kernel->execute_p;
                const PCB_Queue  rq      = info.kernel->ready_queue;
                const PCB_Queue  bq      = info.kernel->block_queue;
                const IO_Device* iod     = info.io_devide;
                Regs             regs    = info.cpu->user_regs;
                int              io_bus  = info.cpu->io_bus;
                auto             br      = info.cpu->user_regs.br;
                auto             pc      = info.cpu->user_regs.pc;
                std::string      inst    = "*";
                std::string      name    = ep == nullptr ? "*" : ep->name;
                int              pid     = 0;

                if (prefetchinst(info.cpu, info.kernel)) {
                        // 预先取指令
                        br   = rq.head->regs.br;
                        pc   = rq.head->regs.pc;
                        ep   = rq.head;
                        name = rq.head->name;
                }
                if (br != nullptr) {
                        // 指令存在
                        pid  = ep->pid;
                        inst = translate(br, pc);
                }
                auto [io0, io1] = ioinfoextract(iod);
                return std::make_tuple(clk, name, pid, inst, pc / 4, io0, io1);
        }

        std::string translate(void* p, int pc) {
                auto br       = (int*)p;
                int  op       = br[pc];
                int  r1       = br[pc + 1];
                int  r2       = br[pc + 2];
                int  r3       = br[pc + 3];
                auto [str, n] = transdict.at(op);
                if (n == 2) {
                        str = std::format("{:4} {:3},{:3}", str, r1, r2);
                }
                if (n == 3) {
                        str = std::format("{:4} {:3},{:3},{:3}", str, r1, r2, r3);
                }
                return str;
        }

        void jsonoutput(std::ostream& os, const std::vector<logslice>& slices) {
                Json::Value root;
                // clk name pid inst pc io(0) io(1)
                for (auto&& e : slices) {
                        Json::Value ee;
                        const auto& [clk, name, pid, inst, pc, io0, io1] = e;
                        ee["clk"]                                        = clk;
                        ee["name"]                                       = name;
                        ee["pid"]                                        = pid;
                        ee["inst"]                                       = inst;
                        ee["pc"]                                         = pc;
                        ee["io(0)"]                                      = io0;
                        ee["io(1)"]                                      = io1;
                        root.append(ee);
                }
                os << Json::FastWriter().write(root);
        }

}  // namespace rr