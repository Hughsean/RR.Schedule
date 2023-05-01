﻿//
// Created by xSeung on 2023/4/5.
//
#include "cpu.h"
#include "memory.h"

static CPU        cpu;
static Irq_Vector iv;

const CPU *cpu_entrance() {
        return &cpu;
}

const Irq_Vector *IV_entrance() {
        return &iv;
}

void IV_Overwrite(int id, void (*fun)()) {
        if (id >= IRQ_N) {
                return;
        }
        iv.fun[id] = fun;
}

void context_write(const Regs *src, Regs *tgt) {
        *tgt = *src;
        //        memcpy(tgt, src, sizeof(Regs));
}
void io_irq(int did) {
        cpu.io_bus[did] = 1;
}
void regs_reset() {
        memset(&cpu.user_regs, 0, sizeof(Regs));
}

void cpu_run() {
        iv.fun[CLK]();                           // 先响应时钟中断
        for (int i = 0; i < IO_DEVICE_N; ++i) {  // 响应IO中断
                if (cpu.io_bus[i] != 0) {
                        iv.fun[IO]();
                        cpu.io_bus[0] = 0;  // 中断信号置0
                        cpu.io_bus[1] = 0;
                        break;
                }
        }
        if (cpu.user_regs.br == (void *)0) {
                return;
        }

        int *inst         = cpu.user_regs.br;
        int  pc           = cpu.user_regs.pc;
        int  op           = inst[pc];
        int  r1           = inst[pc + 1];
        int  r2           = inst[pc + 2];
        int  r3           = inst[pc + 3];
        cpu.user_regs.pc += 4;
        // 执行指令
        switch (op) {
        case 0:
                // op=0, mov : [r1]=[r2]
                cpu.user_regs.ur[r1] = cpu.user_regs.ur[r2];
                break;
        case 1:
                // op=1, movi: [r1]=r2
                cpu.user_regs.ur[r1] = r2;
                break;
        case 2:
                // op=2, add : [r1]=[r2]+[r3]
                cpu.user_regs.ur[r1] = cpu.user_regs.ur[r2] + cpu.user_regs.ur[r3];
                break;
        case 3:
                // op=3, addi: [r1]=[r2]+r3
                cpu.user_regs.ur[r1] = cpu.user_regs.ur[r2] + r3;
                break;
        case 4:
                //
                iv.fun[INT]();
                break;
        }
}
void cpu_init() {
        memset(&cpu, 0, sizeof(CPU));
}
