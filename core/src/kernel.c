#define USE_IV_Overwrite_

#include "kernel.h"
#include "io.h"
#include "memory.h"
#include "stdlib.h"
//
static Kernel kernel;
//
void queue_pushback(PCB_Queue* queue, PCB** pcb) {
        (*pcb)->next = NULL;
        if (*pcb == NULL) {
                return;
        }
        if (queue->head != NULL) {
                queue->tail->next = *pcb;
        }
        else {
                queue->head = *pcb;
        }
        queue->tail = *pcb;
        *pcb        = NULL;
}
PCB* queue_frontpop(PCB_Queue* queue) {
        if (queue->head != NULL) {
                PCB* pcb    = queue->head;
                queue->head = queue->head->next;
                return pcb;
        }
        return NULL;
}
PCB* queue_fetch(PCB_Queue* queue, int pid) {
        PCB** cur = &queue->head;
        PCB*  c;
        PCB*  pre = NULL;
        while (*cur != NULL) {
                c = *cur;
                if (c->pid == pid) {
                        if (c == queue->tail) {
                                queue->tail = pre;
                        }
                        *cur = c->next;
                        return c;
                }
                pre = c;
                cur = &c->next;
        }
        return NULL;
}

void clk_handler() {
        schedule();
        kernel.clk++;
        if (cpu_entrance()->user_regs.br != NULL) {
                kernel.rr_time++;
                if (kernel.execute_p != NULL) {
                        kernel.execute_p->cpu_time++;
                }
        }
}

void io_handler() {
        for (unsigned int i = 0; i < IO_DEVICE_N; ++i) {
                unsigned int sel = 0x01 << i;
                if ((cpu_entrance()->io_bus & sel) == 0) {
                        continue;
                }
                int  pid = ioDevice_entrance(i)->pid;
                PCB* pcb = queue_fetch(&kernel.block_queue, pid);
                // WARNING: 正常情况下pcb不可能为NULL. 因为有IO中断请求, 说明阻塞队列有PCB
                pcb->state = READY;
                queue_pushback(&kernel.ready_queue, &pcb);
                if (kernel.execute_p == NULL) {
                        kernel.execute_p = queue_frontpop(&kernel.ready_queue);
                        kernel.rr_time   = 1;
                        context_write(&kernel.execute_p->regs,
                                      (Regs*)&cpu_entrance()->user_regs);
                }
        }
}

void int_handler() {
        unsigned char r0 = cpu_entrance()->user_regs.ur[0];
        unsigned char r1 = cpu_entrance()->user_regs.ur[1];
        PCB*          p  = kernel.execute_p;
        p->state         = WAITING;
        context_write(&cpu_entrance()->user_regs, &p->regs);
        if (r0 == 0) {
                // io等待
                io_post(r1, p->io_time_required, p->pid, &p->io_time);
                queue_pushback(&kernel.block_queue, &kernel.execute_p);
        }
        else if (r0 == 1) {
                // 程序退出
                pcb_free(&kernel.execute_p);
        }
        regs_reset();
        kernel.rr_time = RR_SLICE;  // int指令必定导致进程切换, rr时间片置0
        // schedule();
}

const Kernel* kernel_entrance() {
        return &kernel;
}

void system_init() {
        // 内核数据初始化
        cpu_init();
        io_init();
        memset(&kernel, 0, sizeof(Kernel));
        kernel.rr_time = RR_SLICE;
        // 覆写中断向量表
        IV_Overwrite(CLK, clk_handler);
        IV_Overwrite(IO, io_handler);
        IV_Overwrite(INT, int_handler);
}

void programload(Program program) {
        PCB* pcb = (PCB*)malloc(sizeof(PCB));
        memset(&pcb->regs, 0, sizeof(Regs));

        pcb->state            = READY;
        pcb->cpu_time         = 0;
        pcb->io_time          = 0;
        pcb->next             = NULL;
        pcb->regs.br          = program.as.p;
        pcb->regs.pc          = 0;
        pcb->pid              = pid_alloc();
        pcb->as               = program.as;
        pcb->io_time_required = program.io_time_required;
        queue_pushback(&kernel.ready_queue, &pcb);
}

void schedule() {
        // 时间片未到, 不进行调度
        if (kernel.rr_time < RR_SLICE) {
                return;
        }
        if (kernel.ready_queue.head == NULL) {
                // 就绪队列无进程
                return;
        }
        Regs* cpu_reg = (Regs*)&cpu_entrance()->user_regs;
        if (kernel.execute_p != NULL) {
                // 运行的PCB不为NULL
                // CPU中的上下文保存至PCB中
                context_write(cpu_reg, &kernel.execute_p->regs);
                kernel.execute_p->state = READY;
                // 运行的PCB移至就绪队列
                queue_pushback(&kernel.ready_queue, &kernel.execute_p);
        }
        // 时间片恢复
        kernel.rr_time = 0;
        // 就绪队列头部PCB移至CPU
        kernel.execute_p = queue_frontpop(&kernel.ready_queue);
        // PCB上下文写入CPU
        context_write(&kernel.execute_p->regs, cpu_reg);
        kernel.execute_p->state = RUNNING;
        // kernel.execute_p->cpu_time++;
}
// void run() {
//         cpu_run();
//         io_run();
// };