#ifndef A_C_LIB_HELPER_H
#define A_C_LIB_HELPER_H
#include "core.h"
void        clock_g(void handler(int));
void        keyboard_g(void handler(int));

inline void irq_generator() {
#ifdef CLOCK
    clock_g(irq_handler);
#endif
#ifdef KEYBOARD
    keyboard_g(irq_handler);
#endif
}

#endif  // A_C_LIB_HELPER_H
