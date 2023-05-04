﻿//
// Created by xSeung on 2023/4/1.
//

#ifndef OS_CD_PROCESS_H
#define OS_CD_PROCESS_H

#include "cpu.h"
#include "global_define.h"

// typedef enum io_ { NO, NET, DISK, USB } IO;
typedef enum state_ {
        RUNNING,  ///< 运行状态
        READY,    ///< 就绪状态
        WAITING,  ///< 阻塞状态
} PRO_STATE;

typedef struct address_space_ {
        unsigned int length;
        int*         p;
} Address_Space;

typedef struct program_ {
        Address_Space as;                ///< 程序的代码与数据
        int           io_time_required;  ///< 程序完成IO所需时间
        int           arrive_time;       ///< 程序到达系统时间
        char          name[NAME_LENGTH];
} Program;

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
} PCB;

/// \brief 分配PID
int pid_alloc();
/// \brief 回收PID
/// \param pid 回收的PID
void          pid_free(int pid);
Address_Space AddressSpace_alloc(unsigned int length);
void          pcb_free(PCB** pcbptr);
#endif  // OS_CD_PROCESS_H
