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
        int       rr_time;      ///< 本轮RR算法已用时间
} Kernel, *Kernel_p;

void           clk_handler();                   // 时钟中断处理程序(不对外开放)
void           io_handler();                    // io中断处理程序(不对外开放)
void           int_handler();                   // 自陷指令服务程序(不对外开放)
const Kernel_p kernel_entrance();               // 内核数据访问函数(不对外开放)
void           system_init(int* clk_);          // 系统初始化
void           programload(Program_p program);  // 程序加载
void           schedule();                      // 调度程序(不对外开放)
#endif                                          // OS_CD_KERNEL_H
