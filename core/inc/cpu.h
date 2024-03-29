﻿//
// Created by xSeung on 2023/4/5.
//

#ifndef OS_CD_CPU_H
#define OS_CD_CPU_H
#include "config.h"

/*
 * op=0, mov : [r1]=[r2]
 * op=1, movi: [r1]=r2
 * op=2, add : [r1]=[r2]+[r3]
 * op=3, addi: [r1]=[r2]+r3
 * op=4, int : cpu.ur[0](r0)与cpu.ur[1](r1)传递参数, 调用iv[INT]中断函数.
 * r0=0:认为IO调用, 进程阻塞, 通过r1进行设备选择; r0=1: 认为进程退出
 */

typedef struct regs_ {
        void *br;           // 基址地址寄存器
        int   pc;           // PC, 即相对基址偏移量
        int   ur[REG_NUM];  // 通用寄存器
} Regs, *Regs_p;

enum { CLK, INT, IO };
/*
 * 中断向量表
 */
typedef struct iv_ {
        /*
         * 0: 时钟中断
         * 1: INT处理(软件中断)
         * 2: IO中断
         */
        void (*fun[IRQ_N])();
} Irq_Vector;

typedef struct cpu_ {
        Regs user_regs;  // 寄存器组
        int  io_bus;     // io中断信号及id
        int  clk_bus;    // 时钟中断信号
        int  clk;

} CPU, *CPU_p;

////////////////////////////////////
#ifdef USE_IV_Overwrite_
void IV_Overwrite(int id, void (*fun)());  // 覆写中断向量(仅对kernel.c开放)
#endif
void        context_write(const Regs *src, Regs *tgt);  // 寄存器覆写(不对外开放)
const CPU_p cpu_entrance();                             // CPU访问入口(不对外开放)
void        io_irq(unsigned int did);                   // 向CPU发出IO中断信号(不对外开放)
void        clk_irq();                                  // 向CPU发出时钟中断信号(不对外开放)
void        regs_reset();                               // 寄存器重置(不对外开放)
void        cpu_run();                                  // CPU运行一个时钟周期
void        cpu_init();                                 // CPU初始化(不对外开放)
#endif                                                  // OS_CD_CPU_H
