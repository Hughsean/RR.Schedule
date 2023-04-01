//
// Created by xSeung on 2023/4/1.
//

#ifndef OS_CD_DATASTRUCT_H
#define OS_CD_DATASTRUCT_H


#include "global_define.h"


typedef enum io_ { NO, NET, DISK, USB } IO;
typedef enum state_ { RUNNING, READY, WAITING, FB } STATE;
typedef enum priority_ { L, M, H } Priority;

typedef struct regs_ {
        long regs[REG_NUM];
} Regs;

typedef struct pi_ {
        int time_need;  // 进程运行结束需要的时间
        IO  io;         // 执行IO的种类
        int io_point;   // 执行IO的时间点
} Process;

typedef struct pcb_ {
        int          pid;          // 进程ID号
        Priority     prt;          // 优先级
        int          run_time;     // 进程已运行时间
        int          io_run_time;  // io已运行时间
        STATE        state;        // 进程状态
        Regs         regs;         // 现场保护
        Process*     pro;          // 进程信息
        struct pcb_* next;
        //        struct pcb_* pre;
} PCB;

typedef struct kernel_ {
        PCB* execute_p;      // 执行队列
        PCB* ready_p_h;      // 就绪队列
        PCB* ready_p_t;      //
                             // PCB* ready_p_tail;
                             // 就绪队列尾
        PCB* block_p;        // IO阻塞队列
        PCB* fallback_p;     // 后备队列
                             // PCB* block_p_tail;
                             // 阻塞队列尾
        Regs regs;           // 寄存器组
        int  current_clock;  // 当前系统周期
        int  power;          // 系统使能信号
        int  rr_time;        // 本轮RR算法，执行进程已用时间
} Kernel;

#endif  // OS_CD_DATASTRUCT_H
