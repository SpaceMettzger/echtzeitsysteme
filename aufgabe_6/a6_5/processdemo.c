#include "process.h"
#include <stdlib.h>
#include <stdio.h>

int main(){

    struct process *p_1 = (struct process*)malloc(sizeof(struct process));
    struct process *p_2 = (struct process*)malloc(sizeof(struct process));

    p_1->p_id = 12345;
    p_1->p_state = READY;

    p_2->p_id = 67890;
    p_2->p_state = RUNNING;

    printf("Testing Process 1\n");
    p_print(p_1);
    p_switch_state(p_1);
    p_print(p_1);

    printf("Testing Process 2\n");
    p_print(p_2);
    p_switch_state(p_2);
    p_print(p_2);

    free(p_1);
    free(p_2);

    return 0;
}