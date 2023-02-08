#ifndef A_C_LIB_CORE_H
#define A_C_LIB_CORE_H
#define RR_SLICE         3  // RR时间片
#define min_procrss_time 1
#define max_process_time 9
#define name_length      32  // 进程名称长度
#define REG_NUM          16
#define n_cpu            1

// IO相关的定义
enum IO { NO = 0, NET = 2, DISK = 3, USB = 4 };

enum STATE { READY, RUNNING, WAITING };

struct Stack {
    long regs[REG_NUM];
};

struct Process_info {
    int     slices;    // 进程的时间片
    enum IO io;        // 执行IO的种类
    int     io_point;  // 执行IO的时间点
};

struct PCB {
    char         name[name_length];  // 进程名称
    int          pid;                // 进程ID号
    struct Stack stack;              // 数据保护存储堆栈
    enum STATE   state;              // 进程状态
    struct PCB*  next;
    struct PCB*  pre;
};

struct Kernel {
    struct PCB* execute_p;
};

void irq_handler(int signal);

// int  irq_generator();//时钟

// void RR();
#endif  // A_C_LIB_CORE_H
#include "stdio.h"

void irq_handler(int signal) {
    printf("%d\n", signal);
}
//
// Created by x-seung on 23-2-3.
//

#ifndef A_C_LIB_HELPER_H
#define A_C_LIB_HELPER_H
void aclock();

#endif  // A_C_LIB_HELPER_H

#include "signal.h"
#include "sys/time.h"
#include <unistd.h>
void aclock() {
    struct sigaction act;
    act.sa_handler = irq_handler;

    struct itimerval t;
    //    {
    //        { RR_SLICE, 0 }, {
    //            0, 0
    //        }
    //    };
    t.it_interval.tv_sec  = RR_SLICE;
    t.it_interval.tv_usec = 0;
    t.it_value.tv_sec     = 0;
    t.it_value.tv_usec    = 50;

    sigaction(SIGALRM, &act, 0);
    setitimer(ITIMER_REAL, &t, 0);

    while (1) {
        pause();
    }
}

int main() {
    aclock();
}