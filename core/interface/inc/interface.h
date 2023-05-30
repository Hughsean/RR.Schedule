//
// Created by xSeung on 2023/4/5.
//

#ifndef OS_CD_INTERFACE_H
#define OS_CD_INTERFACE_H
#ifdef __cplusplus
extern "C" {
#endif
#define IO_DEVICE_N 2
#define REG_NUM     8
#define NAME_LENGTH 20
#define CLK_TIME    3

typedef struct pcb_queue_ *PCB_Queue_p;
typedef struct kernel_    *Kernel_p;
typedef struct io_node_   *IO_Node_p;
typedef struct io_devide_ *IO_Device_p;
typedef struct regs_      *Regs_p;
typedef struct cpu_       *CPU_p;
typedef struct program_   *Program_p;
typedef struct pcb_       *PCB_p;
int                        cpu_clk();                          // 获取CPU周期
int                        finish();                           // 判断用户程序是否全部结束
void              predict(int *pc, void **br, PCB_p *p);       // 预测下个周期将执行指令及其对应PCB句柄
int               pcb_pid(PCB_p p);                            // 获取PCB句柄的PID
const char       *pcb_name(PCB_p p);                           // 获取PCB句柄的名称
const IO_Device_p io_devive_at(int i);                         // 获取i号IO设备句柄
int               io_device_serves_pid(const IO_Device_p io);  // IO设备服务对象PID
Program_p   program_alloc(const char *name, int name_len, int as_len, int *as, int iot, int at);  // 创建程序句柄
void        program_free(Program_p p);                                                            // 回收程序句柄
int         program_at(Program_p p);  // 获取程序句柄中的程序抵达时间
const int  *cpu_ur();                 // 获取CPU的寄存器
extern void system_init(int *clk_);   // 系统初始化
extern void io_run();                 // IO运行一个机器周期
extern void programload(Program_p program);  // 加载程序句柄(内核会创建PCB,也就是静态程序到动态进程转变)
extern void clk_irq();                       // 时钟中断信号
extern void cpu_run();                       // CPU运行一个机器周期
#ifdef __cplusplus
}
#endif
#endif  // OS_CD_INTERFACE_H
