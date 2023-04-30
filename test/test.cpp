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
        int p[50]{ 0 };
        for (int i = 0; i < 25; ++i) {
                p[i] = pid_alloc();
        }
        for (int i = 0; i < 15; ++i) {
                pid_free(p[i]);
                p[i] = -1;
        }
        for (int i = 25; i < 50; ++i) {
                p[i] = pid_alloc();
        }
        for (int i = 0; i < 50; ++i) {
                std::cout << p[i] << std::endl;
        }
}