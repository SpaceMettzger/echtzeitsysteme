#include "process.h"
#include <stdio.h>
#include <string.h>

void p_switch_state(struct process *p) {
    p->p_state = p->p_state == READY 
    ? RUNNING 
    : READY;
}


void p_switch_to_blocked(struct process *p){
    p->p_state = p->p_state == BLOCKED 
    ? READY 
    : BLOCKED;
}



void p_print(struct process *p) {
    char enum_string[8];
    
    if (p->p_state == 0) {
        strcpy(enum_string, "READY");
    }
    else if (p->p_state == 1) {
        strcpy(enum_string, "RUNNING");
    } 
    else {
        strcpy(enum_string, "BLOCKED");
    }

    printf("Process %d, State: %s\n", p->p_id, enum_string);
}

