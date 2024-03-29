﻿//
// Created by xSeung on 2023/4/5.
//
#include "process.h"
#include "stdlib.h"

static unsigned char pid_map[PID_BITMAP_BYTE];
static int           pid_ = 0;

int pid_alloc() {
        unsigned char bitmask;
        int           row  = pid_ % 8;
        int           line = (pid_ / 8) % PID_BITMAP_BYTE;
        for (; line < PID_BITMAP_BYTE; ++line) {
                for (; row < 8; ++row) {
                        bitmask = 0x01 << row;
                        if ((pid_map[line] & bitmask) == 0) {
                                pid_map[line] = pid_map[line] | bitmask;
                                pid_          = (row + 8 * line) % (8 * PID_BITMAP_BYTE) + 1;
                                return pid_;
                        }
                }
        }
        abort();
}

void pid_free(int pid) {
        pid           = pid - 1;
        int row       = pid % 8;
        int line      = pid / 8;
        pid_map[line] = pid_map[line] & ~(0x01 << row);
}

void pcb_free(PCB_p* pcbptr) {
        pid_free((*pcbptr)->pid);
        free((*pcbptr)->as.p);
        free((*pcbptr));
        *pcbptr = NULL;
        regs_reset();
}