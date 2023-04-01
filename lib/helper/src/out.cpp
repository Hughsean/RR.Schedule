//
// Created by xSeung on 2023/3/31.
//
#include "fmt/core.h"
#include "helper.h"

void print_tittle(std::ostream &os) {
        os << fmt::format("{:^12}", "PID");
        os << fmt::format("{:^12}", "状态");
        os << fmt::format("{:^12}", "优先级");
        os << fmt::format("{:^15}", "已运行时间");
        os << fmt::format("{:^15}", "总需时间") << std::endl;
}

void show_pcblist(std::ostream &os, PCB *pcb) {
        if (pcb == nullptr) {
                os << "NULL" << std::endl;
                return;
        }
        print_tittle(os);
        PCB *p = pcb;
        while (true) {
                show_pcb(os, p);
                p = p->next;
                if (p == nullptr) {
                        break;
                }
        }
}
void show_pcb(std::ostream &os, PCB *pcb) {
        os << fmt::format("{:^12}", pcb->pid);
        os << fmt::format("{:^12}", pcb->state);
        os << fmt::format("{:^12}", pcb->prt);
        os << fmt::format("{:^12}", pcb->run_time);
        show_process(os, pcb->pro);
        os << std::endl;
}
void show_process(std::ostream &os, Process *pro) {
        os << fmt::format("{:^12}", pro->time_need);
}