//
// Created by xSeung on 2023/4/1.
//

#ifndef OS_CD_PROCESS_H
#define OS_CD_PROCESS_H

#include "cpu.h"

typedef enum state_ {
        RUNNING,  ///< 运行状态
        READY,    ///< 就绪状态
        WAITING,  ///< 阻塞状态
} PRO_STATE;

typedef struct address_space_ {
        unsigned int length;  // 程序长度
        int*         p;       // 程序静态代码数据,尚未装载进入内存
} Address_Space;

typedef struct program_ {
        Address_Space as;                ///< 程序的代码与数据
        int           io_time_required;  ///< 程序完成IO所需时间
        int           arrive_time;       ///< 程序到达系统时间
        char          name[NAME_LENGTH];
} Program, *Program_p;

typedef struct pcb_ {
        int           pid;                ///< 进程ID号
        int           cpu_time;           ///< 进程已运行时间
        int           io_time;            ///< io已运行时间
        int           io_time_required;   ///< 需要的io时间
        Regs          regs;               ///< 现场保护
        PRO_STATE     state;              ///< 进程状态
        Address_Space as;                 ///< 进程地址空间
        char          name[NAME_LENGTH];  ///< 程序名称
        struct pcb_*  next;               //
} PCB, *PCB_p;

int  pid_alloc();              // PID分配(不对外开放)
void pid_free(int pid);        // PID回收(不对外开放)
void pcb_free(PCB_p* pcbptr);  // PCB回收(不对外开放)
#endif                         // OS_CD_PROCESS_H
