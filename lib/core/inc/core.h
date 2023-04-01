#ifndef A_C_LIB_CORE_H
#define A_C_LIB_CORE_H
#include "datastruct.h"
/**
 * �ں����ݷ�����ں���
 * @return �ں����ݵ�ַ
 */
const Kernel* kernel_entries();
/**
 * �ں˱�����ʼ��
 */
void init();
/**
 * ϵͳ�ػ�������
 * @param _ SIGNAL
 */
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
