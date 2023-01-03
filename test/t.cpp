#include "csignal"
#include "iostream"
#include "sys/time.h"
int n = 0;


void fun(int signal);

int main() {
    std::ios::sync_with_stdio(false);
    std::signal(SIGALRM, fun);
    itimerval a{.it_interval{1, 0},
                .it_value{0, 50}};

    setitimer(ITIMER_REAL, &a, nullptr);
    while (n<30){
        pause();
    }

    return 0;
}

void fun([[maybe_unused]]int signal) {
    std::cout << "call fun"<<n++<<std::endl;
}
