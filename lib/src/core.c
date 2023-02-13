#include "core.h"
#include "memory.h"
#include "signal.h"
#include "stdio.h"
#include "stdlib.h"
//
static Kernel *kernel  = NULL;
static char   *pid_map = NULL;
// static Pro_t     NULL_CELL = { .is_null = 1 };
//

const Kernel *kernel_entries() {
        return kernel;
}
void init() {
        signal(SIGINT, power_off);
        signal(SIGTERM, power_off);
        signal(SIGALRM, irq_handler);

        kernel = (Kernel *)malloc(sizeof(Kernel));
        memset(kernel, 0, sizeof(Kernel));
        kernel->power = 1;

        pid_map = (char *)malloc(sizeof(char) * PID_MAX);
        memset(pid_map, 0, sizeof(char) * PID_MAX);
}
void power_off(int _) {
        kernel->power = 0;
}
void irq_handler(int signal) {
        // todo:先读内存，数据放入内核数据，再调用RR算法
        ++kernel->current_clock;
        printf("current_clock: %d\n", kernel->current_clock);
}
int pid_alloc() {
        for (int i = 0; i < PID_MAX; ++i) {
                if (pid_map[i] == 0) {
                        pid_map[i] = 1;
                        return i + 1;
                }
        }
        exit(1);
}
void pid_free(int pid) {
        pid_map[pid - 1] = 0;
}

PCB *create_pcb(Process *pi, Priority prt) {

        PCB *p      = (PCB *)malloc(sizeof(PCB));
        p->prt      = prt;
        p->pro      = pi;
        p->run_time = 0;
        p->state    = READY;
        p->next     = NULL;
        p->pid      = pid_alloc();
        return p;
}
void remove_pcb(PCB *pcb) {
        pid_free(pcb->pid);
        free(pcb->pro);
        free(pcb);
}
void move_pcb(PCB *dest, PCB *src, int pos) {
        if (pos == HEAD) {
                src->next = dest->next;
                dest      = src;
                return;
        }
        dest->next = src;
        dest       = src;
}

void context_switch(Regs *dect, Regs *src) {
        memcpy(dect, src, sizeof(Regs));
}
void dispatcher() {}
void cpu_sched() {}
void io_sched() {}
void RR() {}
