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
                break;
                // TODO
                //                ualarm(CLOCK_TIME, CLOCK_TIME);
                //                pause();
        }
}

void keyboard() {
        int ch{};
        while (true) {
                if (_kbhit()) {
                        ch = _getch();
                        if (ch == 'q') {
                                break;
                        }
                        if (ch == ' ') {
                                //                                std::wcout << L"irq,
                                //                                测试\n";
                                //                                std::wcout.flush();
                        }
                }
        }
        raise(SIGINT);
}