#ifndef A_C_LIB_CORE_H
#define A_C_LIB_CORE_H

#define min_procrss_time 5     //
#define max_process_time 20     //
#define IO_N             4     //
#define PID_MAX          1024  //
#define REG_NUM          16    //
#define MM_SIZE          10    //
#define n_cpu            1     //
#define RR_SLICE         3     // RR时间片

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

typedef struct mm_slice {
        Process mm;
        int     prt;
        char    is_null;
} MM_Slice;

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
        PCB* ready_p_head;   // 就绪队列头
        PCB* ready_p_tail;   // 就绪队列尾
        PCB* block_p;        // 阻塞队列
        Regs regs;           // 寄存器组
        int  current_clock;  // 当前系统周期
        int  power;          // 系统使能信号
        int  PCB_N;          // 分配PID
        int  mm_p;           // mm位置指针
        int  rr_time;        // 本轮RR算法，执行进程已用时间
} Kernel;

const Kernel* kernel_entries();

void init();
void power_off(int _);
void irq_handler(int signal);

int  pid_alloc();
void pid_free(int pid);

PCB* create_pcb(Process* pi, Priority prt);
void remove_pcb(PCB* pcb);
void pcb_link();

void     mm_write(MM_Slice ms, int pos);
MM_Slice mm_read(int pos);

void load_regs(PCB* pcb);
void store_regs(PCB* pcb);

void RR();
#endif  // A_C_LIB_CORE_H
