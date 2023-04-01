//
// Created by xSeung on 2023/3/31.
//
extern "C" {
#include "core.h"
}
#include "conio.h"
#include "csignal"
#include "iostream"
void timer() {

        while (true) {
                if (kernel_entries()->power == 0) {
                        break;
                }
                // TODO
                //                ualarm(CLOCK_TIME, CLOCK_TIME);
                //                pause();
        }
}

void keyboard() {
        int ch{};
        while (true) {
                if (kbhit()) {
                        ch = getch();
                        if (ch == 'q') {
                                break;
                        }
                        if (ch == ' ') {
                                std::cout << "irq\n";
                                std::cout.flush();
                        }
                }
        }
        raise(SIGINT);
}