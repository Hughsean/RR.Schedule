//
// Created by xSeung on 2023/4/1.
//

#ifndef OS_CD_PROCESS_H
#define OS_CD_PROCESS_H

#include "cpu.h"
#include "global_define.h"

// typedef enum io_ { NO, NET, DISK, USB } IO;
typedef enum state_ {
        RUNNING,  // 运行状态
        READY,    // 就绪状态
        WAITING,  // 阻塞状态
} PRO_STATE;

// typedef enum priority_ {
//         L,  //
//         M,
//         H
// } Priority;

typedef struct address_space_ {
        unsigned int length;
        int*         p;
} Address_Space;

// typedef struct pi_ {
//         int time_need;  // 进程运行结束需要的时间
// } Process;

typedef struct pcb_ {
        int           pid;               // 进程ID号
        int           cpu_time;          // 进程已运行时间
        int           io_time;           // io已运行时间
        int           io_time_required;  // 需要的io时间
        Regs          regs;              // 现场保护
        PRO_STATE     state;             // 进程状态
        Address_Space as;                // 进程地址空间
        struct pcb_*  next;
        //        Process*      pro;       // 进程信息
        //        Priority      prt;          // 优先级
        //        struct pcb_* pre;
} PCB;

/// \brief 分配PID
int pid_alloc();
/// \brief 回收PID
/// \param pid 回收的PID
void pid_free(int pid);

#endif  // OS_CD_PROCESS_H
