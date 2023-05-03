//
// Created by xSeung on 2023/4/30.
//
#include "io.h"
#include "cpu.h"
#include "memory.h"
#include "stdlib.h"
static IO_Device io_device[IO_DEVICE_N];

void io_post(int id, int time_required, int pid, int *pro_io_time) {
        IO_Node *p     = (IO_Node *)malloc(sizeof(IO_Node));
        p->next        = NULL;
        p->time        = time_required;
        p->pid         = pid;
        p->pro_io_time = pro_io_time;
        if (io_device[id].head == NULL) {
                io_device[id].head = p;
                io_device[id].tail = p;
                return;
        }
        io_device[id].tail->next = p;
        io_device[id].tail       = p;
}
void io_run() {
        for (int id = 0; id < IO_DEVICE_N; ++id) {
                if (io_device[id].head == NULL) {
                        continue;
                }
                (*io_device[id].head->pro_io_time)++;
                if (io_device[id].head->time == *io_device[id].head->pro_io_time) {
                        IO_Node *p = io_device[id].head;
                        //                io_device.completed_pid = io_device.head->pid;
                        io_device[id].head = io_device[id].head->next;                            /* code */
                        
                        io_device[id].pid  = p->pid;
                        free(p);
                        io_irq(id);  // 发出IO中断请求
                }
        }
}
const IO_Device *ioDevice_entrance(int id) {
        if (id >= IO_DEVICE_N) {
                abort();
        }
        return &io_device[id];
}
void io_init() {
        memset(io_device, 0, sizeof(IO_Device) * IO_DEVICE_N);
}
