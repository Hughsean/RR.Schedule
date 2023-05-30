//
// Created by xSeung on 2023/4/30.
//

#ifndef OS_CD_IO_H
#define OS_CD_IO_H

typedef struct io_node_ {
        struct io_node_ *next;
        int              time;         // 服务对象需要的IO时间
        int              pid;          // 对象的pid
        int             *pro_io_time;  // 指向服务对象PCB的io_time字段
} IO_Node;

typedef struct io_devide_ {
        IO_Node *head;
        IO_Node *tail;
        int      pid;  ///< 已完成IO的PID号
} IO_Device, *IO_Device_p;

void io_post(int id, int time_required, int pid, int *pro_io_time);  // 内核向IO设备发送任务(不对外开放)
void io_run();                                                       // IO设备运行一个机器周期
const IO_Device_p ioDevice_entrance(unsigned int id);                // IO设备访问入口
void              io_init();                                         // IO设备初始化(不对外开放)
#endif                                                               // OS_CD_IO_H
