//
// Created by xSeung on 2023/4/1.
//

#ifndef OS_CD_PROCESS_H
#define OS_CD_PROCESS_H

#include "global_define.h"
#include "cpu.h"
typedef enum io_ { NO, NET, DISK, USB } IO;
typedef enum state_ { RUNNING, READY, WAITING, FB } STATE;
typedef enum priority_ { L, M, H } Priority;


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

// pid分配器
int pid_alloc();
// pid回收
void pid_free(int pid);


#endif  // OS_CD_PROCESS_H
