//
// Created by xSeung on 2023/4/5.
//
#ifndef OS_CD_KERNEL_H
#define OS_CD_KERNEL_H
#include "cpu.h"
#include "process.h"

typedef struct pcb_queue_ {
        PCB* head;
        PCB* tail;
} PCB_Queue;

typedef struct kernel_ {
        PCB*      execute_p;    // 执行队列
        PCB_Queue ready_queue;  // 就绪队列
        PCB_Queue block_queue;  // 阻塞队列
        int       clk;          // 当前系统的用户周期
        int       rr_time;      // 本轮RR算法剩余时间
        //        PCB_Queue block_queue;    // IO阻塞队列
} Kernel;

void clk_handler();
void io_handler();
void int_handler();
///\return 返回内核数据
const Kernel* kernel_entrance();
///\brief 内核初始化
void system_init();
void progressload(Address_Space as,int io_time_required);
void RR();
void run();
#endif  // OS_CD_KERNEL_H
