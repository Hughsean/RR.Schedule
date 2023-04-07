//
// Created by xSeung on 2023/4/5.
//
#include "global_define.h"

static unsigned char pid_map[PID_MAX];

int pid_alloc() {
        unsigned char i = 1;
        unsigned char ii;

        for (int j = 0; j < PID_MAX; ++j) {
                for (int k = 0; k < 8; ++k) {
                        ii = i << k;
                        if ((pid_map[j] & ii) == 0) {
                                pid_map[j] = pid_map[j] | ii;
                                return k + 8 * j + 1;
                        }
                }
        }
        return 0;
}
void pid_free(int pid) {
        pid        = pid - 1;
        int r      = pid % 8;
        int l      = pid / 8;
        pid_map[l] = pid_map[l] & ~(1 << r);
}