#ifndef A_C_LIB_CORE_H
#define A_C_LIB_CORE_H

#define IO_N        4   //
#define NET_DEVICE  1   //
#define DISK_DEVICE 1   //
#define USB_DEVICE  1   //
#define PID_MAX     32  //
#define REG_NUM     2   //
#define CPU_N       1   //
#define RR_SLICE    3   // RRʱ��Ƭ

// IO��صĶ���
typedef enum io_ { NO, NET, DISK, USB } IO;
typedef enum state_ { RUNNING, READY, WAITING, FB } STATE;
typedef enum priority_ { L, M, H } Priority;

typedef struct regs_ {
        long regs[REG_NUM];
} Regs;

typedef struct pi_ {
        int time_need;  // �������н�����Ҫ��ʱ��
        IO  io;         // ִ��IO������
        int io_point;   // ִ��IO��ʱ���
} Process;

typedef struct pcb_ {
        int          pid;          // ����ID��
        Priority     prt;          // ���ȼ�
        int          run_time;     // ����������ʱ��
        int          io_run_time;  // io������ʱ��
        STATE        state;        // ����״̬
        Regs         regs;         // �ֳ�����
        Process*     pro;          // ������Ϣ
        struct pcb_* next;
        //        struct pcb_* pre;
} PCB;

typedef struct kernel_ {
        PCB* execute_p;      // ִ�ж���
        PCB* ready_p_h;      // ��������
        PCB* ready_p_t;      //
                             // PCB* ready_p_tail;
                             // ��������β
        PCB* block_p;        // IO��������
        PCB* fallback_p;     // �󱸶���
                             // PCB* block_p_tail;
                             // ��������β
        Regs regs;           // �Ĵ�����
        int  current_clock;  // ��ǰϵͳ����
        int  power;          // ϵͳʹ���ź�
        int  rr_time;        // ����RR�㷨��ִ�н�������ʱ��
} Kernel;

// �ⲿ�����ں˱������
const Kernel* kernel_entries();
// �ں˱�����ʼ��
void init();
// ϵͳ�ػ�
void power_off(int _);
// Ӳ���ж���Ӧ����
void irq_handler(int signal);

// pid������
int pid_alloc();
// pid����
void pid_free(int pid);

// ���ؽ���
void process_load(Process* pi, Priority pri);
// �ͷŽ���
void process_free(PCB* pcb);
// ���̷�����
void dispatcher();
// �������л�������ʵ�����ã�ռλ����
void context_switch(Regs* dect, Regs* src);
// cpuִ����
void cpu_processer();
// ioִ����
void io_processer();
// RR����
void RR();
#endif  // A_C_LIB_CORE_H
