//
// Created by xSeung on 2023/4/30.
//

#ifndef OS_CD_IO_H
#define OS_CD_IO_H

typedef struct io_node_ {
        struct io_node_ *next;
        int              time;
        int              pid;
} IO_Node;

typedef struct io_devide_ {
        IO_Node *head;
        IO_Node *tail;
        //        int       completed_pid;
} IO_Device;

void io_push(int did,int time, int pid);
void io_run();
#endif  // OS_CD_IO_H
