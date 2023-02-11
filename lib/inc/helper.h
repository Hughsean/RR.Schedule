#ifndef A_C_LIB_HELPER_H
#define A_C_LIB_HELPER_H

#include "iostream"

void timer();
void keyboard();

inline void clock_g() {
#ifdef TM
        timer();
#elif defined(KB)
        keyboard();
#endif
}

void print_tittle(std::ostream &os);
void show_pcblist(std::ostream &os, PCB* pcb);
void show_pcb(std::ostream &os,PCB* pcb);
void show_process(std::ostream &os,Process* pro);


Process *process_g();

#endif  // A_C_LIB_HELPER_H
