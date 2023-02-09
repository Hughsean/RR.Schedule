#ifndef A_C_LIB_HELPER_H
#define A_C_LIB_HELPER_H

void timer();
void keyboard();

inline void clock_g() {
#ifdef TM
        timer();
#elif defined(KB)
        keyboard();
#endif
}

void print_tittle();
void show_pcblist(PCB* pcb);
void show_pcb(PCB* pcb);
void show_process(Process* pro);
#endif  // A_C_LIB_HELPER_H
