#include "core.h"
#include "helper.h"
#include "memory.h"

#include "stdlib.h"

Kernel* kernel = NULL;

void    init(Kernel* k) {
    kernel = (Kernel*)malloc(sizeof(Kernel));
    memset(kernel, 0, sizeof(Kernel));
    kernel->power = 1;
}

void irq_handler(int signal) {}

PCB* create_pcb(int pid, Process_info* pi) {
    PCB* p           = (PCB*)malloc(sizeof(PCB));

    p->pid           = pid;
    p->pre           = NULL;
    p->next          = NULL;
    p->info.time     = pi->time;
    p->info.io_point = pi->io_point;
    p->info.io       = pi->io;

    return p;
}

void RR(){}