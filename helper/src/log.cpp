//
// Created by xSeung on 2023/5/2.
//
#include "log.h"
#include "core.h"
#include "format"
#include "map"
#include "tuple"
#include "vector"
#include "json/json.h"
namespace rr {
        bool prefetchinst(const CPU* cpu, const Kernel* kernel) {
                /* code */
                if (cpu->user_regs.br == nullptr && kernel->ready_queue.head != nullptr) {
                        // if (kernel->ready_queue.head != nullptr) {
                        return true;
                        // }
                }
                else if (kernel->rr_time >= RR_SLICE) {
                        if (kernel->ready_queue.head != nullptr) {
                                return true;
                        }
                }

                return false;
        }
        void ioinfoextract(jsondict& dict, const IO_Device* iod) {
                for (int i = 0; i < IO_DEVICE_N; i++) {
                        auto        p   = iod[i].head;
                        std::string pid = "*";
                        if (p != nullptr) {
                                pid = std::to_string(p->pid);
                        }
                        dict.insert({ std::format("io({})", i), pid });
                }
        }
        // DICT = {"mov": (0, 2), "movi": (1, 2), "add": (2, 3), "addi": (3, 3), "int":
        static std::map<int, std::tuple<std::string, int>> transdict{ { 0, { "mov", 2 } },
                                                                      { 1, { "movi", 2 } },
                                                                      { 2, { "add", 3 } },
                                                                      { 3, { "addi", 3 } },
                                                                      { 4, { "int", 0 } } };

        std::string summary(const std::vector<Program>& vec) {
                std::string str;
                for (auto&& e : vec) {
                        str = std::format("{}程序名称:{:3} 到达时间:{:3} 指令个数:{:3} io时间:{:3}\n", str, e.name,
                                          e.arrive_time, e.as.length / 4, e.io_time_required);
                }
                return str;
        }

        Info infoFetch() {
                return Info{ .kernel = kernel_entrance(), .cpu = cpu_entrance(), .io_devide = ioDevice_entrance(0) };
        }

        jsondict log(std::ostream& os) {
                Info     info = infoFetch();
                jsondict dict = infoextract(info);
                os << std::format("clk({:4})  name: {:5}  pid: {:3}  inst: {:20}  pc: {:3}  "
                                  "io(0): {:3} io(1): {:3}",
                                  dict.at("clk"), dict.at("name"), dict.at("pid"), dict.at("inst"), dict.at("pc"),
                                  dict.at("io(0)"), dict.at("io(1)"));

                // os.flush();
                return dict;
        }
        void urlog(std::ostream& os) {
                std::string str{"   user_regs:"};
                for (auto&& e : cpu_entrance()->user_regs.ur) {
                        str.append(std::format(" {:3}", e));
                }
                str += '\n';
                os << str;
                os.flush();
        }

        jsondict infoextract(const Info& info) {
                jsondict         dict;
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
                std::string      pc_     = "*";
                int              pid     = 0;
                // const int(*ur)[REG_NUM]  = &regs.ur;

                if (prefetchinst(info.cpu, info.kernel)) {
                        // 预先取指令
                        br = rq.head->regs.br;
                        pc = rq.head->regs.pc;
                        // ur   = &rq.head->regs.ur;
                        ep   = rq.head;
                        name = rq.head->name;
                }
                if (br != nullptr) {
                        // 指令存在
                        pid  = ep->pid;
                        pc_  = std::to_string(pc / 4);
                        inst = translate(br, pc);
                        // ur   = &cpu_entrance()->user_regs.ur;
                }

                // std::string urstr;
                ioinfoextract(dict, iod);
                // for (auto&& e : *ur) {
                // urstr.append(std::format(" {:3}", std::to_string(e)));
                // }
                dict.insert({
                    { "clk", std::to_string(clk) },
                    { "pid", std::to_string(pid) },
                    { "inst", inst },
                    { "name", name },
                    { "pc", pc_ },
                    //       { "urstr", urstr }
                });
                return dict;
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

        void jsonoutput(std::ostream& os, const std::vector<jsondict>& dicts) {
                Json::Value root;
                // clk pid inst io(0) io(1)
                for (auto&& e : dicts) {
                        Json::Value ee;
                        ee["clk"]   = e.at("clk");
                        ee["name"]  = e.at("name");
                        ee["pid"]   = e.at("pid");
                        ee["inst"]  = e.at("inst");
                        ee["pc"]    = e.at("pc");
                        ee["io(0)"] = e.at("io(0)");
                        ee["io(1)"] = e.at("io(1)");
                        root.append(ee);
                }
                os << Json::FastWriter().write(root);
        }

}  // namespace rr