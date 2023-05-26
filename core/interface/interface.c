//
// Created by xSeung on 2023/5/26.
//
#include "interface.h"
#include "cpu.h"
#include "io.h"
#include "kernel.h"
#include "process.h"
#include "stdlib.h"
#include "string.h"

int kernel_uclk() {
        return kernel_entrance()->clk;
}

int nowork() {
        Kernel_p p = kernel_entrance();
        if (p->execute_p == NULL && p->block_queue.head == NULL && p->ready_queue.head == NULL) {
                return 1;
        };
        return 0;
}

void predict(int *pc, void **br, PCB_p *p) {
        *p               = NULL;
        *pc              = -1;
        *br              = NULL;
        const Kernel_p k = kernel_entrance();
        if (k->rr_time < RR_SLICE) {
                *p  = k->execute_p;
                *pc = cpu_entrance()->user_regs.pc;
                *br = cpu_entrance()->user_regs.br;
        }
        else if (k->ready_queue.head != NULL) {
                *p  = k->ready_queue.head;
                *pc = k->ready_queue.head->regs.pc;
                *br = k->ready_queue.head->regs.br;
        }
}

int pcb_pid(PCB_p p) {
        if (p == NULL) {
                abort();
        }
        return p->pid;
}

const char *pcb_name(PCB_p p) {
        if (p == NULL) {
                abort();
        }
        return p->name;
}

const IO_Device_p io_devive_at(int i) {
        return ioDevice_entrance(i);
}

int io_device_serves_pid(const IO_Device_p io) {
        if (io == NULL) {
                abort();
        }
        if (io->head != NULL) {
                return io->head->pid;
        }
        return -1;
}

Program_p program_alloc(const char *name, int name_len, int as_len, int *as, int iot, int at) {
        Program_p p         = calloc(1, sizeof(Program));
        p->as.p             = calloc(as_len, sizeof(int));
        p->as.length        = as_len;
        p->arrive_time      = at;
        p->io_time_required = iot;
        memcpy(p->name, name, sizeof(char) * name_len);
        memcpy(p->as.p, as, sizeof(int) * as_len);
        return p;
}

void program_free(Program_p p) {
        if (p == NULL) {
                abort();
        }
        free(p->as.p);
        free(p);
}

int program_at(Program_p p) {
        if (p == NULL) {
                abort();
        }
        return p->arrive_time;
}

const int *cpu_ur() {
        return cpu_entrance()->user_regs.ur;
}