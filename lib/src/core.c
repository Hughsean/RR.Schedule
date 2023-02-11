#include "core.h"
#include "memory.h"
#include "signal.h"
#include "stdio.h"
#include "stdlib.h"
//
static Kernel   *kernel  = NULL;
static MM_Slice *mm      = NULL;
static char     *pid_map = NULL;
//
static MM_Slice NULL_CELL = { .is_null = 1 };

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

        mm = (MM_Slice *)malloc(sizeof(MM_Slice) * MM_SIZE);
        memset(mm, 0, sizeof(MM_Slice) * MM_SIZE);
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
        PCB *p   = (PCB *)malloc(sizeof(PCB));
        p->pre   = NULL;
        p->next  = NULL;
        p->pro   = pi;
        p->pid   = pid_alloc();
        p->prt   = prt;
        p->state = READY;
        return p;
}
void remove_pcb(PCB *pcb) {
        pid_free(pcb->pid);
        free(pcb->pro);
        free(pcb);
}
void pcb_link() {

}

void mm_write(MM_Slice ms, int pos) {
        if (pos >= MM_SIZE) {
                exit(1);
        }
        mm[pos] = ms;
}

MM_Slice mm_read(int pos) {
        if (pos >= MM_SIZE) {
                return NULL_CELL;
        }
        return mm[pos];
}

void load_regs(PCB *pcb) {
        memcpy(&kernel->regs, &pcb->regs, sizeof(Regs));
}
void store_regs(PCB *pcb) {
        memcpy(&pcb->regs, &kernel->regs, sizeof(Regs));
}

void RR() {}
