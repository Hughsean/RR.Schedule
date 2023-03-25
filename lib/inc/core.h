#ifndef A_C_LIB_CORE_H
#define A_C_LIB_CORE_H

#define IO_N        4   //
#define NET_DEVICE  1   //
#define DISK_DEVICE 1   //
#define USB_DEVICE  1   //
#define PID_MAX     32  //
#define REG_NUM     2   //
#define CPU_N       1   //
#define RR_SLICE    3   // RR时间片

// IO相关的定义
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

// 外部访问内核变量入口
const Kernel* kernel_entries();
// 内核变量初始化
void init();
// 系统关机
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
