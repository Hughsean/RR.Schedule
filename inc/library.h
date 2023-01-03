#ifndef A_C_LIB_LIBRARY_H
#define A_C_LIB_LIBRARY_H
#define time_slice 3  // RR时间片
#define min_procrss_time 1
#define max_process_time 9
#define name_length 32  // 进程名称长度

//
enum STATE { READY, RUNNING, WAITING };

struct PCB {
    char   name[name_length];
    double arrivetime;
    double starttime;
    double servicetime;
};

struct JCB {};
void ma(void (*p)());
#endif  // A_C_LIB_LIBRARY_H
