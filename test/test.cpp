#define KB
extern "C" {
#include "core.h"
}
#include "cstdlib"
#include "format"
#include "fstream"
#include "iostream"
#include "json/json.h"
auto main() -> int {
        Json::Value   root;
        std::ifstream infs(R"(D:\WorkSpace\OS.CD\test\test.json)", std::ios::binary);
        Json::Reader  reader;
        Address_Space as;
        int           io_time_required;
        if (reader.parse(infs, root)) {
                auto p           = root[0]["address_space"];
                io_time_required = root[0]["io_time_required"].asInt();
                as.length        = p.size();
                as.p             = (int *)malloc(sizeof(int) * as.length);
                int n            = 0;
                for (auto i = p.begin(); i != p.end(); i++) {
                        as.p[n] = i->asInt();
                        n++;
                }
        }
        system_init();
        progressload(as, io_time_required);
        PCB *pcb = kernel_entrance()->ready_queue.head;
        while (true) {
                run();
        }
}
