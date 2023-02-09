#include "core.h"
#include "memory.h"
#include "signal.h"
#include "stdio.h"
#include "stdlib.h"
//
static Kernel *kernel  = NULL;
static char   *pid_map = NULL;
//

Kernel *get_kernel() {
        return kernel;
}

void init(Kernel *k) {
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
        printf("ss\n");
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
        p->pid   = pid_alloc();
        p->pre   = NULL;
        p->next  = NULL;
        p->pro   = pi;
        p->state = READY;
        p->prt   = prt;
        return p;
}
void remove_pcb(PCB *pcb) {
        if (pcb->next != NULL) {}
        pid_free(pcb->pid);
        free(pcb->pro);
        free(pcb);
}

void RR() {}
