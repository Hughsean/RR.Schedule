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

void IV_Rewritter(int id, void (*fun)()) {
        if (id >= IRQ_N) {
                return;
        }
        iv.fun[id] = fun;
}

void context_swap(Regs src, Regs tgt) {
        Regs tmp = src;
        src      = tgt;
        tgt      = tmp;
}