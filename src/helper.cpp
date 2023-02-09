extern "C" {
#include "core.h"
}
#include "csignal"
#include "fmt/core.h"
#include "helper.h"
#include "iostream"

void timer() {
        while (true) {
                if (get_kernel()->power == 0) {
                        break;
                }
                alarm(1);
                pause();
        }
}
void keyboard() {
        while (true) {
                if (get_kernel()->power == 0) {
                        break;
                }
                getchar();
                alarm(0);
                pause();
        }
}

void print_tittle() {
        std::cout << fmt::format("{:^12}", "PID");
        std::cout << fmt::format("{:^12}", "优先级");
        std::cout << fmt::format("{:^12}", "状态");
        std::cout << fmt::format("{:^15}", "已运行时间");
        std::cout << fmt::format("{:^15}", "总需时间") << std::endl;
}

void show_pcblist(PCB *pcb) {
        if (pcb == nullptr) {
                std::cout << "NULL" << std::endl;
                return;
        }
        print_tittle();
        PCB *p = pcb;
        while (true) {
                show_pcb(p);
                p = p->next;
                if (p == nullptr) {
                        break;
                }
        }
}
void show_pcb(PCB *pcb) {
        std::cout << fmt::format("{:^12}", pcb->pid);
        std::cout << fmt::format("{:^12}", pcb->prt);
        std::cout << fmt::format("{:^12}", pcb->state);
        show_process(pcb->pro);
        std::cout << std::endl;
}
void show_process(Process *pro) {
        std::cout << fmt::format("{:^12}", pro->run_time);
        std::cout << fmt::format("{:^12}", pro->time);
}
