#include "kernel.h"
#include "memory.h"
#include "signal.h"
#include "stdlib.h"
//
static Kernel kernel;
//
const Kernel *kernel_entries() {
        return &kernel;
}
void init() {
        // TODO
        //        signal(SIGTERM, power_off);
        //        signal(SIGINT, irq_handler);
        //        signal(SIGALRM, irq_handler);
        memset(&kernel, 0, sizeof(Kernel));
        kernel.power = 1;
}

void power_off(int _) {
        kernel.power = 0;
}

void irq_handler(int signal) {

        RR();
        cpu_processer();
        io_processer();
        // rr,cpu,io
        ++kernel.current_clock;
}

void process_load(Process *pi, Priority pri) {
        PCB *p         = (PCB *)malloc(sizeof(PCB));
        p->prt         = pri;
        p->pro         = pi;
        p->run_time    = 0;
        p->io_run_time = 0;
        p->state       = READY;
        p->next        = NULL;
        p->pid         = pid_alloc();
}
void process_free(PCB *pcb) {
        pid_free(pcb->pid);
        free(pcb->pro);
        free(pcb);
}
// void move_pcb(PCB *dest, PCB *src, int pos) {
//
// }

void dispatcher() {
        //
        //        PCB *p1  = (PCB *)malloc(sizeof(PCB));
        //        PCB *p2  = kernel->block_p;
        //        p1->next = kernel->block_p;
        //        while (1) {
        //                if (p2 == NULL) {
        //                        break;
        //                }
        //                if (p2->io_run_time == p2->pro->io) {
        //                        p1->next                = p2->next;
        //                        p2->next                = NULL;
        //                        kernel->ready_p_t->next = p2;
        //                        kernel->ready_p_t       = p2;
        //                        p2                      = p1->next;
        //                        continue;
        //                }
        //                p1 = p1->next;
        //                p2 = p2->next;
        //        }
        //
}

// void cpu_sched() {}
// void io_sched() {}
void cpu_processer() {
        //        PCB *p = kernel->execute_p;
        //        for (int i = 0; i < CPU_N; ++i) {
        //                if (p == NULL) {
        //                        break;
        //                }
        //                p->run_time++;
        //                p = p->next;
        //        }
}
void io_processer() {
        //        PCB *p    = kernel->block_p;
        //        int  net  = NET_DEVICE;
        //        int  disk = DISK_DEVICE;
        //        int  usb  = USB_DEVICE;
        //        while (1) {
        //                if (p == NULL) {
        //                        break;
        //                }
        //                if (net == 0 && disk == 0 && usb == 0) {
        //                        break;
        //                }
        //                switch (p->pro->io) {
        //                case NET:
        //                        net--;
        //                        break;
        //                case DISK:
        //                        disk--;
        //                        break;
        //                case USB:
        //                        usb--;
        //                        break;
        //                default:
        //                        break;
        //                }
        //                p->io_run_time++;
        //        }
}
void RR() {}
