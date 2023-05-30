//
// Created by xSeung on 2023/4/5.
//

#ifndef OS_CD_INTERFACE_H
#define OS_CD_INTERFACE_H
#ifdef __cplusplus
extern "C" {
#endif
// #define PID_BITMAP_BYTE 16
#define IO_DEVICE_N     2
#define REG_NUM         8
#define NAME_LENGTH     20
// #define RR_SLICE        3
// #define IRQ_N           4

typedef struct pcb_queue_ *PCB_Queue_p;
typedef struct kernel_    *Kernel_p;
typedef struct io_node_   *IO_Node_p;
typedef struct io_devide_ *IO_Device_p;
typedef struct regs_      *Regs_p;
typedef struct cpu_       *CPU_p;
typedef struct program_   *Program_p;
typedef struct pcb_       *PCB_p;
int                        cpu_clk();
int                        finish();
void                       predict(int *pc, void **br, PCB_p *p);
int                        pcb_pid(PCB_p p);
const char                *pcb_name(PCB_p p);
const IO_Device_p          io_devive_at(int i);
int                        io_device_serves_pid(const IO_Device_p io);
Program_p                  program_alloc(const char *name, int name_len, int as_len, int *as, int iot, int at);
void                       program_free(Program_p p);
int                        program_at(Program_p p);
const int                 *cpu_ur();
extern void                system_init();
extern void                io_init();
extern void                io_run();
extern void                programload(Program_p program);
extern void                clk_irq();
extern void                cpu_run();

#ifdef __cplusplus
}
#endif
#endif  // OS_CD_INTERFACE_H
