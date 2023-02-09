#ifndef A_C_LIB_CORE_H
#define A_C_LIB_CORE_H

#define min_procrss_time 1  //
#define max_process_time 9  //
#define IO_N             4

// #define Name_length      32  // 进程名称长度
#define REG_NUM          16  //
#define n_cpu            1   //
#define RR_SLICE         1   // RR时间片

// IO相关的定义
typedef enum io_ { NO, NET, DISK, USB } IO;

typedef enum state_ { READY, RUNNING, WAITING } STATE;

typedef struct regs_ {
    long regs[REG_NUM];
} Regs;

typedef struct pi_ {
    //    char  name[Name_length];  // 进程名称
    int   run_time;  // 进程运行时间
    int   time;      // 进程运行结束需要的时间
    IO    io;        // 执行IO的种类
    int   io_point;  // 执行IO的时间点
    STATE state;     // 进程状态
} Process;

typedef struct pcb_ {
    int         pid;   // 进程ID号
    Regs        regs;  // 现场保护
    Process     pro;   // 进程信息
    struct pcb* next;
    struct pcb* pre;
} PCB;

typedef struct kernel_ {
    PCB* execute_p;      // 执行队列
    PCB* ready_p;        // 就绪队列
    PCB* block_p;        // 阻塞队列
    Regs regs;           // 寄存器组
    int  current_clock;  // 当前系统周期
    int  power;          // 系统使能信号
    int  PCB_N;          // 分配PID
} Kernel;

void           init(Kernel* k);
void           power_off(int _);

void           irq_signal(int signal);
PCB*           create_pcb(Process* pi);
void           RR();

extern Kernel* kernel;

#endif  // A_C_LIB_CORE_H
