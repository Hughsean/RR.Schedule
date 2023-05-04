//
// Created by xSeung on 2023/5/2.
//
#include "process_h.h"
#include "algorithm"
#include "fstream"
#include "iostream"
#include "json/json.h"

namespace fox {

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
                if (!Json::Reader().parse(infs, root)) {
                        std::cerr << "Json 解析失败" << std::endl;
                        abort();
                }
                for (auto iter = root.begin(); iter != root.end(); iter++) {
                        int  io_time_required = (*iter)["io_time_required"].asInt();
                        int  arrive_time      = (*iter)["arrive_time"].asInt();
                        auto p                = (*iter)["address_space"];
                        unsigned int  length  = p.size();
                        Address_Space as      = AddressSpace_alloc(length);
                        for (int i = 0; i < length; ++i) {
                                as.p[i] = p[i].asInt();
                        }
                        vec.push_back(Program{ .as               = as,
                                               .io_time_required = io_time_required,
                                               .arrive_time      = arrive_time });
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