#ifndef A_C_LIB_CORE_H
#define A_C_LIB_CORE_H
#include "datastruct.h"
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

// pid分配器
int pid_alloc();
// pid回收
void pid_free(int pid);

// 加载进程
void process_load(Process* pi, Priority pri);
// 释放进程
void process_free(PCB* pcb);
// 进程分配器
void dispatcher();
// 上下文切换器，无实际作用，占位函数
void context_switch(Regs* dect, Regs* src);
// cpu执行器
void cpu_processer();
// io执行器
void io_processer();
// RR调度
void RR();
#endif  // A_C_LIB_CORE_H
