#define CLOCK_TIME 400000

extern "C" {
#include "core.h"
}
#include "csignal"
#include "fmt/core.h"
#include "helper.h"
#include "iostream"
#include "random"
#include "unistd.h"
#include "json/json.h"
//
#define PRO_MAX_TIME 20
#define PRO_MIN_TIME 5
//
Pro_d *pro_pool = nullptr;
IO     io__[4]  = { NO, NET, DISK, USB };
//
void timer() {

        while (true) {
                if (kernel_entries()->power == 0) {
                        break;
                }
                ualarm(CLOCK_TIME, CLOCK_TIME);
                pause();
        }
}

void keyboard() {
        fd_set         fds, fds_;
        char           temp;
        struct timeval tv {};
        int            ch = 0;

        FD_ZERO(&fds);
        FD_SET(0, &fds);

        while (true) {
                tv.tv_sec  = 0;
                tv.tv_usec = 300000;
                fds_       = fds;
                if (kernel_entries()->power == 0) {
                        break;
                }
                if (select(1, &fds_, nullptr, nullptr, &tv) > 0) {
                        read(0, &temp, 1);
                        raise(SIGALRM);
                }
        }
}

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
        os << fmt::format("{:^12}", pro->time);
}

Process process_random_g() {
        std::default_random_engine         e{ std::random_device{}() };
        std::uniform_int_distribution<int> u{ 0, 1000 };

        Process p{
                .time = u(e) % (PRO_MAX_TIME - PRO_MIN_TIME) + PRO_MIN_TIME,
                .io   = io__[u(e) % IO_N],
        };
        if (p.io != NO) {

                p.io_point = u(e) % (p.time - PRO_MIN_TIME) + PRO_MIN_TIME;
        }
        else {
                p.io_point = -1;
        }
        return p;
}