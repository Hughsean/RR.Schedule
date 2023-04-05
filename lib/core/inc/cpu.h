//
// Created by xSeung on 2023/4/5.
//

#ifndef OS_CD_CPU_H
#define OS_CD_CPU_H

typedef struct regs_ {
        void         *br;     // 基址地址寄存器
        unsigned int  pc;     // PC, 即相对基址偏移量
        unsigned char nr[8];  // 通用寄存器
} Regs;

typedef enum cpustate_ {
        USER,   // 用户态
        KERNEL  // 内核态
} CPU_STATE;

typedef struct cpu_ {
        Regs      regs;   // 寄存器组
        CPU_STATE state;  // CPU状态
} CPU;

const CPU *cpu_enteries();
void       context_swap(Regs src, Regs tgt);

#endif  // OS_CD_CPU_H
