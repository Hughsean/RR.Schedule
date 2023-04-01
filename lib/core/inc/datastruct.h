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

#endif  // OS_CD_DATASTRUCT_H
