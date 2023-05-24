//
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
}
void io_irq(unsigned int did) {
        cpu.io_bus = cpu.io_bus | (0x01 << did);
}
void clk_irq() {
        cpu.clk_bus = 1;
}
void regs_reset() {
        memset(&cpu.user_regs, 0, sizeof(Regs));
}

void cpu_run() {
        if (cpu.clk_bus != 0) {
                iv.fun[CLK]();  // 响应时钟中断
                cpu.clk_bus = 0;
        }
        if (cpu.io_bus != 0) {
                iv.fun[IO]();
                cpu.io_bus = 0;
        }
        if (cpu.user_regs.br == (void *)0) {
                return;
        }

        int *br           = (int *)cpu.user_regs.br;
        int  pc           = cpu.user_regs.pc;
        int  op           = br[pc];
        int  r1           = br[pc + 1];
        int  r2           = br[pc + 2];
        int  r3           = br[pc + 3];
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
        default:
                break;
        }
}
void cpu_init() {
        memset(&cpu, 0, sizeof(CPU));
}
