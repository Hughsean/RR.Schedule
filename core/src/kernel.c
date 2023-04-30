#define USE_IV_Overwrite_

#include "kernel.h"
#include "io.h"
#include "memory.h"
#include "stdlib.h"
//
static Kernel kernel;
//
void queue_pushback(PCB_Queue queue, PCB* pcb) {
        pcb->next = NULL;
        if (pcb == NULL) {
                return;
        }
        if (queue.tail != NULL) {
                queue.tail->next = pcb;
        }
        else {
                queue.head = pcb;
        }
        queue.tail = queue.tail->next;
}
PCB* queue_frontpop(PCB_Queue queue) {
        if (queue.head != NULL) {
                PCB* pcb   = queue.head;
                queue.head = queue.head->next;
                return pcb;
        }
        return NULL;
}
PCB* queue_front(PCB_Queue queue) {
        return queue.head;
}

void clk_handler() {
        kernel.rr_time--;
        kernel.clk++;
        if (kernel.execute_p != NULL) {
                kernel.execute_p->run_time++;
        }
        RR();
}
void io_handler() {
        PCB* block   = queue_frontpop(kernel.block_queue);
        block->state = READY;
        queue_pushback(kernel.ready_queue, block);
}
void int_handler() {
        unsigned char r1 = cpu_entrance()->user_regs.ur[0];
        unsigned char r2 = cpu_entrance()->user_regs.ur[1];
        PCB*          p  = kernel.execute_p;
        p->state         = WAITING;

        if (r1 == 0) {
                // io等待
                io_push(r2, p->io_time, p->pid);
                queue_pushback(kernel.block_queue, kernel.execute_p);
        }
        else if (r1 == 1) {
                // 程序退出
                free(kernel.execute_p->as.p);
                free(kernel.execute_p);
                kernel.execute_p = NULL;
        }
        kernel.rr_time = 0;  // int指令必定导致进程切换, rr时间片置0
        RR();
}

const Kernel* kernel_entrance() {
        return &kernel;
}

void init() {
        // 内核数据初始化
        memset(&kernel, 0, sizeof(Kernel));
        // 覆写中断向量表
        IV_Overwrite(CLK, clk_handler);
        IV_Overwrite(IO, io_handler);
        IV_Overwrite(INT, int_handler);
}
void RR() {
        // 时间片未到, 不进行调度
        if (kernel.rr_time != 0) {
                return;
        }
        kernel.rr_time = RR_SLICE;
        if (kernel.ready_queue.head == NULL) {
                // 就绪队列无进程
                return;
        }
        if (kernel.execute_p != NULL) {
                Regs* cpu_reg = (Regs*)&cpu_entrance()->user_regs;
                // 运行的PCB不为NULL
                // CPU中的上下文保存至PCB中
                context_write(cpu_reg, &kernel.execute_p->regs);
                kernel.execute_p->state = READY;
                // 运行的PCB移至就绪队列
                queue_pushback(kernel.ready_queue, kernel.execute_p);
                // 就绪队列头部PCB移至CPU
                kernel.execute_p = queue_frontpop(kernel.ready_queue);
                // PCB上下文写入CPU
                context_write(&kernel.execute_p->regs, cpu_reg);
                kernel.execute_p->state = RUNNING;
        }
}
