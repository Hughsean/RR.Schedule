#include "core.h"
#include "stdio.h"
// #include "helper.h"
#include "memory.h"
#include "signal.h"
#include "stdlib.h"
//
Kernel* kernel = NULL;

void    init(Kernel* k) {
    signal(SIGINT, power_off);
    signal(SIGTERM, power_off);

    kernel = (Kernel*)malloc(sizeof(Kernel));
    memset(kernel, 0, sizeof(Kernel));
    kernel->power = 1;
}
void power_off(int _) {
    kernel->power = 0;
}

void irq_signal(int signal) {
    printf("ss\n");
}

PCB* create_pcb(Process* pi) {
    PCB* p          = (PCB*)malloc(sizeof(PCB));

    p->pid          = ++kernel->PCB_N;
    p->pre          = NULL;
    p->next         = NULL;
    p->pro.time     = pi->time;
    p->pro.io_point = pi->io_point;
    p->pro.io       = pi->io;

    return p;
}

void RR() {}
