//
// Created by xSeung on 2023/4/30.
//
#include "io.h"
#include "cpu.h"
#include "stdlib.h"

static IO_Device io_device[IO_DEVICE_N];

void io_push(int did, int time, int pid) {
        IO_Node *p = (IO_Node *)malloc(sizeof(IO_Node));
        p->next    = NULL;
        p->time    = time;
        p->pid     = pid;
        if (io_device[did].head == NULL) {
                io_device[did].head = p;
                io_device[did].tail = p;
                return;
        }
        io_device[did].tail->next = p;
        io_device[did].tail       = p;
}
void io_run() {
        for (int i = 0; i < IO_DEVICE_N; ++i) {
                if (io_device[i].head == NULL) {
                        return;
                }
                io_device[i].head->time--;
                if (io_device[i].tail->time == 0) {
                        IO_Node *p = io_device[i].head;
                        //                io_device.completed_pid = io_device.head->pid;
                        io_device[i].head = io_device[i].head->next;
                        free(p);
                        io_irq(i);  // 发出IO中断请求
                }
        }
}
