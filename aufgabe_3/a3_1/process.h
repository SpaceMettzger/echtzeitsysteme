#pragma once
#include <stdint.h>


enum state {READY, RUNNING, BLOCKED};

struct process {
    uint32_t p_id;
    enum state p_state;
};

void p_switch_state(struct process *p);

void p_switch_to_blocked(struct process *p);

void p_print(struct process *p);

