#define USE_IV_Overwrite_

#include "kernel.h"
#include "memory.h"
#include "stdlib.h"
//
static Kernel kernel;
int*          clk;
//
void queue_pushback(PCB_Queue* queue, PCB_p* pcb) {
        if (*pcb == NULL) {
                return;
        }
        (*pcb)->next = NULL;
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
                pcb->next   = NULL;
                return pcb;
        }
        // Warning: 返回NULL就是出问题了, 不会向空队列取值
        return NULL;
}
PCB* queue_fetch(PCB_Queue* queue, int pid) {
        PCB_p* cur = &queue->head;
        PCB_p  pre = NULL;
        while (*cur != NULL) {
                if ((*cur)->pid == pid) {
                        if (*cur == queue->tail) {
                                queue->tail = pre;
                        }
                        PCB* ret  = *cur;
                        *cur      = (*cur)->next;
                        ret->next = NULL;
                        return ret;
                }
                pre = *cur;
                cur = &(*cur)->next;
        }
        // Warning: 返回NULL就是出问题了, 不会向空队列取值
        return NULL;
}

void clk_handler() {
        schedule();
        if (cpu_entrance()->user_regs.br != NULL) {
                if (cpu_entrance()->io_bus == 0) {
                        kernel.rr_time++;
                }
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
        }
}

void int_handler() {
        unsigned char r0 = cpu_entrance()->user_regs.ur[0];
        unsigned char r1 = cpu_entrance()->user_regs.ur[1];
        PCB_p         p  = kernel.execute_p;
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
        kernel.rr_time = RR_SLICE;  // int指令必定导致进程切换, 清除系统RR时间片
        *clk           = 0;         // 外部时钟重置
}

const Kernel_p kernel_entrance() {
        return &kernel;
}

void system_init(int* clk_) {
        // 内核数据初始化
        clk = clk_;
        cpu_init();
        io_init();
        memset(&kernel, 0, sizeof(Kernel));
        kernel.rr_time = RR_SLICE;
        // 覆写中断向量表
        IV_Overwrite(CLK, clk_handler);
        IV_Overwrite(IO, io_handler);
        IV_Overwrite(INT, int_handler);
}

void programload(Program_p program) {
        if (program == NULL) {
                abort();
        }
        PCB_p pcb = calloc(1, sizeof(PCB));
        pcb->as.p = calloc(program->as.length, sizeof(int));
        memcpy(pcb->name, program->name, NAME_LENGTH);
        memcpy(pcb->as.p, program->as.p, sizeof(int) * program->as.length);
        pcb->state            = READY;
        pcb->cpu_time         = 0;
        pcb->io_time          = 0;
        pcb->next             = NULL;
        pcb->pid              = pid_alloc();
        pcb->io_time_required = program->io_time_required;
        pcb->as.length        = program->as.length;
        pcb->regs.pc          = 0;
        pcb->regs.br          = pcb->as.p;
        queue_pushback(&kernel.ready_queue, &pcb);
        *clk = 0;
}

void schedule() {
        // 时间片未到||就绪队列无进程, 不进行调度
        if (kernel.rr_time < RR_SLICE || kernel.ready_queue.head == NULL) {
                return;
        }
        Regs_p cpu_reg = (Regs_p)&cpu_entrance()->user_regs;
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
}