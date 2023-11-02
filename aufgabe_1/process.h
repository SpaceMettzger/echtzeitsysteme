#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>


enum state {READY, RUNNING};

struct process {
    uint32_t p_id;
    enum state p_state;
};

void p_switch_state(struct process *p);

void p_print(struct process *p);

#endif