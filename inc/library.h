#ifndef A_C_LIB_LIBRARY_H
#define A_C_LIB_LIBRARY_H

const int time_slice       = 3;  // RR时间片
const int min_procrss_time = time_slice / 2;
const int max_process_time = time_slice * 2;
const int name_length      = 32;  // 进程名称长度
enum STATE{
    READY,
    RUNNING,
    WAITING
};
struct pcb {
    char   name[name_length];
    double arrivetime;
    double starttime;
    double servicetime;
};
void ma(void (*p)());
#endif  // A_C_LIB_LIBRARY_H
