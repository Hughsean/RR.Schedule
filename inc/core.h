#ifndef A_C_LIB_CORE_H
#define A_C_LIB_CORE_H

#define min_procrss_time 1  //
#define max_process_time 9  //
#define IO_N             4

#define PID_MAX  1024
#define REG_NUM  16  //
#define n_cpu    1   //
#define RR_SLICE 1   // RR时间片

// IO相关的定义
typedef enum io_ { NO, NET, DISK, USB } IO;
typedef enum state_ { READY, RUNNING, WAITING } STATE;
typedef enum priority_ { L, M, H } Priority;

typedef struct regs_ {
        long regs[REG_NUM];
} Regs;

typedef struct pi_ {
        int run_time;  // 进程已运行时间
        int time;      // 进程运行结束需要的时间
        IO  io;        // 执行IO的种类
        int io_point;  // 执行IO的时间点
} Process;

typedef struct pcb_ {
        int          pid;    // 进程ID号
        STATE        state;  // 进程状态
        Priority     prt;    // 优先级
        Regs         regs;   // 现场保护
        Process*     pro;    // 进程信息
        struct pcb_* next;
        struct pcb_* pre;
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

void init(Kernel* k);
void power_off(int _);

void irq_handler(int signal);

int  pid_alloc();
void pid_free(int pid);
PCB* create_pcb(Process* pi, Priority prt);
void remove_pcb(PCB* pcb);
void pcb_link();

void RR();

// extern Kernel* kernel;

Kernel* get_kernel();
#endif  // A_C_LIB_CORE_H
