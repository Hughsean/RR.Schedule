//
// Created by xSeung on 2023/4/5.
//

#ifndef OS_CD_KERNEL_H
#define OS_CD_KERNEL_H

#include "process.h"

typedef struct pcb_queue_ {
        PCB* head;
        PCB* tail;
} PCB_Queue;

typedef struct kernel_ {
        PCB*      execute_p;       // 执行队列
        PCB_Queue ready_queue;     // 就绪队列
        PCB_Queue block_queue;     // IO阻塞队列
        PCB_Queue fallback_queue;  // 后备队列
        Regs regs;                 // 寄存器组
        int  current_clock;        // 当前系统周期
        int  power;                // 系统使能信号
        int  rr_time;              // 本轮RR算法，执行进程已用时间
} Kernel;

/**
 * 内核数据访问入口函数
 * @return 内核数据地址
 */
const Kernel* kernel_entries();
/**
 * 内核变量初始化
 */
void init();
/**
 * 系统关机处理函数
 * @param _ SIGNAL
 */
void power_off(int _);
// 硬件中断响应函数
void irq_handler(int signal);

// 加载进程
void process_load(Process* pi, Priority pri);
// 释放进程
void process_free(PCB* pcb);
// 进程分配器
void dispatcher();
// cpu执行器
void cpu_processer();
// io执行器
void io_processer();
// RR调度
void RR();

#endif  // OS_CD_KERNEL_H
