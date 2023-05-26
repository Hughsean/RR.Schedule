//
// Created by xSeung on 2023/4/5.
//
#ifndef OS_CD_KERNEL_H
#define OS_CD_KERNEL_H
#include "cpu.h"
#include "io.h"
#include "process.h"

typedef struct pcb_queue_ {
        PCB* head;
        PCB* tail;
} PCB_Queue;

typedef struct kernel_ {
        PCB*      execute_p;    ///< 执行队列
        PCB_Queue ready_queue;  ///< 就绪队列
        PCB_Queue block_queue;  ///< 阻塞队列
        int       clk;          ///< 当前系统的用户周期
        int       rr_time;      ///< 本轮RR算法已用时间
} Kernel, *Kernel_p;

void           clk_handler();
void           io_handler();
void           int_handler();
const Kernel_p kernel_entrance();
void           system_init();
void           programload(Program_p program);
void           schedule();
#endif  // OS_CD_KERNEL_H
