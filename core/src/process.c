//
// Created by xSeung on 2023/4/5.
//
#include "global_define.h"

static unsigned char pid_map[PID_BITMAP_BYTE];

int pid_alloc() {
        unsigned char bitmask;
        for (int line = 0; line < PID_BITMAP_BYTE; ++line) {
                for (int row = 0; row < 8; ++row) {
                        bitmask = 0x01 << row;
                        if ((pid_map[line] & bitmask) == 0) {
                                pid_map[line] = pid_map[line] | bitmask;
                                return row + 8 * line + 1;
                        }
                }
        }
        return -1;
}

void pid_free(int pid) {
        pid           = pid - 1;
        int row       = pid % 8;
        int line      = pid / 8;
        pid_map[line] = pid_map[line] & ~(1 << row);
}