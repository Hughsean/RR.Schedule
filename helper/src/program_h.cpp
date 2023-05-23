//
// Created by xSeung on 2023/5/2.
//
#include "program_h.h"
#include "algorithm"
#include "fstream"
#include "iostream"
#include "json/json.h"

namespace rr {

        void programCommit(std::vector<Program> &vec) {
                while (true) {
                        if (vec.size() == 0) {
                                return;
                        }
                        if (vec.front().arrive_time == kernel_entrance()->clk) {
                                programload(vec.front());
                                vec.erase(vec.begin());
                        }
                        else {
                                break;
                        }
                }
        }
        std::vector<Program> programVec(const std::string &FilePath) {
                Json::Value          root;
                Json::Reader         reader;
                std::ifstream        infs(FilePath, std::ios::binary);
                std::vector<Program> vec;
                Program              program;
                if (!infs.good()) {
                        std::cerr << "文件未打开\n";
                        abort();
                }
                if (!Json::Reader().parse(infs, root)) {
                        std::cerr << "Json 解析失败\n";
                        abort();
                }
                for (auto iter = root.begin(); iter != root.end(); iter++) {
                        std::memset(&program, 0, sizeof(Program));
                        auto p                   = (*iter)["address_space"];
                        auto name                = (*iter)["name"].asString();
                        auto aslength            = p.size();
                        program.io_time_required = (*iter)["io_time_required"].asInt();
                        program.arrive_time      = (*iter)["arrive_time"].asInt();
                        program.as               = AddressSpace_alloc(aslength);
                        std::memcpy(program.name, name.c_str(), name.size());
                        for (int i = 0; i < aslength; ++i) {
                                program.as.p[i] = p[i].asInt();
                        }
                        vec.push_back(program);
                }
                std::sort(vec.begin(), vec.end(),
                          [&](const Program &l, const Program &r) {
                                  return l.arrive_time < r.arrive_time;
                          });
                return vec;
        }

        bool programFinish(const std::vector<Program> &vec) {
                auto p = kernel_entrance();
                return p->execute_p == nullptr && p->block_queue.head == nullptr
                       && p->ready_queue.head == nullptr && vec.size() == 0;
        }

}  // namespace fox