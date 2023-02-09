#include "helper.h"
#include "signal.h"
#include "stdio.h"
#include "sys/time.h"
#include "unistd.h"

void clock_g(void handler(int)) {

    struct itimerval t, old_t;
    //    struct sigaction act, old_act;
    //    act.sa_handler        = handler;
    t.it_interval.tv_sec  = 1;
    t.it_interval.tv_usec = 0;
    t.it_value.tv_sec     = 1;
    t.it_value.tv_usec    = 0;
    //
    //    sigaction(SIGALRM, &act, &old_act);
    signal(SIGALRM, handler);
    setitimer(ITIMER_REAL, &t, &old_t);
    //
    while (1) {
        pause();
        if (kernel->power == 0) {
            break;
        }
    }
}
void keyboard_g(void handler(int)) {
    while (1) {
        getchar();
        if (kernel->power == 0) {
            break;
        }
        handler(0);
        // todo
    }
}
