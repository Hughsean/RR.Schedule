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
        // DICT = {"mov": (0, 2), "movi": (1, 2), "add": (2, 3), "addi": (3, 3), "int":
        static std::map<int, std::tuple<std::string, int>> transdict{ { 0, { "mov", 2 } },
                                                                      { 1, { "movi", 2 } },
                                                                      { 2, { "add", 3 } },
                                                                      { 3, { "addi", 3 } },
                                                                      { 4, { "int", 0 } } };

        std::tuple<std::string, std::string> ioinfoextract() {
                std::string io[IO_DEVICE_N];
                for (int i = 0; i < IO_DEVICE_N; i++) {
                        std::string pidstr = "*";
                        auto        pid    = io_device_serves_pid(io_devive_at(i));
                        if (pid != -1) {
                                pidstr = std::to_string(pid);
                        }
                        io[i] = std::move(pidstr);
                }
                return std::make_tuple(std::move(io[0]), std::move(io[1]));
        }

        logslice log(std::ostream& os) {
                logslice slice                                   = infoextract();
                const auto& [clk, name, pid, inst, pc, io0, io1] = slice;
                os << std::format("clk({:4})  name: {:6}  pid: {:3}  inst: {:20}  pc: {:3}  io(0): {:3} io(1): {:3}",
                                  clk, name, pid, inst, pc, io0, io1);
                return slice;
        }
        void urlog(std::ostream& os) {
                std::string str{ " user_regs:" };
                auto        ur = cpu_ur();
                for (int i = 0; i < REG_NUM; i++) {
                        str.append(std::format(" {:3}", ur[i]));
                }
                str += '\n';
                os << str;
                os.flush();
        }

        logslice infoextract() {
                int   clk = kernel_uclk();
                int   pid = 0;
                int   pc;
                void* br;
                PCB_p pcb;
                predict(&pc, &br, &pcb);
                std::string name = "*";
                std::string inst = "*";
                if (pcb != nullptr) {
                        pid  = pcb_pid(pcb);
                        name = pcb_name(pcb);
                        inst = translate(br, pc);
                }
                auto [io0, io1] = ioinfoextract();
                // clk name pid inst pc io(0) io(1)
                return { clk, name, pid, inst, pc / 4, std::move(io0), std::move(io1) };
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