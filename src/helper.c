#include "helper.h"
#include "stdio.h"
//#include "unistd.h"
//#include <stdlib.h>
//#include "csignal"
//#include "random"
//#include "sys/time.h"
//#include "stdlib.h"
void clock_g(void irq_handler(int)) {
//    struct sigaction act {};
//    struct itimerval t {};
//
//    act.sa_handler        = irq_handler;
//    t.it_interval.tv_sec  = RR_SLICE;
//    t.it_interval.tv_usec = 0;
//    t.it_value.tv_sec     = 0;
//    t.it_value.tv_usec    = 1000;
//
//    sigaction(SIGALRM, &act, nullptr);
//    setitimer(ITIMER_REAL, &t, nullptr);

    while (1) {
//        pause();
        if (kernel->power == 0) {
            break;
        }
//        sleep(1000);
        // todo
    }
}
void keyboard_g(void handler(int)) {
    while (1) {
        if (kernel->power == 0) {
            break;
        }
//        getchar();
        getchar();
        handler(0);
        // todo
    }
}
