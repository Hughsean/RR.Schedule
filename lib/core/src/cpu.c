//
// Created by xSeung on 2023/4/5.
//
#include "cpu.h"

static CPU cpu;

const CPU *cpu_enteries() {
        return &cpu;
}
void context_swap(Regs src, Regs tgt) {
        Regs tmp = src;
        src      = tgt;
        tgt      = tmp;
}