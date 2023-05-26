//
// Created by xSeung on 2023/4/30.
//

#ifndef OS_CD_IO_H
#define OS_CD_IO_H

typedef struct io_node_ {
        struct io_node_ *next;
        int              time;
        int              pid;
        int             *pro_io_time;
} IO_Node;

typedef struct io_devide_ {
        IO_Node *head;
        IO_Node *tail;
        int      pid;  ///< 已完成IO的PID号
} IO_Device, *IO_Device_p;

void              io_post(int id, int time_required, int pid, int *pro_io_time);
void              io_run();
const IO_Device_p ioDevice_entrance(unsigned int id);
void              io_init();
#endif  // OS_CD_IO_H
