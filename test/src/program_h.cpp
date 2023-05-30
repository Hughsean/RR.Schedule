//
// Created by xSeung on 2023/5/2.
//
#include "program_h.h"
#include "algorithm"
#include "fstream"
#include "iostream"
#include "json/json.h"

namespace rr {

        void programCommit(std::vector<Program_p> &vec) {
                while (true) {
                        if (vec.size() == 0) {
                                return;
                        }
                        if (program_at(vec.front()) == cpu_clk()) {
                                programload(vec.front());
                                program_free(vec.front());
                                vec.erase(vec.begin());
                        }
                        else {
                                break;
                        }
                }
        }
        std::vector<Program_p> programVec(const std::string &FilePath) {
                Json::Value            root;
                Json::Reader           reader;
                std::ifstream          infs(FilePath, std::ios::binary);
                std::vector<Program_p> vec;
                if (!infs.good()) {
                        std::cerr << "文件未打开\n";
                        abort();
                }
                if (!Json::Reader().parse(infs, root)) {
                        std::cerr << "Json 解析失败\n";
                        abort();
                }
                for (auto iter = root.begin(); iter != root.end(); iter++) {
                        auto p                = (*iter)["address_space"];
                        auto name             = (*iter)["name"].asString();
                        auto aslength         = p.size();
                        auto io_time_required = (*iter)["io_time_required"].asInt();
                        auto arrive_time      = (*iter)["arrive_time"].asInt();
                        int *as               = new int[aslength];
                        for (int i = 0; i < aslength; ++i) {
                                as[i] = p[i].asInt();
                        }
                        vec.push_back(program_alloc(name.c_str(), (int)name.size(), (int)aslength, as, io_time_required,
                                                    arrive_time));
                        delete[] as;
                }
                std::sort(vec.begin(), vec.end(),
                          [&](const Program_p &l, const Program_p &r) { return program_at(l) < program_at(r); });
                return vec;
        }

        bool programFinish(const std::vector<Program_p> &vec) {
                return finish() == 1 && vec.size() == 0;
        }

}  // namespace rr