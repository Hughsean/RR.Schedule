//
// Created by xSeung on 2023/4/5.
//
#include "cpu.h"

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

void context_write(Regs *src, Regs *tgt) {
        *tgt = *src;
}
void io_irq(int did) {
        cpu.io_enable = did;
}

void cpu_run() {
        iv.fun[CLK]();
        if (cpu.io_enable != 0) {
                cpu.io_enable = 0;
                iv.fun[IO]();
        }
        if (cpu.user_regs.br == (void *)0) {
                return;
        }
        // 取指令
        Inst          inst = ((Inst *)cpu.user_regs.br)[cpu.user_regs.pc];
        unsigned char r1   = inst.r1;
        unsigned char r2   = inst.r2;
        unsigned char r3   = inst.r3;
        // 执行指令
        switch (inst.op) {
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
                cpu.user_regs.ur[0] = r1;
                cpu.user_regs.ur[1] = r2;
                iv.fun[INT]();
                break;
        }
}
